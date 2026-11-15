**A. Test paths**

Tổng số nhánh = 2 × 1 = 2 (node 2: đúng, node 2: sai). Gọi k là số lần lặp, bằng `size()` của mảng.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | node 2: sai (k = 0) |
| P2 | START → 1 → 2 → 3 → 4 → 2 → END | node 2: đúng, rồi sai (k = 1) |
| P3 | START → 1 → (2 → 3 → 4) × 2 → 2 → END | node 2: đúng, đúng, rồi sai (k = 2) |
| P4 | START → 1 → (2 → 3 → 4) × 3 → 2 → END | node 2: đúng × 3, rồi sai (k = 3, số ở giữa) |
| P5 | START → 1 → (2 → 3 → 4) × 4 → 2 → END | node 2: đúng × 4, rồi sai (k = 4, n−1) |
| P6 | START → 1 → (2 → 3 → 4) × 5 → 2 → END | node 2: đúng × 5, rồi sai (k = 5, n) |

**B. Bộ test case**

Số lần lặp bị chặn bởi quy tắc "mảng tối đa 5 phần tử", nên n = 5.

| Test | Path | Khoảng giá trị đầu vào (`size`) | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | đúng 0 | 0 |
| TC2 | P2 | đúng 1 | 1 |
| TC3 | P3 | đúng 2 | 2 |
| TC4 | P4 | đúng 3 (nằm giữa 2 và 4) | 3 |
| TC5 | P5 | đúng 4 | 4 |
| TC6 | P6 | đúng 5 | 5 |

Mỗi khoảng chỉ chứa một giá trị nên không cần sinh ngẫu nhiên, và kết quả cố định giữa các lần chạy.

**C. Nhánh không test**

- Không có nhánh không thể đi tới và không có `CHECK`.
- Số lần lặp n+1 (6 lần) không làm được, vì vượt giới hạn 5 phần tử của yêu cầu.
- Vòng lặp trong destructor luôn kết thúc bằng điều kiện sai ở node 2, không có `break` hay `return`.
- Ghi chú: CFG khớp với mã nguồn.

`C2 dự kiến = 2 / 2`

**D. File test**

```cpp
// FILE: u0448_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

namespace ceres {
namespace internal {

using IntFixedArray = FixedArray<int, 20>;

// P1: START -> 1 -> 2 (sai) -> END ; k = 0
TEST(FixedArrayDestructorTest, ZeroIterations) {
  {
    IntFixedArray arr(0, IntFixedArray::allocator_type());
  }
}

// P2: node 2: đúng, sai ; k = 1
TEST(FixedArrayDestructorTest, OneIteration) {
  {
    IntFixedArray arr(1, IntFixedArray::allocator_type());
  }
}

// P3: node 2: đúng, đúng, sai ; k = 2
TEST(FixedArrayDestructorTest, TwoIterations) {
  {
    IntFixedArray arr(2, IntFixedArray::allocator_type());
  }
}

// P4: node 2: đúng x3, sai ; k = 3 (giá trị ở giữa)
TEST(FixedArrayDestructorTest, MiddleIterations) {
  {
    IntFixedArray arr(3, IntFixedArray::allocator_type());
  }
}

// P5: node 2: đúng x4, sai ; k = 4 (n-1)
TEST(FixedArrayDestructorTest, NMinusOneIterations) {
  {
    IntFixedArray arr(4, IntFixedArray::allocator_type());
  }
}

// P6: node 2: đúng x5, sai ; k = 5 (n)
TEST(FixedArrayDestructorTest, NIterations) {
  {
    IntFixedArray arr(5, IntFixedArray::allocator_type());
  }
}

}  // namespace internal
}  // namespace ceres
```