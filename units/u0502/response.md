**A. Test paths**

Có 2 điểm rẽ nhánh (node 1 và node 3), tổng cộng 4 nhánh. CFG khớp với mã nguồn.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | node 1: sai |
| P2 | START → 1 → 2 → 3 → END | node 1: đúng, node 3: sai (0 lần lặp) |
| P3 | START → 1 → 2 → 3 → 4 → 5 → 3 → END | node 1: đúng, node 3: đúng 1 lần rồi sai (1 lần lặp) |
| P4 | START → 1 → 2 → (3 → 4 → 5) ×2 → 3 → END | node 1: đúng, node 3: đúng 2 lần rồi sai (2 lần lặp) |
| P5 | START → 1 → 2 → (3 → 4 → 5) ×3 → 3 → END | node 1: đúng, node 3: đúng 3 lần rồi sai (số lần lặp ở giữa) |
| P6 | START → 1 → 2 → (3 → 4 → 5) ×4 → 3 → END | node 1: đúng, node 3: đúng 4 lần rồi sai (n−1 lần lặp) |
| P7 | START → 1 → 2 → (3 → 4 → 5) ×5 → 3 → END | node 1: đúng, node 3: đúng 5 lần rồi sai (n lần lặp) |

**B. Bộ test case**

Vòng lặp có giới hạn n = size, với size tối đa là 5 do mảng tối đa 5 phần tử.

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | x = nullptr; size ∈ [1, 5] | x = nullptr, size = 3 |
| TC2 | P2 | x ≠ nullptr; size ≤ 0 (chọn size = 0) | x = mảng 5 phần tử, size = 0 |
| TC3 | P3 | x ≠ nullptr; size = 1 | size = 1 |
| TC4 | P4 | x ≠ nullptr; size = 2 | size = 2 |
| TC5 | P5 | x ≠ nullptr; size ∈ [3, 3] (giá trị ở giữa) | size = 3 |
| TC6 | P6 | x ≠ nullptr; size = 4 | size = 4 |
| TC7 | P7 | x ≠ nullptr; size = 5 | size = 5 |

**C. Nhánh không test**

- Không có nhánh nào không thể đi tới và không có `CHECK`.
- Số lần lặp n+1 (size = 6) không làm được. Mảng tối đa 5 phần tử, nên size = 6 sẽ ghi ra ngoài vùng nhớ của mảng (hành vi không xác định).
- C2 dự kiến = 4 / 4

**D. File test**

```cpp
// FILE: u0502_test.cc
#include "gtest/gtest.h"
#include "ceres/array_utils.h"

#include <cstdint>

namespace ceres {
namespace internal {

// P1: node 1: sai (x == nullptr)
TEST(InvalidateArrayTest, TC1_NullPointer) {
  const int64_t size = 3;
  InvalidateArray(size, nullptr);
}

// P2: node 1: đúng, node 3: sai ngay (0 lần lặp)
TEST(InvalidateArrayTest, TC2_ZeroIterations) {
  double x[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  const int64_t size = 0;
  InvalidateArray(size, x);
}

// P3: node 1: đúng, node 3: đúng 1 lần rồi sai (1 lần lặp)
TEST(InvalidateArrayTest, TC3_OneIteration) {
  double x[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  const int64_t size = 1;
  InvalidateArray(size, x);
}

// P4: node 1: đúng, node 3: đúng 2 lần rồi sai (2 lần lặp)
TEST(InvalidateArrayTest, TC4_TwoIterations) {
  double x[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  const int64_t size = 2;
  InvalidateArray(size, x);
}

// P5: node 1: đúng, node 3: đúng 3 lần rồi sai (số lần lặp ở giữa)
TEST(InvalidateArrayTest, TC5_MiddleIterations) {
  double x[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  const int64_t size = 3;
  InvalidateArray(size, x);
}

// P6: node 1: đúng, node 3: đúng 4 lần rồi sai (n-1 lần lặp)
TEST(InvalidateArrayTest, TC6_NMinusOneIterations) {
  double x[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  const int64_t size = 4;
  InvalidateArray(size, x);
}

// P7: node 1: đúng, node 3: đúng 5 lần rồi sai (n lần lặp)
TEST(InvalidateArrayTest, TC7_NIterations) {
  double x[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  const int64_t size = 5;
  InvalidateArray(size, x);
}

}  // namespace internal
}  // namespace ceres
```