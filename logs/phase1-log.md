# Nhật ký Phase 1 – Code graph và AST (Ceres 2.2.0)

Ghi theo thứ tự: làm gì, kết quả, vấn đề gặp phải, xử lý thế nào, vì sao.
Hướng dẫn chạy và giải thích thiết kế: `docs/phase1-guide.md`.

---

## Bước 1 – Thiết kế graph

**Làm gì:** chốt graph cần chứa những gì, dựa trên việc các phase sau cần hỏi gì:

| Phase sau cần hỏi | Graph phải có |
|---|---|
| Phase 2: unit nào, độ khó, làm trước/sau | node `function` + số nhánh, linkage, access; `level` (từ dưới lên) |
| Phase 3: đưa gì vào prompt | cạnh `CALLS` (hàm được gọi), `USES_TYPE` (class được dùng), `MEMBER_OF` (class chứa), header cần include |
| Phase 3: test mẫu | lời gọi từ file `*_test.cc` có sẵn |
| Phase 5: stub cái gì | `CALLS` tới hàm nặng, `INHERITS` để viết class con giả lập |

**Quyết định:** tự viết bằng libclang (đã dùng ở Phase 0, parse 292/292 file OK), lưu SQLite. Lý do: `docs/phase1-guide.md` mục 3.

---

## Bước 2 – Viết script

| Script | Việc |
|---|---|
| `scripts/build_graph.py` | parse 292 file `.cc` song song, trích node/cạnh, gộp, tính fan-in/out, level, ghi `data/graph.db` + thống kê |
| `scripts/graph_query.py` | tra cứu: tìm unit, BFS hàm gọi/được gọi, **gói context cho Phase 3** (`Graph.context()`) |
| `scripts/viz_graph.py` + `templates/graph.html` | xuất graph ra HTML tương tác (cytoscape.js) |
| `scripts/ast_export.py` + `templates/ast.html` | xuất AST của ~36 unit tiêu biểu ra HTML |
| `scripts/phase1.sh` | chạy cả 3 bước trên |

**Tối ưu đã áp dụng ngay từ đầu** (rút kinh nghiệm Phase 0):
- Chỉ duyệt node nằm trong file Ceres, bỏ qua Eigen/glog/std.
- Hàm trong header bị parse lại ở nhiều file `.cc` → mỗi process nhớ hàm đã duyệt thân, không duyệt lại.
- Bỏ googletest (`gmock_gtest_all.cc`, `gmock/`, `gtest/`) mà Ceres 2.2.0 để trong `internal/ceres/`.

---

## Bước 3 – Chạy lần 1

**Kết quả:** 292/292 file không lỗi, ~6 phút. Nhưng số unit = **2302**, nhiều hơn hẳn con số ~1500 của Phase 0.

**Vấn đề 1: đếm cả hàm do compiler tự sinh.**
- **Phát hiện:** tra cứu `DoglegStrategy::ComputeStep` thấy nó "gọi" `TrustRegionStrategy::Summary::Summary()`, `Summary(Summary&&)`, `operator=`… Đây là constructor/operator do compiler tự sinh, **không có trong source**, không viết test cho được.
- **Nguyên nhân:** khi gặp lời gọi, script tạo node cho hàm được gọi và đánh dấu "có định nghĩa" theo libclang (libclang coi hàm tự sinh là có định nghĩa).
- **Xử lý:** node tạo từ lời gọi luôn đánh dấu là *khai báo*. Chỉ khi duyệt thấy định nghĩa thật trong source mới thành unit.
- **Kết quả:** 2302 → **1540 unit**. Constructor giảm 417 → 177, hàm tự do 492 → 205.

**Vấn đề 2: `access = invalid` cho hàm tự do** (không thuộc class). → để trống.

**Vấn đề 3: version Ceres hiện "unknown" trong báo cáo.**
- **Nguyên nhân:** `run_docker.sh` gọi `git describe` **sau** khi đặt `MSYS_NO_PATHCONV=1`. `git.exe` của Windows không hiểu đường dẫn kiểu `/e/Code/...` khi tắt chuyển đổi.
- **Xử lý:** lấy version trước dòng `export MSYS_NO_PATHCONV=1`.

---

## Bước 4 – Kiểm tra trên trình duyệt

**Vấn đề 4: trang `graph.html` trắng.**
- **Nguyên nhân:** console báo `Identifier 'top' has already been declared`. Biến `top` trùng với `window.top` có sẵn của trình duyệt.
- **Xử lý:** đổi tên biến.

**Vấn đề 5: tab "Kế thừa class" là 1 hàng ngang dài không đọc được.**
- **Nguyên nhân:** layout cây (breadthfirst) đặt ~200 cây nhỏ cạnh nhau. Phần lớn là cặp 1 cha – 1 con.
- **Xử lý:** đổi sang layout `cose` (tự gom cụm) + mặc định chỉ hiện class cha có ≥ 2 class con.

