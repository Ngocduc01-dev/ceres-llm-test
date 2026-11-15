**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào. Chỉ cần tạo một object của class con rồi để nó bị huỷ (destructor chạy một lần). | Không có |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nào, nên tổng số nhánh là 0. Mã nguồn (`= default`) khớp với CFG.

`C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ; test TC1 chỉ chạy qua START → END)

**D. File test**

```cpp
// FILE: u0327_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search_direction.h"

namespace ceres {
namespace internal {

namespace {

// Lớp con cài đặt hàm thuần ảo để có thể tạo object.
class TestLineSearchDirection : public LineSearchDirection {
 public:
  bool NextDirection(const LineSearchMinimizer::State& previous,
                     const LineSearchMinimizer::State& current,
                     Vector* search_direction) override {
    return true;
  }
};

}  // namespace

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(LineSearchDirectionDestructorTest, TC1_DestroyObject) {
  {
    TestLineSearchDirection obj;
  }  // destructor ~LineSearchDirection() chạy khi ra khỏi phạm vi
  SUCCEED();
}

}  // namespace internal
}  // namespace ceres
```