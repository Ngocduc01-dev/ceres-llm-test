# Phase 4 – Dựng CFG bằng Clang

> Mục tiêu: mỗi unit có CFG do **tool** dựng (`units/<id>/cfg.txt`), gọn và có số dòng, đưa vào mục 3 của prompt.
> Nhật ký, lỗi gặp và kết quả: `logs/phase4-log.md`.

## Chạy

Cần: Docker, bản build Phase 0 (`scripts/build.sh`) để có `data/compile_commands.json` và header sinh ra trong volume build.

```bash
scripts/run_docker.sh env JOBS=4 python3 scripts/build_cfg.py          # tất cả unit (~3.5 phút)
scripts/run_docker.sh python3 scripts/build_cfg.py --smoke             # 20 unit smoke test
scripts/run_docker.sh python3 scripts/build_cfg.py --ids u0553 u0540   # vài unit
python3 scripts/render_prompt.py                                       # ghép lại prompt có CFG
```

## Cách hoạt động

1. Với mỗi file `.cc` của Ceres (292 file, kể cả test), chạy:
   ```
   clang++-18 --analyze --analyzer-no-default-checks
     -Xclang -analyzer-checker=debug.DumpCFG
     -Xclang -analyzer-display-progress
     -Xclang -analyzer-opt-analyze-headers
     -Xclang -analyzer-config -Xclang cfg-implicit-dtors=false,cfg-temporary-dtors=false,cfg-lifetime=false,cfg-scopes=false,cfg-loopexit=false
     <cờ compile từ compile_commands.json> file.cc
   ```
2. Giữ CFG của hàm trong `internal/ceres/`, `include/ceres/` (bỏ Eigen, std, googletest).
3. Làm gọn (thay tham chiếu, bỏ ép kiểu ngầm, gom `CHECK`/`VLOG`, ghi T/F, gắn số dòng) – chi tiết ở nhật ký.
4. Ghép với unit theo (file, tên, tham số) → `units/<id>/cfg.txt`.

## Vì sao làm như vậy

- **Vì sao Clang mà không để LLM tự dựng:** Clang thấy đúng code được compile (macro đã bung, `#if` theo cờ build, `switch`/`break`/`try`); LLM đọc source thô có thể vẽ cả code trong `#if` bị tắt. Mẫu số C2 cố định giữa các lần chạy.
- **Vì sao chạy theo file `.cc` mà không theo từng hàm:** `-analyze-function` đòi tên kèm đúng kiểu tham số; chạy cả file rồi tách theo tên vừa nhanh (292 lần thay vì 1540) vừa không phải đoán tên.
- **Vì sao chạy cả file test:** template chỉ có CFG khi được instantiate; file test là nơi instantiate nhiều template của header.
- **Vì sao gom `CHECK`/`VLOG`:** macro glog bung ra hàng chục khối in log; gom lại thành 1 điểm quyết định có số dòng chính xác (lấy từ `LogMessage(file, dòng)`).
- **Vì sao không lưu output thô:** chỉ dùng bản đã làm gọn; output thô dài gấp nhiều lần và chạy lại được bất cứ lúc nào.

## Định dạng `cfg.txt`

```
UNIT u0540
Hàm: SetUpperBound(int index, double upper_bound)  → trả về void
Loại: method (hàm thành viên của class)
Thuộc class: ceres::internal::ParameterBlock
Vị trí: internal/ceres/parameter_block.h, dòng 190–205

Số điểm rẽ nhánh: 2 (và 1 lệnh CHECK)

START → 1
1   CHECK_LT(index, size_)                                         đúng → 2   sai → DỪNG
2   if (upper_bound >= std::numeric_limits<double>::max() && !upper_bounds_)   đúng → 3   sai → 4
3   return                                                         → END
4   if (!upper_bounds_)                                            đúng → 5   sai → 6
5   upper_bounds_ = std::make_unique<double[]>(size_)
    std::fill(upper_bounds_.get(), upper_bounds_.get() + size_, std::numeric_limits<double>::max())   → 6
6   upper_bounds_[index] = upper_bound                             → END
```

| Thành phần | Ý nghĩa |
|---|---|
| Phần đầu | Thông tin hàm: tên + tham số (không có tham số thì `()`), kiểu trả về, loại hàm, class hoặc namespace, vị trí. Hàm/class template có thêm dòng **Ghi chú**: template là code có kiểu dữ liệu để trống; Clang chỉ dựng CFG khi kiểu đã được điền, nên ghi chú cho biết CFG dựng với kiểu nào (vd. `LineManifold<3>`) |
| `Số điểm rẽ nhánh` | Số chỗ `if`/`for`/`while`/`switch`/`?:` (mỗi chỗ 2 nhánh); `CHECK` đếm riêng |
| `START`, `END`, `DỪNG` | Bắt đầu, kết thúc, chương trình dừng (do `CHECK`/`assert` sai) |
| `1`, `2`, `3`… | Số node, **đánh riêng cho từng unit theo thứ tự chạy**. Câu lệnh chạy trước một điều kiện là 1 node riêng |
| Node nhiều câu lệnh | Mỗi câu lệnh 1 dòng, mũi tên ở câu cuối. Không cắt bớt nội dung |
| `đúng → x   sai → y` | Điểm rẽ nhánh: điều kiện đúng đi node x, sai đi node y (`switch`: `nhánh → …`) |

Những gì script đã làm gọn sẵn (người đọc không cần biết): gộp điều kiện ghép `a && b` / `a || b` (Clang tách thành 2 khối) thành 1 node; bỏ nhánh in log của macro `VLOG` (không phải logic của hàm); bỏ khối rỗng và khối không bao giờ tới được; đổi `for (...; i < n; ...)` thành `vòng for, điều kiện: i < n`.

Cách đọc cho LLM nằm trong `prompts/master_prompt.md` mục 3.2.
