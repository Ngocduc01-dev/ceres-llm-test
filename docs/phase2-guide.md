# Phase 2 – Liệt kê và phân loại unit

> Mục tiêu: xuất danh sách **toàn bộ unit** trong phạm vi kiểm thử, phân loại mức độ khó, khả năng gọi trực tiếp và sắp xếp thứ tự sinh test từ dưới lên (bottom-up).
> Đây là "bảng điều phối" cho Phase 3 gom context, Phase 5 sinh code test và Phase 8 chạy hàng loạt.

---

## 1. Chạy

Cần chạy Phase 1 `phase1.sh` trước (để có `data/graph.db`).

```bash
./scripts/run_docker.sh bash scripts/phase2.sh
```

| Bước | Script | Đầu ra |
|---|---|---|
| 1 | `scripts/list_units.py` | `data/units.json` (không commit – sinh lại được), `reports/units/summary.txt`, `data/smoke_test_units.txt` |

---

## 2. Cấu trúc `data/units.json`

Mỗi phần tử trong `data/units.json` đại diện cho một unit (`function` có `in_scope = 1` trong `graph.db`):

```json
{
  "id": "u0042",
  "graph_id": 1834,
  "name": "ceres::internal::Foo::Bar",
  "file": "internal/ceres/foo.cc",
  "lines": [120, 168],
  "signature": "bool Bar(const double* x, double* y)",
  "branches": 6,
  "cyclomatic": 4,
  "topo_level": 0,
  "level": "de",
  "callable": "public",
  "access": "public",
  "linkage": "external",
  "called_by_tests": 2,
  "fan_in": 3,
  "fan_out": 0,
  "template_args": null,
  "order": 42
}
```

### Quy tắc phân loại

| Trường | Giá trị | Cách xác định |
|---|---|---|
| `level` (độ khó) | `de` / `trung_binh` / `kho` | Dựa trên kiểu tham số và cạnh `USES_TYPE`: `de` (số, `bool`, con trỏ mảng thuần); `trung_binh` (Eigen, STL, struct nhỏ); `kho` (`Problem`, `CostFunction`, `LinearSolver`, `SparseMatrix`, `ThreadPool`…) |
| `callable` | `public` / `internal` | `internal` nếu `linkage == "internal"` (`static`, anonymous namespace) hoặc `access` là `private` / `protected` |
| `topo_level` | `0, 1, 2...` | Kế thừa trực tiếp từ `level` của Phase 1 (`0` = hàm lá, các chu trình đệ quy đã được gom nhóm) |
| `template_args` | `["double"]` / `null` | Gán kiểu instantiate mặc định cho hàm/class template để Phase 5 biên dịch được |
| `order` | `1..N` | Sắp xếp theo `(topo_level, level, callable, branches)` để sinh test từ đơn giản đến phức tạp |

---

## 3. Vì sao làm như vậy

### 3.1. Tách riêng `topo_level` và `level`
- Phase 1 dùng cột `level` để lưu độ sâu trên đồ thị gọi hàm (`0` = hàm lá), trong khi kế hoạch tổng thể dùng `level` để chỉ độ khó (`de`, `trung_binh`, `kho`). Tách rõ hai trường giúp các phase sau không bị nhầm lẫn khi lọc dữ liệu.

### 3.2. Kết hợp thứ tự topo với độ khó
- Sắp xếp ưu tiên `topo_level` trước rồi mới đến `level` đảm bảo mọi hàm con (hàm lá) đều được sinh test và xác minh cách khởi tạo input trước khi LLM xử lý các hàm cấp cao hơn.

### 3.3. Xuất sẵn tập `smoke_test_units.txt`
- Lọc ra 20 unit mức `de` ở `topo_level = 0`, `callable = public` và ưu tiên hàm đã có test mẫu (`called_by_tests > 0`) để nhóm chạy thử thông mạch Phase 3 → Phase 6 trước khi nhân rộng toàn dự án.
