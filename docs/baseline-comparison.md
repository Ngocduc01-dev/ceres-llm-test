# So sánh các kết quả baseline coverage (Ceres 2.2.0)

Kết quả đo độ phủ của **test có sẵn** của Ceres 2.2.0, giữa lần đo đầu tiên của nhóm (lần 1) và lần làm lại (lần 2):

| | Lần 1 – nhóm (`reports/archive/baseline-2.2.0-lan1/`) | Lần 2 – làm lại (`reports/baseline/`) |
|---|---|---|
| Ceres | 2.2.0 | 2.2.0 |
| Compiler | GCC 13 | GCC 14 |
| `SCHUR_SPECIALIZATIONS` | ON (mặc định) | OFF |
| Bộ lọc gcovr | bỏ `*_test.cc`, `generated/` | bỏ thêm googletest/gmock và file hỗ trợ test |
| Số file được tính | 217 | 205 |
| Phủ dòng (C1) | 71.2% (14338 / 20139) | **85.8%** (11886 / 13846) |
| **Phủ nhánh (C2)** | 47.9% (10285 / 21452) | **59.5%** (8770 / 14745) |
| Phủ hàm | 63.5% (7892 / 12424) | 89.6% (5267 / 5881) |

## Kết luận: hai lần đo KHỚP nhau, chỉ khác bộ lọc

Lấy dữ liệu lần 2 rồi chạy gcovr với **đúng bộ lọc của lần 1** (`logs/raw/lan2_voi_bo_loc_lan1.json`):

| | Lần 1 | Lần 2, dùng bộ lọc lần 1 | Chênh |
|---|---|---|---|
| Phủ dòng (C1) | 71.2% | 71.6% | +0.4 |
| **Phủ nhánh (C2)** | **47.9%** | **48.3%** | **+0.4** |

→ Cùng phiên bản, cùng bộ lọc thì **chỉ lệch 0.4 điểm**. Con số 59.5% của lần 2 cao hơn **chỉ vì bộ lọc khác**, không phải vì đo khác.

Chi tiết từng file: `logs/raw/compare_cung_bo_loc.md` (cùng bộ lọc), `logs/raw/compare_lan1_lan2.md` (bộ lọc riêng của mỗi lần).

---

## Vì sao bộ lọc làm % thay đổi nhiều như vậy (47.9% → 59.5%)

Ceres 2.2.0 để sẵn **toàn bộ googletest** ngay trong `internal/ceres/`. Bộ lọc lần 1 chỉ bỏ `*_test.cc`, nên 12 file không phải code Ceres lọt vào: **5980 dòng, 6307 nhánh, 3569 hàm**:

| File | Dòng | Nhánh (phủ / tổng) | Là gì |
|---|---|---|---|
| `internal/ceres/gmock_gtest_all.cc` | 4618 | 813 / 4963 | toàn bộ googletest gộp 1 file |
| `internal/ceres/gmock/gmock.h` | 857 | 245 / 596 | header gmock |
| `include/ceres/manifold_test_utils.h` | 175 | 163 / 340 | hàm hỗ trợ viết test |
| `internal/ceres/test_util.cc`, `numeric_diff_test_utils.cc`, `evaluator_test_utils.cc`, `bundle_adjustment_test_util.h`, `test_util.h`, `tiny_solver_test_util.h`, `gmock/mock-log.h` | 310 | 172 / 407 | hàm hỗ trợ viết test |

- Test chỉ dùng một phần nhỏ googletest → riêng `gmock_gtest_all.cc` có **~4150 nhánh không bao giờ phủ**, kéo % tụt mạnh.
- Đây không phải code cần kiểm thử (bài toán là sinh test cho **code của Ceres**), nên lần 2 loại ra.

**Nếu chỉ so trên 205 file chung** (bỏ 12 file trên): lần 1 = **58.7%**, lần 2 = **59.5%**.

---

## Phần lệch nhỏ còn lại (~0.4–0.8 điểm)

