**A. Test paths**

Có 3 điểm rẽ nhánh (node 1, 4, 5), tổng cộng 6 nhánh. CFG khớp với mã nguồn.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | node 1: đúng |
| P2 | START → 1 → 3 → 4 → 8 → END | node 1: sai, node 4: sai (0 lần lặp) |
| P3 | START → 1 → 3 → (4 → 5 → 7) × k → 4 → 8 → END, với k = 1, 2, 3, 4, 5 | node 1: sai, node 4: đúng (k lần) rồi sai, node 5: sai (k lần) |
| P4 | START → 1 → 3 → 4 → 5 → 6 → END | node 1: sai, node 4: đúng, node 5: đúng (do `!isfinite`, trả về ngay ở lần lặp đầu) |
| P5 | START → 1 → 3 → (4 → 5 → 7) × 2 → 4 → 5 → 6 → END | node 4: đúng, node 5: sai ở 2 lần đầu, đúng ở lần 3 (do `!isfinite`) |
| P6 | START → 1 → 3 → (4 → 5 → 7) × 4 → 4 → 5 → 6 → END | node 5: đúng ở lần 5 (do `x[i] == kImpossibleValue`, thoát ở phần tử cuối) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `x == nullptr`, size ∈ [0, 5] | x = nullptr, size = 3 |
| TC2 | P2 | x khác null, size = 0 | x = {7.0}, size = 0 |
| TC3 | P3 (k=1) | size = 1, phần tử hữu hạn, khác 1e302 (∈ [-10, 10]) | {2.5}, size = 1 |
| TC4 | P3 (k=2) | size = 2, các phần tử hữu hạn | {-3.0, 4.5}, size = 2 |
| TC5 | P3 (k=3, giá trị giữa) | size = 3, các phần tử hữu hạn | {1.5, -6.0, 8.0}, size = 3 |
| TC6 | P3 (k=4, n−1) | size = 4, các phần tử hữu hạn | {0.5, -1.0, 9.0, -7.5}, size = 4 |
| TC7 | P3 (k=5, n) | size = 5, các phần tử hữu hạn | {3.0, -2.0, 6.5, -4.0, 1.0}, size = 5 |
| TC8 | P4 | size ∈ [1, 5], x[0] là NaN | {NaN, 1.0, 2.0}, size = 3 |
| TC9 | P5 | size ∈ [3, 5], x[0], x[1] hữu hạn, x[2] là vô cực | {1.0, -2.0, +inf, 5.0}, size = 4 |
| TC10 | P6 | size = 5, x[0..3] hữu hạn, x[4] = 1e302 | {1.0, 2.0, -3.0, 4.0, 1e302}, size = 5 |

Ghi chú: n+1 lần lặp không làm được vì vòng lặp có điều kiện `i < size`, nên số lần lặp tối đa bằng `size`. Các giá trị ở trên là cố định, không dùng hàm sinh số ngẫu nhiên, nên mỗi lần chạy cho cùng kết quả.

**C. Nhánh không test**

Không có nhánh nào không đi tới được. Hàm không có `CHECK`.

`C2 dự kiến = 6 / 6`

**D. File test**

```cpp
// FILE: u0537_test.cc
#include <cstdint>
#include <limits>

#include "ceres/array_utils.h"
#include "gtest/gtest.h"

namespace ceres {
namespace internal {

// P1: node 1: đúng -> node 2 -> END
TEST(FindInvalidValueTest, TC1_NullPointer) {
  FindInvalidValue(3, nullptr);
}

// P2: node 1: sai, node 4: sai (0 lần lặp)
TEST(FindInvalidValueTest, TC2_ZeroIterations) {
  const double x[] = {7.0};
  FindInvalidValue(0, x);
}

// P3 (k=1): node 1: sai, node 4: đúng 1 lần rồi sai, node 5: sai
TEST(FindInvalidValueTest, TC3_OneIteration) {
  const double x[] = {2.5};
  FindInvalidValue(1, x);
}

// P3 (k=2): node 1: sai, node 4: đúng 2 lần rồi sai, node 5: sai
TEST(FindInvalidValueTest, TC4_TwoIterations) {
  const double x[] = {-3.0, 4.5};
  FindInvalidValue(2, x);
}

// P3 (k=3): node 1: sai, node 4: đúng 3 lần rồi sai, node 5: sai
TEST(FindInvalidValueTest, TC5_MiddleIterations) {
  const double x[] = {1.5, -6.0, 8.0};
  FindInvalidValue(3, x);
}

// P3 (k=4): node 1: sai, node 4: đúng 4 lần rồi sai, node 5: sai
TEST(FindInvalidValueTest, TC6_NMinusOneIterations) {
  const double x[] = {0.5, -1.0, 9.0, -7.5};
  FindInvalidValue(4, x);
}

// P3 (k=5): node 1: sai, node 4: đúng 5 lần rồi sai, node 5: sai
TEST(FindInvalidValueTest, TC7_NIterations) {
  const double x[] = {3.0, -2.0, 6.5, -4.0, 1.0};
  FindInvalidValue(5, x);
}

// P4: node 1: sai, node 4: đúng, node 5: đúng (NaN ở phần tử đầu)
TEST(FindInvalidValueTest, TC8_NaNAtFirstElement) {
  const double x[] = {std::numeric_limits<double>::quiet_NaN(), 1.0, 2.0};
  FindInvalidValue(3, x);
}

// P5: node 1: sai, node 4: đúng, node 5: sai, sai, đúng (vô cực ở index 2)
TEST(FindInvalidValueTest, TC9_InfinityAtThirdElement) {
  const double x[] = {1.0, -2.0, std::numeric_limits<double>::infinity(), 5.0};
  FindInvalidValue(4, x);
}

// P6: node 1: sai, node 4: đúng, node 5: đúng ở lần 5 (x[i] == 1e302, tức kImpossibleValue)
TEST(FindInvalidValueTest, TC10_ImpossibleValueAtLastElement) {
  const double x[] = {1.0, 2.0, -3.0, 4.0, 1e302};
  FindInvalidValue(5, x);
}

}  // namespace internal
}  // namespace ceres
```

Lưu ý: TC10 dùng trực tiếp giá trị `1e302`, là giá trị của `kImpossibleValue` theo mã nguồn Ceres 2.2.0. Tôi dùng literal để tránh phụ thuộc vào việc hằng này có được khai báo trong header hay không. Tôi chưa build hay chạy bộ test này.