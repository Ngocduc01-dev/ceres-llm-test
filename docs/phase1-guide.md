# Phase 1 – Code graph và AST

> Mục tiêu: biết **mỗi unit gọi hàm nào, được ai gọi, dùng kiểu gì, cần include gì, có bao nhiêu nhánh**.
> Đây là "bản đồ" để Phase 2 liệt kê/sắp xếp unit và Phase 3 gom context cho LLM.

---

## 1. Chạy

Cần chạy Phase 0 `build.sh` trước (để có `data/compile_commands.json`).

```bash
scripts/run_docker.sh env JOBS=4 bash scripts/phase1.sh      # ~6–8 phút
```

`phase1.sh` chạy lần lượt:

| Bước | Script | Đầu ra |
|---|---|---|
| 1 | `scripts/build_graph.py` | `data/graph.db` (SQLite, không commit – sinh lại được), `reports/graph/summary.txt`, `reports/graph/stats.json` |
| 2 | `scripts/viz_graph.py` | `reports/graph/graph.html` – xem graph tương tác |
| 3 | `scripts/ast_export.py` | `reports/ast/ast.html` – xem AST của các unit tiêu biểu |

Tra cứu 1 unit từ dòng lệnh:

```bash
scripts/run_docker.sh python3 scripts/graph_query.py ComputeStep
scripts/run_docker.sh python3 scripts/graph_query.py "ceres::internal::DoglegStrategy::ComputeStep" --hops 2 --json
```

Xuất AST cho unit tuỳ chọn:

```bash
scripts/run_docker.sh python3 scripts/ast_export.py --units ComputeStep "ceres::internal::Program::IsValid"
```

Xem file HTML: mở trực tiếp bằng trình duyệt (cần mạng để tải thư viện vẽ graph `cytoscape.js` từ cdnjs).

---

## 2. Graph gồm những gì

### Node (bảng `nodes`)

| Loại | Là gì | Thuộc tính chính |
|---|---|---|
| `function` | hàm, method, constructor, destructor, function template | signature, kiểu tham số, file:dòng, access, linkage, số nhánh, cyclomatic, level, fan-in/out, số test có sẵn gọi tới |
| `class` | class / struct / class template | file:dòng, có phải template |
| `file` | file `.h` / `.cc` của Ceres | |

**Unit** = node `function` có `in_scope = 1`: có thân hàm, nằm trong `internal/ceres/` hoặc `include/ceres/`, không phải file test, không phải code sinh tự động, không phải googletest.

### Cạnh (bảng `edges`)

| Cạnh | Ý nghĩa | Dùng để |
|---|---|---|
| `CALLS` A→B | hàm A gọi hàm B (`count` = số chỗ gọi) | gom signature hàm được gọi vào prompt; biết cần stub gì; sắp thứ tự |
| `USES_TYPE` A→C | hàm A dùng class C (tham số, biến, giá trị trả về) | đưa định nghĩa class vào prompt; biết header cần include |
| `INHERITS` C→P | class C kế thừa P | biết có thể viết class con giả lập (stub) |
| `MEMBER_OF` A→C | method A thuộc class C | đưa khai báo class vào prompt |
| `DEFINED_IN` X→F | hàm/class định nghĩa trong file F | |
| `INCLUDES` F→G | file F `#include` file G | |

Lời gọi từ **test có sẵn** (`*_test.cc`) cũng được ghi lại (`called_by_tests`), để Phase 3 lấy làm **test mẫu** cho LLM bắt chước.

### Thuộc tính tính sẵn cho các phase sau

