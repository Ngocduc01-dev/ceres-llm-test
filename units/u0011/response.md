**A. Test paths**

Unit không có điểm rẽ nhánh nào (0 điểm, 0 nhánh), nên chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `y`, `x`: mảng 3 phần tử `Jet<double, 6>`, mỗi giá trị bất kỳ trong [-5, 5]. `y_minus_x`: mảng 3 phần tử `Jet<double, 6>`. Không có điều kiện đường đi ràng buộc dữ liệu. | `y = {1.5, -2.0, 3.25}`, `x = {0.5, 4.0, -1.25}`, `y_minus_x` khởi tạo 0 |

**C. Nhánh không test**

- Không có nhánh nào bị bỏ sót. `CHECK` không xuất hiện trong unit.
- Ghi chú: `EuclideanFunctor` không có trong header `autodiff_manifold.h`, nên file test tự định nghĩa một functor có method template `Minus`. Mã nguồn của Ceres không bị sửa.
- `C2 dự kiến = 0 / 0` (unit không có nhánh). Test P1 chạy qua node 1 duy nhất, nên mọi node đều được phủ (dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0011_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_manifold.h"

namespace ceres {
namespace internal {

namespace {

// Functor tối thiểu có method template Minus để MinusWrapper gọi tới.
struct EuclideanFunctor {
  template <typename T>
  bool Minus(const T* y, const T* x, T* y_minus_x) const {
    for (int i = 0; i < 3; ++i) {
      y_minus_x[i] = y[i] - x[i];
    }
    return true;
  }
};

}  // namespace

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(MinusWrapperOperatorTest, P1_CallMinusWithJet) {
  using JetT = Jet<double, 6>;

  EuclideanFunctor functor;
  MinusWrapper<EuclideanFunctor> wrapper(functor);

  const JetT y[3] = {JetT(1.5), JetT(-2.0), JetT(3.25)};
  const JetT x[3] = {JetT(0.5), JetT(4.0), JetT(-1.25)};
  JetT y_minus_x[3] = {JetT(0.0), JetT(0.0), JetT(0.0)};

  // Không kiểm tra kết quả trả về, chỉ gọi unit một lần.
  wrapper(y, x, y_minus_x);
}

}  // namespace internal
}  // namespace ceres
```