**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `LinearSolver::Options` tuỳ ý (destructor không có điều kiện nào ràng buộc đầu vào) | `LinearSolver::Options` mặc định |

**C. Nhánh không test**

- Không có nhánh nào bị bỏ. Hàm là `= default`, không có điểm rẽ nhánh, không có vòng lặp và không có `CHECK`.
- Lưu ý: CFG khớp với mã nguồn dòng 56.
- `C2 dự kiến = 0 / 0` (tổng số nhánh là 0, nên coi như đạt 100%). Test vẫn đi qua đường START → END duy nhất, vì object được tạo rồi bị huỷ khi hết phạm vi.

**D. File test**

```cpp
// FILE: u0416_test.cc
#include "gtest/gtest.h"
#include "ceres/sparse_normal_cholesky_solver.h"

namespace ceres {
namespace internal {

// P1: START -> END (không có điểm rẽ nhánh)
TEST(SparseNormalCholeskySolverDestructorTest, DestroyObject) {
  LinearSolver::Options options;
  {
    SparseNormalCholeskySolver solver(options);
  }  // destructor được gọi ở đây
  SUCCEED();
}

}  // namespace internal
}  // namespace ceres
```