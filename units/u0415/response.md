**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh |

CFG khớp với mã nguồn. Dòng 126 là destructor `= default`, nên không có node điều kiện nào.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `sparse_cholesky`: `nullptr` hoặc đối tượng hợp lệ. `iterative_refiner`: `nullptr` hoặc đối tượng hợp lệ. Không có giá trị ngẫu nhiên, không cần seed. | Cả hai là `nullptr`. Tạo object rồi `delete` để gọi destructor đúng một lần. |

**C. Nhánh không test**

Không có nhánh nào. Unit có 0 điểm rẽ nhánh, nên không có nhánh `CHECK` sai nào bị bỏ qua.

`C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ; test đi qua đường START → END duy nhất nên coi như đạt 100%, dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0415_test.cc
#include "gtest/gtest.h"
#include "ceres/sparse_cholesky.h"

namespace ceres {
namespace internal {

// TC1 - P1: START -> END (không có điểm rẽ nhánh)
TEST(RefinedSparseCholeskyDestructorTest, DestroyObjectWithNullMembers) {
  auto* object = new RefinedSparseCholesky(nullptr, nullptr);
  delete object;  // gọi ~RefinedSparseCholesky() đúng một lần
}

}  // namespace internal
}  // namespace ceres
```