| Thuộc tính | Cách tính | Dùng ở |
|---|---|---|
| `branches` | 2 × số điểm quyết định (`if`, `for`, `while`, `do`, `case`, `?:`, `catch`, `&&`, `||`) đếm trên AST | ước lượng độ khó, Phase 2 phân loại. Số nhánh thật do gcov đếm (Phase 4) |
| `cyclomatic` | 1 + số điểm quyết định | |
| `level` | 0 = hàm lá (không gọi hàm Ceres khác); level k = gọi tới hàm level k-1. Chu trình (đệ quy) gom lại thành 1 nhóm | Phase 2: sinh test **từ dưới lên** |
| `linkage` | `internal` = `static` hoặc trong namespace ẩn danh | Phase 5: phải `#include "file.cc"` mới gọi được |
| `access` | public / protected / private | Phase 5: method private phải gọi gián tiếp |
| `fan_in` / `fan_out` | số hàm (không phải test) gọi tới / số hàm nó gọi | ưu tiên, độ ảnh hưởng |
| `called_by_tests` | số test có sẵn gọi trực tiếp | chọn test mẫu |

---

## 3. Vì sao làm như vậy

### 3.1. Vì sao dùng libclang mà không dùng tool có sẵn (Joern, codegraph, Doxygen…)?
- libclang đã dùng ở Phase 0, parse được **292/292** file với đúng cờ compile. Không phải cài thêm gì.
- Hiểu C++ đầy đủ: biết `a.Foo()` gọi **đúng** hàm `Foo` nào (overload, namespace, method của class nào), biết kiểu tham số. Tool dựa trên regex/tree-sitter sẽ đoán sai với code nhiều template như Ceres.
- Tự viết thì lấy được đúng thứ các phase sau cần (linkage, access, số nhánh, level), không thừa không thiếu.

### 3.2. Vì sao lưu SQLite?
- 1 file, không cần cài server (khác Neo4j). Python có sẵn `sqlite3`.
- Truy vấn bằng SQL đơn giản: "hàm nào gọi X", "unit nào chưa có test gọi"…
- Kích thước ~10 MB, dựng lại mất vài phút → không commit, ai cần thì chạy lại.

### 3.3. Vì sao chỉ duyệt code của Ceres?
- Mỗi file `.cc` include hàng trăm header của Eigen, glog, thư viện chuẩn. Duyệt hết thì chậm hàng chục lần và graph đầy node không liên quan.
- Script chỉ đi vào node nằm trong `internal/ceres/`, `include/ceres/`. Lời gọi ra ngoài (Eigen, std…) chỉ đếm số lượng.

### 3.4. Vì sao đếm nhánh trên AST, không đếm bằng token hay regex?
- Đếm token `&&`, `||` trên cả hàm sẽ **tính nhầm code nằm trong `#if` bị tắt** (xem nhật ký: `GetBestSchurTemplateSpecialization` từ 37 xuống 1). AST chỉ chứa code thật sự được compile, giống cái gcov đo.
- Macro như `CHECK(x)` của glog khi bung ra có chứa `?:` → AST đếm là 1 điểm quyết định. gcov cũng đếm nhánh này. Không tránh được, cần biết khi đọc số liệu.

### 3.5. Vì sao cần `level`?
- Hàm lá (level 0) dễ test nhất: không gọi hàm Ceres nào khác, không cần stub.
- Làm từ dưới lên: khi tới hàm level cao, các hàm nó gọi đã có test → dùng lại cách khởi tạo input đã chạy được.

---

## 4. Hạn chế đã biết

| Hạn chế | Ảnh hưởng | Cách xử lý ở phase sau |
|---|---|---|
| Lời gọi trong template phụ thuộc kiểu (`T::Foo()`) không resolve được (~8.700 chỗ) | thiếu một số cạnh `CALLS` trong code template | Phase 3 thêm signature các method của class được dùng (`USES_TYPE`) |
| Lời gọi qua hàm ảo chỉ trỏ tới hàm của class cha | không thấy class con nào thực sự được gọi | dùng cạnh `INHERITS` để tìm các class con |
| `branches` là ước lượng từ AST | có thể lệch với gcov (gcov còn tính nhánh compiler tự sinh) | Phase 4 lấy nhánh mục tiêu từ gcov |
| AST viewer chỉ xuất ~36 unit tiêu biểu | file HTML không quá nặng | xuất unit khác bằng `--units` |
