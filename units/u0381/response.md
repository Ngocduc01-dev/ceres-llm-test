**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (chỉ khởi tạo các member) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào (constructor mặc định) | Không có |

**C. Nhánh không test**

Không có. Unit không có điểm rẽ nhánh nên tổng số nhánh là 0, không có nhánh nào bị bỏ qua. Ghi chú: node 1 chỉ gồm các member initializer, không có lệnh điều khiển. Mã nguồn `Options() = default;` khớp với CFG.

`C2 dự kiến = 0 / 0` (không có nhánh nào; coi như đạt 100% vì mọi node đều được chạy qua).

**D. File test**

```cpp
// FILE: u0381_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(PreconditionerOptionsConstructorTest, DefaultConstructor_P1) {
  Preconditioner::Options options;
  (void)options;
}

}  // namespace internal
}  // namespace ceres
```