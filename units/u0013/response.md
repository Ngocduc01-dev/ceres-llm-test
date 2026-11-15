**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `num_residuals_` (đặt bằng `set_num_residuals` trong constructor của lớp con): 1 đến 5 | 3 |

**C. Nhánh không test**

- Không có nhánh nào bị bỏ. Hàm không có điểm rẽ nhánh, không có vòng lặp và không có `CHECK`.
- CFG khớp với mã nguồn.
- C2 dự kiến = 0 / 0 (tổng số nhánh bằng 0). TC1 vẫn đi qua toàn bộ đường START → 1 → END, nên phủ 100% câu lệnh.

**D. File test**

```cpp
// FILE: u0013_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"

namespace {

// Lớp con cụ thể để tạo được object của ceres::CostFunction
class TestCostFunction : public ceres::CostFunction {
 public:
  explicit TestCostFunction(int num_residuals) {
    set_num_residuals(num_residuals);
  }

  bool Evaluate(double const* const* parameters,
                double* residuals,
                double** jacobians) const override {
    return true;
  }
};

}  // namespace

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(CostFunctionNumResidualsTest, P1_ReturnNumResiduals) {
  TestCostFunction cost_function(3);  // giá trị cố định trong khoảng 1..5
  cost_function.num_residuals();      // không kiểm tra kết quả trả về
}
```