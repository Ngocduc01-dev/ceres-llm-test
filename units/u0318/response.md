**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 nhánh, 0 vòng lặp). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (node 1 là các member initializer chạy tuần tự) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `max_num_iterations` là int bất kỳ, chọn trong [1, 10] (không có điều kiện ràng buộc) | 4 |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh nào; mọi câu lệnh của node 1 đều được chạy bởi TC1, nên coi như phủ đầy đủ 100%).

**D. File test**

```cpp
// FILE: u0318_test.cc
#include "gtest/gtest.h"
#include "ceres/iterative_refiner.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(DenseIterativeRefinerConstructor, TC1_SinglePath) {
  const int max_num_iterations = 4;
  DenseIterativeRefiner refiner(max_num_iterations);
  (void)refiner;
}

}  // namespace internal
}  // namespace ceres
```