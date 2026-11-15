**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn (seed cố định, chọn tay) |
|---|---|---|---|
| TC1 | P1 | `x[3]`, `delta[3]`, mỗi phần tử trong [-5, 5]. Hàm không có điều kiện nên mọi giá trị đều hợp lệ. | `x = {1.5, -2.0, 0.5}`, `delta = {0.25, 3.0, -1.0}` |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có `CHECK`.
`C2 dự kiến = 0 / 0` (tổng số nhánh bằng 0, nên mọi câu lệnh của hàm đều được chạy bởi TC1 và độ phủ coi như đầy đủ).

Ghi chú:
- Tôi dùng `T = double` thay cho `Jet<double, 6>` ở CFG, vì `#include` ở mục 3.3 không có `ceres/jet.h`. Hàm không có nhánh nên đường đi giống nhau với cả hai kiểu.
- `EuclideanFunctor` được định nghĩa ngay trong file test, vì file `autodiff_manifold.h` chỉ cần một functor có `Plus` để khởi tạo `PlusWrapper`.

**D. File test**

```cpp
// FILE: u0010_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_manifold.h"

namespace {

// Functor đơn giản có phương thức Plus, dùng để khởi tạo PlusWrapper.
struct EuclideanFunctor {
  template <typename T>
  bool Plus(const T* x, const T* delta, T* x_plus_delta) const {
    for (int i = 0; i < 3; ++i) {
      x_plus_delta[i] = x[i] + delta[i];
    }
    return true;
  }
};

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(PlusWrapperOperatorTest, TC1_P1_GoiPlusMotLan) {
  EuclideanFunctor functor;
  ceres::internal::PlusWrapper<EuclideanFunctor> wrapper(functor);

  const double x[3] = {1.5, -2.0, 0.5};
  const double delta[3] = {0.25, 3.0, -1.0};
  double x_plus_delta[3] = {0.0, 0.0, 0.0};

  // Không kiểm tra kết quả trả về.
  wrapper(x, delta, x_plus_delta);
}

}  // namespace
```