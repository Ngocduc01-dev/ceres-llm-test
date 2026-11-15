**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh, 0 nhánh). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | num_parameters: 1..5; max_num_corrections: 1..5; use_approximate_eigenvalue_scaling: true/false (không ảnh hưởng đường đi) | num_parameters = 4; max_num_corrections = 3; use_approximate_eigenvalue_scaling = true |

**C. Nhánh không test**

Không có. Hàm không có nhánh nào, không có vòng lặp và không có `CHECK`.
C2 dự kiến = 0 / 0 (không có nhánh; unit được chạy qua toàn bộ node 1, tương đương 100% câu lệnh).

**D. File test**

```cpp
// FILE: u0337_test.cc
#include "gtest/gtest.h"
#include "ceres/low_rank_inverse_hessian.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(LowRankInverseHessianConstructorTest, TC1_SinglePath) {
  const int num_parameters = 4;          // khoảng 1..5
  const int max_num_corrections = 3;     // khoảng 1..5
  const bool use_approximate_eigenvalue_scaling = true;
  ceres::internal::LowRankInverseHessian hessian(
      num_parameters, max_num_corrections, use_approximate_eigenvalue_scaling);
  (void)hessian;
}
```