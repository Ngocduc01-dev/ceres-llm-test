**A. Test paths**

Unit không có điểm rẽ nhánh nào (CFG chỉ có node 1: `return 4`), nên chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Hàm không có tham số. Template cố định `kNumParameters = 4`, không có dữ liệu ngẫu nhiên nên không cần seed. | Tạo `AutoDiffFirstOrderFunction<QuadraticCostFunctor, 4>` từ một functor cấp phát bằng `new`, rồi gọi `NumParameters()` một lần. |

**C. Nhánh không test**

Không có. Unit không có điểm rẽ nhánh và không có `CHECK`. Vòng lặp: không có.

C2 dự kiến = 0 / 0. Tổng số nhánh bằng 0 nên C2 coi như đạt trọn vẹn khi node 1 được chạy qua (dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0002_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_first_order_function.h"

namespace {

// Functor bậc hai với 4 tham số: f(x) = sum(x_i^2)
struct QuadraticCostFunctor {
  template <typename T>
  bool operator()(const T* const x, T* cost) const {
    cost[0] = T(0.0);
    for (int i = 0; i < 4; ++i) {
      cost[0] += x[i] * x[i];
    }
    return true;
  }
};

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(AutoDiffFirstOrderFunctionNumParametersTest, P1_ReturnsNumParameters) {
  // Constructor nhận con trỏ functor và sở hữu nó.
  ceres::AutoDiffFirstOrderFunction<QuadraticCostFunctor, 4> function(
      new QuadraticCostFunctor);
  function.NumParameters();  // Không kiểm tra kết quả trả về
}

}  // namespace
```