**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | node 1: đúng |
| P2 | START → 1 → END | node 1: sai |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `ownership` = `DO_NOT_TAKE_OWNERSHIP` (chỉ có 1 giá trị thoả); `rho` = con trỏ tới `TrivialLoss` cấp phát trên stack | `ownership = DO_NOT_TAKE_OWNERSHIP`, `rho = &loss` |
| TC2 | P2 | `ownership` = `TAKE_OWNERSHIP` (giá trị còn lại của enum); `rho` = con trỏ tới `TrivialLoss` cấp phát bằng `new` | `ownership = TAKE_OWNERSHIP`, `rho = new TrivialLoss()` |

Hàm không có vòng lặp và đầu vào chỉ là enum nên không cần sinh số ngẫu nhiên.

**C. Nhánh không test:** không có.
`C2 dự kiến = 2 / 2`

**D. File test**

```cpp
// FILE: u0453_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

namespace ceres {

// Path P1: START -> 1 -> 2 -> END (node 1: đúng)
TEST(LossFunctionWrapperDestructorTest, DoNotTakeOwnership) {
  TrivialLoss loss;
  {
    LossFunctionWrapper wrapper(&loss, DO_NOT_TAKE_OWNERSHIP);
  }  // destructor được gọi tại đây
}

// Path P2: START -> 1 -> END (node 1: sai)
TEST(LossFunctionWrapperDestructorTest, TakeOwnership) {
  {
    LossFunctionWrapper wrapper(new TrivialLoss(), TAKE_OWNERSHIP);
  }  // destructor được gọi tại đây, rho_ tự giải phóng
}

}  // namespace ceres
```