**Vấn đề 6 (quan trọng): số nhánh bị đếm sai với code nằm trong `#if` bị tắt.**
- **Phát hiện:** trong AST viewer, `GetBestSchurTemplateSpecialization` chỉ có 41 node, không có `if` nào, nhưng graph báo cyclomatic = 37.
- **Nguyên nhân:** build tắt `SCHUR_SPECIALIZATIONS` → định nghĩa `CERES_RESTRICT_SCHUR_SPECIALIZATION` → cả chuỗi `if` trong `#ifndef` bị preprocessor bỏ đi. Script đếm `&&`/`||` bằng **token** trên cả thân hàm, mà token thì vẫn có phần code bị bỏ.
- **Xử lý:** đếm `&&`/`||` trên node `BINARY_OPERATOR` của AST (chỉ có code thật được compile). Binding Python của libclang 18 không có thuộc tính lấy toán tử → lấy token ngay sau phần token của vế trái.
- **Kết quả:** tổng nhánh ước lượng 6064 → **5754**. `GetBestSchurTemplateSpecialization`, `PartitionedMatrixViewBase::Create`, `SchurEliminatorBase::Create` ra khỏi top phức tạp (đúng, vì code của chúng không được compile).
- **Bài học:** mọi số liệu phải lấy từ code **thật sự được compile**, giống cái gcov đo.

**Quan sát:** macro `CHECK(...)` của glog bung ra có `?:` → AST viewer tô đỏ dòng `CHECK` là điểm quyết định. gcov cũng tính nhánh này (nhánh "CHECK sai"). Phase 6 cần biết: muốn phủ nhánh này thì test phải làm `CHECK` sai → chương trình dừng → phải hook glog để gcov kịp ghi dữ liệu.

---

## Bước 5 – Chạy lại toàn bộ bằng `phase1.sh`

`scripts/run_docker.sh env JOBS=3 bash scripts/phase1.sh` → **PHASE 1 OK**, 9 phút 20 giây (chạy song song cùng lúc với đo baseline nên chậm hơn; chạy riêng ~6 phút).

### Kết quả

| Chỉ số | Giá trị |
|---|---|
| File `.cc` đã parse | 292 (lỗi: 0) |
| Node | 1540 unit trong phạm vi (9065 function kể cả test/khai báo), 1363 class, 480 file |
| Cạnh | CALLS 6696 · USES_TYPE 4751 · MEMBER_OF 4118 · INCLUDES 1326 · INHERITS 388 |
| Unit theo loại | method 871 · function template 212 · hàm tự do 205 · constructor 177 · destructor 75 |
| Nhánh ước lượng (AST) | 5754 |
| Unit không có nhánh nào | 846 (55%) – chỉ cần gọi được 1 lần là phủ hết |
| Unit lá (level 0) | 974 (63%) |
| Level cao nhất | 9 |
| Unit `static`/namespace ẩn danh | 80 – phải `#include "file.cc"` mới gọi được |
| Unit private/protected | 140 |
| Unit được test có sẵn gọi trực tiếp | 372 (24%) |
| Chu trình gọi (đệ quy) | 2, lớn nhất 4 hàm |
| Lời gọi không resolve được | 6922 (chủ yếu trong template) |

Số unit theo level: `0: 974 · 1: 264 · 2: 141 · 3: 82 · 4: 36 · 5: 20 · 6: 12 · 7: 4 · 8: 4 · 9: 3`

### Nhận xét cho các phase sau
- **Hơn một nửa unit không có nhánh** (846) và **63% là hàm lá** → phần lớn unit dễ, chỉ cần khởi tạo được input và gọi 1 lần. Công sức thật nằm ở ~700 unit có nhánh, đặc biệt nhóm phức tạp nhất (`LineSearchMinimizer::Minimize` cc=53, `Solver::Summary::FullReport` cc=44, `WolfeLineSearch::BracketingPhase` cc=31…).
- **Chỉ 24% unit được test có sẵn gọi trực tiếp** → 76% còn lại Phase 3 phải lấy test mẫu từ hàm "hàng xóm" (cùng class/cùng file).
- **Hàm được gọi nhiều nhất** (`StringPrintf`, `ResidualBlock::NumParameterBlocks`, `ParameterBlock::Size`…) là "nền móng" → làm sớm, helper khởi tạo `ResidualBlock`/`ParameterBlock`/`BlockSparseMatrix` sẽ dùng lại nhiều.

### Ví dụ gói context (đầu vào Phase 3)

`scripts/run_docker.sh python3 scripts/graph_query.py "ceres::internal::DoglegStrategy::ComputeStep"` cho ra:
- unit: `dogleg_strategy.cc:78–166`, nhánh≈26, cyclomatic 14, level 5, public
- class chứa: `DoglegStrategy`; kiểu dùng: `SparseMatrix`, `LinearSolver`, `TrustRegionStrategy::PerSolveOptions`…
- hàm gọi (hop 1): `ComputeGradient`, `ComputeCauchyPoint`, `ComputeGaussNewtonStep`, `ComputeSubspaceModel`…
- **6 test có sẵn** gọi trực tiếp (`DoglegStrategyFixtureEllipse_*`) → làm test mẫu
- header cần include: `dogleg_strategy.h`, `linear_solver.h`, `sparse_matrix.h`, `trust_region_strategy.h`

---

## Đầu ra

| File | Commit? | Nội dung |
|---|---|---|
| `reports/graph/summary.txt`, `stats.json` | có | thống kê ở trên |
| `reports/graph/graph.html` (~700 KB) | có | graph tương tác: khám phá unit, tổng quan file, kế thừa class, bảng unit |
| `reports/ast/ast.html` (~1.2 MB) | có | AST của 36 unit tiêu biểu, dạng cây + sơ đồ, tô điểm quyết định, đối chiếu source |
| `data/graph.db` (~10 MB) | không | sinh lại bằng `phase1.sh` |
| `logs/raw/phase1.log`, `build_graph.log` | có | log thô |
