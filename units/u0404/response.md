**A. Test paths**

Unit không có điểm rẽ nhánh nào (CFG: START → END, destructor `= default`). Chỉ có 1 đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có nhánh (0 điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `LinearSolver::Options` mặc định (không có điều kiện ràng buộc); object được tạo rồi bị huỷ khi ra khỏi scope | Options mặc định, không đổi trường nào |

**C. Nhánh không test**

Không có nhánh nào (0 điểm rẽ nhánh, không có vòng lặp, không có `CHECK`).

C2 dự kiến = 0 / 0 (tổng số nhánh = 0, nên mặc định coi là phủ đầy đủ 100%).

**D. File test**

```cpp
// FILE: u0404_test.cc
#include "gtest/gtest.h"
#include "ceres/schur_complement_solver.h"

namespace ceres {
namespace internal {

// P1: START -> END (không có điểm rẽ nhánh)
TEST(DenseSchurComplementSolverDestructorTest, TC1_DestroyObject) {
  LinearSolver::Options options;
  {
    DenseSchurComplementSolver solver(options);
  }  // destructor được gọi tại đây khi ra khỏi scope
  SUCCEED();
}

}  // namespace internal
}  // namespace ceres
```