**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào (0 nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có đầu vào. Chỉ tạo rồi huỷ một object của class con của `Preconditioner` (destructor không tham số). | Không có (object `TestPreconditioner` tạo trên stack, huỷ khi hết phạm vi) |

**C. Nhánh không test**

Không có. Destructor `= default` không có điểm rẽ nhánh, nên không có nhánh nào bị bỏ.
`C2 dự kiến = 0 / 0` (không có nhánh; đường START → END được chạy qua 1 lần nên coi như đạt 100%).

**D. File test**

```cpp
// FILE: u0380_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"

namespace ceres {
namespace internal {

namespace {

// Lớp con cụ thể để tạo được object (Preconditioner có hàm thuần ảo).
class TestPreconditioner : public Preconditioner {
 public:
  bool Update(const LinearOperator& /*A*/, const double* /*D*/) override {
    return true;
  }

  void RightMultiplyAndAccumulate(const double* /*x*/,
                                  double* /*y*/) const override {}

  int num_rows() const override { return 0; }
};

}  // namespace

// Path P1: START -> END
TEST(PreconditionerDestructorTest, DestroyObject) {
  {
    TestPreconditioner obj;
  }  // ~Preconditioner() được gọi khi obj ra khỏi phạm vi
  SUCCEED();
}

}  // namespace internal
}  // namespace ceres
```