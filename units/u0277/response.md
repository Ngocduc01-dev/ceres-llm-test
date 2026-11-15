**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `dense_cholesky`: con trỏ khác null. `iterative_refiner`: con trỏ khác null, `max_num_iterations` ≥ 1 (chọn trong 1..5). | `EigenDenseCholesky`, `DenseIterativeRefiner(3)` |

**C. Nhánh không test**

Không có nhánh nào, vì hàm không có điểm rẽ nhánh. CFG khớp với mã nguồn (destructor `= default`).

C2 dự kiến = 0 / 0 (không có nhánh nào cần phủ, coi như đạt 100%).

Giả định: `EigenDenseCholesky` và `DenseIterativeRefiner` có thể dùng được qua `ceres/dense_cholesky.h`. Nếu lúc biên dịch báo thiếu kiểu `DenseIterativeRefiner`, cần bổ sung `#include "ceres/dense_iterative_refiner.h"`.

**D. File test**

```cpp
// FILE: u0277_test.cc
#include <memory>
#include <utility>

#include "gtest/gtest.h"
#include "ceres/dense_cholesky.h"

namespace ceres {
namespace internal {

// TC1 - P1: START -> END (hàm không có điểm rẽ nhánh)
TEST(RefinedDenseCholeskyDestructorTest, DestroyObject_P1) {
  std::unique_ptr<DenseCholesky> dense_cholesky(new EigenDenseCholesky());
  std::unique_ptr<DenseIterativeRefiner> refiner(new DenseIterativeRefiner(3));
  {
    RefinedDenseCholesky object(std::move(dense_cholesky), std::move(refiner));
  }  // destructor ~RefinedDenseCholesky() được gọi tại đây
  SUCCEED();
}

}  // namespace internal
}  // namespace ceres
```