**A. Test paths**

Unit không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 nhánh), nên chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `sq_norm` ∈ [0, 10] (không có điều kiện ràng buộc); `rho` là mảng 3 phần tử; `user_data` = con trỏ tới một biến `int` | `sq_norm` = 3.7 (chọn cố định); `rho` = {0, 0, 0}; `user_data` = &biến `int` có giá trị 42 |

**C. Nhánh không test**

Không có. Unit không có điểm rẽ nhánh nào và không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ; node 1 được chạy qua bởi TC1, nên C1 là 100%).

**D. File test**

Theo mục 3.3, file chỉ `#include "gtest/gtest.h"`. Khi biên dịch, file này cần nhìn thấy định nghĩa `CallbackLossFunction` và `ceres_loss_function_t` từ `c_api.cc`.

```cpp
// FILE: u0246_test.cc
#include "gtest/gtest.h"

namespace {

// Hàm callback đơn giản dùng làm loss_function_ (không kiểm tra kết quả).
void TestLossCallback(void* user_data, double sq_norm, double* rho) {
  int* counter = static_cast<int*>(user_data);
  if (counter != nullptr) {
    ++(*counter);
  }
  rho[0] = sq_norm;
  rho[1] = 1.0;
  rho[2] = 0.0;
}

}  // namespace

// P1: START -> 1 -> END
TEST(CallbackLossFunctionEvaluateTest, P1_CallsLossCallback) {
  int user_value = 42;
  CallbackLossFunction loss_function(TestLossCallback, &user_value);

  double sq_norm = 3.7;
  double rho[3] = {0.0, 0.0, 0.0};

  loss_function.Evaluate(sq_norm, rho);
}
```