# ceres-llm-test

Sinh unit test tự động bằng LLM cho [Ceres Solver](https://github.com/ceres-solver/ceres-solver) **release 2.2.0** (~100k dòng C++17), theo **kiểm thử dòng điều khiển (CFT), tiêu chí phủ nhánh C2**. Không có đặc tả nên không có expected output: test chỉ cần chạy được, không quan tâm PASS/FAIL, đánh giá bằng **độ phủ**.

Kế hoạch tổng thể 9 phase và phân công: [docs/PLAN.md](docs/PLAN.md)

## Trạng thái

| Phase | Nội dung | Trạng thái |
|---|---|---|
| 0 | Môi trường Docker, build có coverage, baseline, parse thử | ✅ [hướng dẫn](docs/phase0-guide.md) · [nhật ký](logs/phase0-log.md) · [so khớp baseline](docs/baseline-comparison.md) |
| 1 | Code graph + AST | ✅ [hướng dẫn](docs/phase1-guide.md) · [nhật ký](logs/phase1-log.md) |
| 2 | Liệt kê & phân loại unit | ⏳ |
| 3 | Gom context cho LLM | ⏳ (đã có `Graph.context()` trong `scripts/graph_query.py`) |
| 4 | Lập kế hoạch nhánh (C2) | ⏳ |
| 5 | Sinh test | ⏳ |
| 6 | Compile / chạy / vòng lặp phủ nhánh | ⏳ |
| 7 | Hậu xử lý | ⏳ |
| 8 | Chạy hàng loạt, báo cáo | ⏳ |

## Kết quả

**Phase 0 – baseline của test có sẵn** (Ceres 2.2.0, GCC 14) · trang xem: [reports/baseline/index.html](reports/baseline/index.html)

| Chỉ số | Giá trị |
|---|---|
| Test có sẵn | 175 / 175 PASS |
| Phủ dòng (C1) | 85.8% (11886 / 13846) |
| **Phủ nhánh (C2)** | **59.5% (8770 / 14745)** → còn **5975 nhánh** chưa phủ |
| Khớp với lần đo đầu của nhóm? | ✅ cùng bộ lọc: 48.3% vs 47.9% ([vì sao 2 con số khác nhau](docs/baseline-comparison.md)) |

**Phase 1 – code graph** · trang xem: [reports/graph/graph.html](reports/graph/graph.html), [reports/ast/ast.html](reports/ast/ast.html)

| Chỉ số | Giá trị |
|---|---|
| File `.cc` parse bằng libclang | 292 / 292 không lỗi |
| Unit (hàm/method có thân, trong phạm vi) | **1540** |
| Cạnh gọi hàm / dùng kiểu / kế thừa | 6696 / 4751 / 388 |
| Unit không có nhánh · unit lá (level 0) | 846 · 974 |
| Unit được test có sẵn gọi trực tiếp | 372 |
| Unit `static`/namespace ẩn danh · private/protected | 80 · 140 |

## Chạy

Cần: Docker Desktop (8 GB RAM trở lên), Git Bash (Windows) hoặc bash.

```bash
git clone --recursive https://github.com/Ngocduc01-dev/ceres-llm-test.git
cd ceres-llm-test
docker build -t ceres-testgen:phase0 docker                              # ~2 phút
scripts/run_docker.sh env JOBS=4 bash scripts/build.sh                   # Phase 0: build, ~10 phút
scripts/run_docker.sh env JOBS=14 bash scripts/coverage.sh               # Phase 0: baseline, ~1–1.5 tiếng
scripts/run_docker.sh env JOBS=4 python3 scripts/parse_check.py          # Phase 0: parse thử, ~8 phút
scripts/run_docker.sh env JOBS=4 bash scripts/phase1.sh                  # Phase 1: graph + HTML, ~6–9 phút
scripts/run_docker.sh python3 scripts/graph_query.py ComputeStep         # tra cứu 1 unit
```

## Cấu trúc thư mục

```
ceres-llm-test/
├── ceres-solver/                  # submodule Ceres, chốt tag 2.2.0 (không sửa bên trong)
├── docker/Dockerfile              # Ubuntu 24.04, GCC 14, glog, gflags, CMake, Ninja, gcovr, Clang 18 + libclang
├── scripts/
│   ├── run_docker.sh              # chạy 1 lệnh trong container
│   ├── build.sh                   # [P0] build Ceres có --coverage, xuất compile_commands.json
│   ├── coverage.sh                # [P0] chạy test có sẵn + gcovr (SKIP_TESTS=1 / RERUN_FAILED=1)
│   ├── parse_check.py             # [P0] parse toàn bộ source bằng libclang, đếm unit
│   ├── compare_baseline.py        # so sánh 2 báo cáo độ phủ theo từng file
│   ├── phase1.sh                  # [P1] chạy cả 3 bước dưới
│   ├── build_graph.py             # [P1] dựng code graph -> data/graph.db
│   ├── graph_query.py             # [P1] tra cứu graph, gói context cho Phase 3
│   ├── viz_graph.py               # [P1] -> reports/graph/graph.html
│   ├── ast_export.py              # [P1] -> reports/ast/ast.html
│   └── templates/                 # khung HTML của 2 trang trên
├── docs/                          # PLAN, hướng dẫn từng phase, so khớp baseline
├── reports/
│   ├── baseline/                  # [P0] độ phủ chính thức: index.html, summary, coverage.json (từng nhánh)
│   ├── parse/                     # [P0] kết quả parse
│   ├── graph/                     # [P1] graph.html, summary.txt, stats.json
│   ├── ast/                       # [P1] ast.html
│   └── archive/                   # các lần đo trước (lần 1 của nhóm, bản thử e831bfef)
├── logs/                          # nhật ký từng phase + raw/ (log thô từng lệnh)
└── data/                          # sinh ra khi chạy, không commit (compile_commands.json, graph.db)
```
