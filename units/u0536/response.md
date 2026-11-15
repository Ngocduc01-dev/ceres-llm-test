**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 7 → END | node 1: sai |
| P2 | START → 1 → 2 → 3 → 7 → END | node 1: đúng, node 3: sai (0 lần lặp) |
| P3 | START → 1 → 2 → 3 → 4 → 6 → 3 → 7 → END | node 1: đúng, node 3: đúng rồi sai, node 4: sai (1 lần lặp) |
| P4 | START → 1 → 2 → (3 → 4 → 6) ×2 → 3 → 7 → END | như P3, 2 lần lặp |
| P5 | START → 1 → 2 → (3 → 4 → 6) ×3 → 3 → 7 → END | như P3, 3 lần lặp (số ở giữa) |
| P6 | START → 1 → 2 → (3 → 4 → 6) ×4 → 3 → 7 → END | như P3, 4 lần lặp (n−1) |
| P7 | START → 1 → 2 → (3 → 4 → 6) ×5 → 3 → 7 → END | như P3, 5 lần lặp (n) |
| P8 | START → 1 → 2 → 3 → 4 → 5 → END | node 1: đúng, node 3: đúng, node 4: đúng (do `!isfinite`), thoát bằng `return false` ở lần lặp 1 |
| P9 | START → 1 → 2 → (3 → 4 → 6) ×2 → 3 → 4 → 5 → END | node 4: sai 2 lần rồi đúng (do `== kImpossibleValue`), thoát bằng `return false` ở lần lặp 3 |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `x = nullptr`, `size` ∈ [1, 5] | `x = nullptr`, `size = 3` |
| TC2 | P2 | `x` khác null, `size = 0` | `x = {1.5}`, `size = 0` |
| TC3 | P3 | `size = 1`, `x[0]` hữu hạn và khác `kImpossibleValue` | `{1.5}` |
| TC4 | P4 | `size = 2`, mọi phần tử hữu hạn và khác `kImpossibleValue` | `{1.5, -2.25}` |
| TC5 | P5 | `size = 3`, như trên | `{1.5, -2.25, 3.75}` |
| TC6 | P6 | `size = 4`, như trên | `{1.5, -2.25, 3.75, 0.5}` |
| TC7 | P7 | `size = 5`, như trên | `{1.5, -2.25, 3.75, 0.5, 7.0}` |
| TC8 | P8 | `size` ∈ [1, 5], `x[0]` là NaN hoặc ±Inf | `size = 3`, `x = {NaN, 1.5, 2.5}` |
| TC9 | P9 | `size = 3`, `x[0]`, `x[1]` hữu hạn, `x[2] == kImpossibleValue` | `x = {1.5, -2.25, kImpossibleValue}` |

**C. Nhánh không test**

- Tổng số nhánh = 2 × 3 = 6 (node 1, node 3, node 4 mỗi node 2 nhánh). Cả 6 nhánh đều có test.
- Không có nhánh không thể đi tới và không có `CHECK`.
- Vòng lặp: không làm được **n+1** lần lặp. Thân vòng lặp tối đa chạy `size` lần, và nếu đặt `size` lớn hơn số phần tử mảng thì sẽ đọc ngoài vùng nhớ (hành vi không xác định).
- Các số lần lặp 0, 1, 2, 3, 4, 5 đều được test với n = 5 (mảng tối đa 5 phần tử). Hai cách thoát vòng lặp (điều kiện sai, `return false`) đều được test.

`C2 dự kiến = 6 / 6`

**D. File test**

```cpp
// FILE: u0536_test.cc
#include <cmath>
#include <cstdint>
#include <limits>

#include "ceres/array_utils.h"
#include "gtest/gtest.h"

namespace ceres {
namespace internal {

// Path P1: node 1: sai (x == nullptr)
TEST(IsArrayValidTest, NullArray) {
  const double* x = nullptr;
  const int64_t size = 3;
  IsArrayValid(size, x);
}

// Path P2: node 1: đúng, node 3: sai (0 lần lặp)
TEST(IsArrayValidTest, ZeroIterations) {
  const double x[1] = {1.5};
  const int64_t size = 0;
  IsArrayValid(size, x);
}

// Path P3: node 1: đúng, node 3: đúng rồi sai, node 4: sai (1 lần lặp)
TEST(IsArrayValidTest, OneIteration) {
  const double x[1] = {1.5};
  const int64_t size = 1;
  IsArrayValid(size, x);
}

// Path P4: như P3, 2 lần lặp
TEST(IsArrayValidTest, TwoIterations) {
  const double x[2] = {1.5, -2.25};
  const int64_t size = 2;
  IsArrayValid(size, x);
}

// Path P5: như P3, 3 lần lặp (số ở giữa)
TEST(IsArrayValidTest, ThreeIterations) {
  const double x[3] = {1.5, -2.25, 3.75};
  const int64_t size = 3;
  IsArrayValid(size, x);
}

// Path P6: như P3, 4 lần lặp (n-1)
TEST(IsArrayValidTest, FourIterations) {
  const double x[4] = {1.5, -2.25, 3.75, 0.5};
  const int64_t size = 4;
  IsArrayValid(size, x);
}

// Path P7: như P3, 5 lần lặp (n)
TEST(IsArrayValidTest, FiveIterations) {
  const double x[5] = {1.5, -2.25, 3.75, 0.5, 7.0};
  const int64_t size = 5;
  IsArrayValid(size, x);
}

// Path P8: node 1: đúng, node 3: đúng, node 4: đúng (!isfinite), return false ở lần lặp 1
TEST(IsArrayValidTest, NonFiniteAtFirstElement) {
  const double x[3] = {std::numeric_limits<double>::quiet_NaN(), 1.5, 2.5};
  const int64_t size = 3;
  IsArrayValid(size, x);
}

// Path P9: node 4: sai 2 lần rồi đúng (== kImpossibleValue), return false ở lần lặp 3
TEST(IsArrayValidTest, ImpossibleValueAtThirdElement) {
  const double x[3] = {1.5, -2.25, kImpossibleValue};
  const int64_t size = 3;
  IsArrayValid(size, x);
}

}  // namespace internal
}  // namespace ceres
```