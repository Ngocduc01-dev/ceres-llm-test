| | Lần 1 (nhóm) | Lần 2 (mới) |
|---|---|---|
| Số file | 217 | 205 |
| Dòng (C1) | 14338 / 20139 = **71.2%** | 11886 / 13846 = **85.8%** |
| Nhánh (C2) | 10285 / 21452 = **47.9%** | 8770 / 14745 = **59.5%** |
| Hàm | 7892 / 12424 = **63.5%** | 5267 / 5881 = **89.6%** |

**File chỉ có ở Lần 1 (nhóm): 12** – 5980 dòng, 6307 nhánh, 3569 hàm

| File | Dòng | Nhánh (phủ/tổng) | Hàm |
|---|---|---|---|
| `internal/ceres/gmock_gtest_all.cc` | 4618 | 813/4963 | 756 |
| `internal/ceres/gmock/gmock.h` | 857 | 245/596 | 2086 |
| `include/ceres/manifold_test_utils.h` | 175 | 163/340 | 680 |
| `internal/ceres/test_util.cc` | 55 | 22/142 | 5 |
| `internal/ceres/numeric_diff_test_utils.cc` | 103 | 57/93 | 8 |
| `internal/ceres/evaluator_test_utils.cc` | 24 | 35/68 | 1 |
| `internal/ceres/bundle_adjustment_test_util.h` | 82 | 33/67 | 13 |
| `internal/ceres/test_util.h` | 20 | 14/26 | 6 |

**File chỉ có ở Lần 2 (mới): 0** – 0 dòng, 0 nhánh, 0 hàm


**205 file chung:**

| | Lần 1 (nhóm) | Lần 2 (mới) |
|---|---|---|
| Dòng | 11994 / 14159 = 84.7% | 11886 / 13846 = 85.8% |
| Nhánh | 8891 / 15145 = 58.7% | 8770 / 14745 = 59.5% |
| Hàm | 5425 / 8855 = 61.3% | 5267 / 5881 = 89.6% |

**File chung lệch tổng số nhánh nhiều nhất:**

| File | Nhánh Lần 1 (nhóm) | Nhánh Lần 2 (mới) | Hàm Lần 1 (nhóm) | Hàm Lần 2 (mới) |
|---|---|---|---|---|
| `internal/ceres/partitioned_matrix_view.cc` | 47/153 | 5/18 | 2 | 2 |
| `internal/ceres/schur_eliminator.cc` | 52/153 | 5/18 | 2 | 2 |
| `internal/ceres/schur_templates.cc` | 41/114 | 0/0 | 1 | 1 |
| `internal/ceres/small_blas.h` | 149/307 | 145/279 | 215 | 70 |
| `internal/ceres/array_utils.cc` | 32/33 | 36/37 | 5 | 5 |
| `internal/ceres/schur_complement_solver.cc` | 108/218 | 108/222 | 15 | 15 |
| `internal/ceres/iterative_schur_complement_solver.cc` | 70/114 | 71/118 | 4 | 4 |
| `internal/ceres/residual_block.cc` | 76/88 | 77/89 | 3 | 3 |

**File chung lệch số nhánh được phủ nhiều nhất (cùng tổng thì lệch do test chạy khác):**

| File | Nhánh Lần 1 (nhóm) | Nhánh Lần 2 (mới) |
|---|---|---|
| `internal/ceres/schur_eliminator.cc` | 52/153 | 5/18 |
| `internal/ceres/partitioned_matrix_view.cc` | 47/153 | 5/18 |
| `internal/ceres/schur_templates.cc` | 41/114 | 0/0 |
| `internal/ceres/parallel_invoke.h` | 348/423 | 357/423 |
| `internal/ceres/array_utils.cc` | 32/33 | 36/37 |
| `internal/ceres/small_blas.h` | 149/307 | 145/279 |
| `internal/ceres/schur_eliminator_impl.h` | 187/228 | 185/227 |
| `internal/ceres/residual_block.cc` | 76/88 | 77/89 |
