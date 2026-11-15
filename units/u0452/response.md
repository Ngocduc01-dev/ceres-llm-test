**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | node 1: đúng |
| P2 | START → 1 → END | node 1: sai |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `ownership = DO_NOT_TAKE_OWNERSHIP`; `rho` là con trỏ hợp lệ, tự quản lý vòng đời (đối tượng trên stack); `a` là số thực bất kỳ trong [0.5, 5] | `rho` = `TrivialLoss` trên stack; `a = 1.7` |
| TC2 | P2 | `ownership = TAKE_OWNERSHIP`; `rho` cấp phát bằng `new` (destructor sẽ xoá); `a` trong [0.5, 5] | `rho` = `new TrivialLoss`; `a = 3.2` |

**C. Nhánh không test**

Không có. Mọi nhánh đều đi tới được, và hàm không có `CHECK` hay vòng lặp.

`C2 dự kiến = 2 / 2` (dự kiến, chưa chạy thật)

**D. File test**

```cpp
// FILE: u0452_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// P1: node 1: đúng (DO_NOT_TAKE_OWNERSHIP) -> node 2 -> END
TEST(ScaledLossDestructorTest, DoNotTakeOwnershipReleasesPointer) {
  ceres::TrivialLoss rho;
  ceres::ScaledLoss* loss =
      new ceres::ScaledLoss(&rho, 1.7, ceres::DO_NOT_TAKE_OWNERSHIP);
  delete loss;
}

// P2: node 1: sai (TAKE_OWNERSHIP) -> END
TEST(ScaledLossDestructorTest, TakeOwnershipDeletesLoss) {
  ceres::ScaledLoss* loss =
      new ceres::ScaledLoss(new ceres::TrivialLoss(), 3.2, ceres::TAKE_OWNERSHIP);
  delete loss;
}
```