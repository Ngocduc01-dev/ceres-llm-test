# Phase 6 – Compile, chạy, đo phủ (lượt 1)

Lượt 1 **chưa sửa gì**: compile, chạy và đo phủ đúng file test LLM sinh ra, rồi ghi lại lỗi để thống kê.

## Chạy

Cần build Ceres bản coverage trong Docker volume (`scripts/build.sh`, Phase 0).

```bash
MSYS_NO_PATHCONV=1 scripts/run_docker.sh python3 scripts/phase6.py --smoke
MSYS_NO_PATHCONV=1 scripts/run_docker.sh python3 scripts/phase6.py --ids u0540 u0541 --keep   # giữ thư mục build để soát
MSYS_NO_PATHCONV=1 scripts/run_docker.sh python3 scripts/phase6.py -j 4                      # mọi unit đã có file test
MSYS_NO_PATHCONV=1 scripts/run_docker.sh python3 scripts/phase6.py --report-only                # chỉ dựng lại báo cáo
```

`-j`: số unit làm song song. Máy 8 GB RAM thì để 4 (compile Eigen tốn khoảng 1 GB mỗi unit).

## Các bước cho mỗi unit

1. **Compile** `units/<id>/<id>_test.cc`:
   - dùng cùng cờ với test có sẵn của Ceres (lấy từ `compile_commands.json`), có `--coverage -O0`;
   - link với `libceres-debug.a`, `libgtest-debug.a`, `libtest_util-debug.a`, glog, gflags.
2. **Hàm `main` riêng** – [scripts/phase6_main.cc](../scripts/phase6_main.cc), không dùng `gmock_main`. Nếu `CHECK` sai, segfault hoặc bị timeout, chương trình gọi `__gcov_dump()` trước khi thoát, nên **không mất số liệu phủ**. Mã thoát cho biết lý do:
   - `134` = `CHECK` sai
   - `139` = segfault
   - `143` hoặc `124` = timeout
3. **Chạy từng test riêng** (`--gtest_filter=<Suite>.<Test>`):
   - timeout 10 giây/test, để một test crash không kéo theo các test sau;
   - kết quả của từng test: `pass` / `fail` / `check_fail` / `crash` / `timeout`, loại nào cũng chấp nhận.
4. **Số liệu gcov của mỗi unit ghi vào thư mục riêng** (`GCOV_PREFIX`), nên chạy song song được và không lẫn với unit khác.
5. **Đo phủ** bằng gcovr và **chỉ lấy các dòng của unit**. Hàm inline trong header có thể nằm ở nhiều file object; số liệu được cộng dồn theo dòng.

## Cách tính

| Chỉ số | Cách tính |
|---|---|
| C1 | số dòng code của unit đã chạy / tổng số dòng code của unit |
| C2 | số nhánh đã đi / tổng số nhánh, **đếm theo điểm rẽ nhánh như CFG Phase 4** |

Cách đếm nhánh ở C2 (dùng `gcovr --decisions`):
- `if`, `for`, `while`, `do-while`, `?:` là 1 điểm rẽ nhánh với 2 nhánh (đúng, sai), kể cả khi điều kiện là `a && b`;
- `switch`: mỗi `case` là 1 nhánh;
- **không** tính các dòng thuộc lệnh `CHECK` / `DCHECK` / `LOG(FATAL)`, kể cả phần `<< "..."` viết tiếp ở dòng sau.

Chỉ dùng **một** loại nhánh này. Số nhánh "thô" của gcov (tách `a && b` thành nhiều nhánh mã máy) không dùng ở đâu cả. Trang HTML cũng hiện số theo điểm rẽ nhánh ở cột **Branches**.

**Hai trường hợp gcovr không tự nhận ra**, script tự suy ra (đếm vào `c2.inferred` trong `result.json`):
- `if (...) {` mà ở `-O0` gcov gắn nhánh sang dòng `}` (ví dụ destructor u0436):
  - nhánh đúng = số lần chạy dòng code đầu tiên trong thân;
  - nhánh sai = số lần chạy dòng `if` trừ nhánh đúng.
- `?:` trên một dòng mà gcov có đúng 2 nhánh (ví dụ u0482): mỗi nhánh gcov là một nhánh của điểm rẽ nhánh.

Điểm rẽ nhánh vẫn không đo được thì ghi vào `c2.uncheckable` và không tính vào C2.

## Đầu ra

| File | Nội dung |
|---|---|
| `units/<id>/result.json` | `status`, kết quả từng test, `run` (đếm pass/fail/…), `c1`, `c2`, `uncovered` (dòng còn nhánh chưa đi), `cfg_branches` |
| `units/<id>/coverage.json` | số liệu phủ của unit (JSON của gcovr, chỉ các dòng của unit) |
| `units/<id>/compile.log` | log lỗi compile/link, chỉ có khi lỗi |
| `reports/phase6/summary.md`, `summary.csv` | bảng tổng hợp **mọi** unit đã chạy Phase 6 |
| `reports/phase6/gen_coverage.html` | **trang tổng quan độ phủ** theo từng file, cùng kiểu với `reports/baseline/index.html` (commit) |
| `reports/phase6/html/gen_coverage.html` | bản có trang chi tiết từng file: tô màu từng dòng, số nhánh ở mỗi dòng (không commit, sinh lại bằng `--report-only`) |

Các giá trị `status`:

| `status` | Ý nghĩa |
|---|---|
| `ok` | compile và chạy được (test có thể fail hoặc crash, vẫn đo phủ) |
| `compile_fail` / `link_fail` | lỗi compile hoặc link |
| `no_tests` | file test không có `TEST` nào |
| `coverage_fail` | gcovr lỗi |
