**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `LinearSolver::Options` mặc định (không có điều kiện ràng buộc vì không có điểm rẽ nhánh) | `LinearSolver::Options` khởi tạo mặc định, không đặt trường nào |

**C. Nhánh không test**

Không có. Hàm là destructor `= default`, không có điểm rẽ nhánh (0 nhánh). Không có nhánh `CHECK`.

C2 dự kiến = 0 / 0 (không có nhánh nào; path P1 duy nhất được chạy qua bằng cách tạo rồi huỷ object, coi như phủ đầy đủ).

Ghi chú: CFG khớp với mã nguồn (dòng 61 là `= default`).

**D. File test**

```cpp
// FILE: u0320_test.cc
#include "gtest/gtest.h"
#include "ceres/iterative_schur_complement_solver.h"

namespace ceres {
namespace internal {

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(IterativeSchurComplementSolverDestructorTest, TC1_ConstructThenDestroy) {
  LinearSolver::Options options;
  {
    IterativeSchurComplementSolver solver(options);
  }  // destructor được gọi tại đây
  SUCCEED();
}

}  // namespace internal
}  // namespace ceres
```