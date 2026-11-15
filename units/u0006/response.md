**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào (node 1: `return 3`, không có điều kiện) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào. Object dùng `AutoDiffManifold<EuclideanFunctor, 3, 3>` tạo bằng constructor mặc định. | Không có (không cần sinh số ngẫu nhiên, không cần seed) |

**C. Nhánh không test**

- Không có nhánh nào bị bỏ qua. Hàm không có điểm rẽ nhánh và không có `CHECK`.
- C2 dự kiến = 0 / 0. Tổng số nhánh là 0, nên P1 phủ toàn bộ CFG và coi như đạt 100%. Đây là kết quả dự kiến, chưa chạy thật.

**D. File test**

```cpp
// FILE: u0006_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_manifold.h"

namespace {

// Functor Euclid đơn giản (tự định nghĩa) dùng cho AutoDiffManifold.
struct EuclideanFunctor {
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

}  // namespace

// P1: START -> 1 -> END (không có nhánh rẽ)
TEST(AutoDiffManifoldTangentSizeTest, TC1_P1_ReturnTangentSize) {
  ceres::AutoDiffManifold<EuclideanFunctor, 3, 3> manifold;
  int tangent_size = manifold.TangentSize();
  (void)tangent_size;  // Không kiểm tra kết quả trả về
}
```