### 1. `SCHUR_SPECIALIZATIONS` ON (lần 1) vs OFF (lần 2)
Bật thì Ceres compile thêm các bản template cho từng kích thước ma trận cố định, và các hàm chọn bản template có thêm hàng chục nhánh:

| File | Nhánh lần 1 | Nhánh lần 2 |
|---|---|---|
| `internal/ceres/schur_eliminator.cc` | 52 / 153 | 5 / 18 |
| `internal/ceres/partitioned_matrix_view.cc` | 47 / 153 | 5 / 18 |
| `internal/ceres/schur_templates.cc` | 41 / 114 | 0 / 0 (code nằm trong `#ifndef`, bị tắt) |
| `internal/ceres/small_blas.h` | 149 / 307 (215 hàm) | 145 / 279 (70 hàm) |
| `internal/ceres/schur_eliminator_impl.h` | 187 / 228 (286 hàm) | 185 / 227 (13 hàm) |

Đây cũng là lý do chính khiến **số hàm** khác nhau nhiều (gcov đếm mỗi bản instantiate template là 1 hàm).

**Vì sao lần 2 tắt:** code của các bản template nằm trong `internal/ceres/generated/` (vốn đã loại khỏi phạm vi). Bật lên chỉ làm build lâu hơn và làm phình số nhánh của vài hàm "chọn bản template", không thêm code thật cần test.

### 2. GCC 13 vs GCC 14
Cùng một dòng `if`, mỗi version GCC có thể sinh số nhánh hơi khác nhau. Ví dụ `array_utils.cc`: 32/33 (GCC 13) và 36/37 (GCC 14). Ảnh hưởng tổng nhỏ.

GCC 14 + gcovr 7.0 còn **không đọc được** output gcov của `gmock_gtest_all.cc` (lỗi `UnknownLineType`). Bộ lọc lần 2 vốn loại file này nên không bị ảnh hưởng; khi đo lại bằng bộ lọc lần 1 phải bật `--gcov-ignore-parse-errors=all`.

### 3. `-fprofile-update=atomic` (chỉ lần 2)
Lần 2 compile với bộ đếm atomic → không bị lỗi "bộ đếm âm" khi test chạy đa luồng. Không làm đổi độ phủ đáng kể, nhưng làm test chạy **chậm hơn nhiều** (test bundle adjustment 15–20 phút/test).

---

## Về 20 test bị timeout ở lần 2

Lần chạy đầu của lần 2, 20 test bundle adjustment (`ba_*_user_test`, `ba_*_threads_test`…) vượt timeout 1200 giây. Đã chạy lại riêng 20 test đó (không giới hạn thời gian, giữ dữ liệu cũ): **20/20 PASS, độ phủ không đổi** (vẫn 59.5%). Lý do: chúng là biến thể (bản `user`, bản `threads`) của các test bundle adjustment khác đã chạy xong, đi qua cùng đoạn code → không phủ thêm nhánh mới.

---

## Đề xuất (đã áp dụng ở lần 2)

1. **Chốt bộ lọc phạm vi**: chỉ đo code Ceres – bỏ `*_test.cc`, `generated/`, googletest/gmock, file hỗ trợ test (`*test_util*`). Dùng chung cho mọi lần đo về sau (Phase 6, 8) để so sánh được.
2. **Mọi báo cáo ghi kèm**: phiên bản Ceres, version compiler, option CMake, bộ lọc gcovr.
3. **Baseline chính thức của nhóm: C1 = 85.8%, C2 = 59.5%** (Ceres 2.2.0, GCC 14, bộ lọc ở trên). Còn **5975 nhánh chưa phủ** – đây là mục tiêu của test sinh tự động.

---

## Phụ lục: lần thử trên bản phát triển `e831bfef`

Trước khi nhóm chốt 2.2.0, đã thử đo trên `e831bfef` (2.2.0 + 286 commit, dùng Abseil thay glog): C1 86.9%, C2 64.3%. Kết quả giữ ở `reports/archive/baseline-e831bfef/` để tham khảo; không dùng để so sánh vì khác phiên bản code.
