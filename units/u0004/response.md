**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào. Kiểu template: `Functor` là functor tự định nghĩa, `kAmbientSpaceDim = 3`, `kTangentSpaceDim = 3`. | Gọi `AutoDiffManifold<TestEuclideanFunctor, 3, 3>()` bằng constructor mặc định. |

**C. Nhánh không test**

- Không có nhánh nào: unit có 0 điểm rẽ nhánh. Node 1 (khởi tạo base và `functor_`) luôn chạy qua.
- Mã nguồn khớp với CFG. Tôi dùng functor tự định nghĩa `TestEuclideanFunctor` trong file test, vì `ceres::internal::EuclideanFunctor` trong CFG không có trong header ở mục 3.3.
- C2 dự kiến = 0 / 0 (tổng số nhánh bằng 0, nên coi là đạt đủ độ phủ).

**D. File test**

```cpp
// FILE: u0004_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_manifold.h"

namespace ceres {
namespace {

// Functor Euclidean đơn giản dùng làm tham số template cho AutoDiffManifold.
struct TestEuclideanFunctor {
  template <typename T>
  bool operator()(const T* x, const T* delta, T* x_plus_delta) const {
    for (int i = 0; i < 3; ++i) {
      x_plus_delta[i] = x[i] + delta[i];
    }
    return true;
  }

  template <typename T>
  bool Minus(const T* y, const T* x, T* y_minus_x) const {
    for (int i = 0; i < 3; ++i) {
      y_minus_x[i] = y[i] - x[i];
    }
    return true;
  }
};

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(AutoDiffManifoldConstructorTest, TC1_DefaultConstructor) {
  AutoDiffManifold<TestEuclideanFunctor, 3, 3> manifold;
  (void)manifold;
}

}  // namespace
}  // namespace ceres
```