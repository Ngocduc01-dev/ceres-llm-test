**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Tham số `void*` không được dùng (bị comment tên), không ràng buộc | `nullptr` |

**C. Nhánh không test**

Không có nhánh nào (hàm không có điểm rẽ nhánh, không có `CHECK`).

`C2 dự kiến = 0 / 0` (tổng số nhánh = 0, nên C2 coi như đạt 100% khi hàm được gọi 1 lần).

**D. File test**

```cpp
// FILE: u0421_test.cc
#include "gtest/gtest.h"
#include "ceres/suitesparse.h"

namespace ceres {
namespace internal {

// Path P1: START -> END (hàm không có điểm rẽ nhánh)
TEST(SuiteSparseFreeTest, P1_NoBranch) {
  SuiteSparse obj;
  obj.Free(nullptr);
}

}  // namespace internal
}  // namespace ceres
```