**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (đường đi duy nhất) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `max_num_iterations` là số nguyên bất kỳ (không có điều kiện ràng buộc), chọn trong khoảng 1 đến 5 | 3 |

**C. Nhánh không test**

Không có. Unit không có điểm rẽ nhánh, không có vòng lặp và không có `CHECK`.

`C2 dự kiến = 0 / 0` (tổng số nhánh là 0, nên C2 không xác định; test path P1 phủ toàn bộ node 1 nên đạt C1 = 100%).

**D. File test**

```cpp
// FILE: u0316_test.cc
#include "gtest/gtest.h"
#include "ceres/iterative_refiner.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(SparseIterativeRefinerConstructorTest, TC1_P1_ConstructWithMaxNumIterations) {
  const int max_num_iterations = 3;
  SparseIterativeRefiner refiner(max_num_iterations);
  (void)refiner;
}

}  // namespace internal
}  // namespace ceres
```