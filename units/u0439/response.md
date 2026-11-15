**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2(đúng) → 3 → 4 → 2(đúng) → 3 → 4 → 2(sai) → END | node 2: đúng (2 lần), node 2: sai (1 lần) |

Node 1 không phải điểm rẽ nhánh. Nó chỉ chứa các câu lệnh tuần tự.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Dữ liệu lưới: 2 mẫu × 2 giá trị = 4 số thực, `begin = 0`, `end = 2`. `x.a` nằm trong [0, 1]. `x.v` là vector 4 chiều tuỳ ý. | data = {1, 2, 3, 4}, `x = Jet<double, 4>(0.5, 0)` (a = 0.5, v = (1, 0, 0, 0)) |

**C. Nhánh không test**

- Không có nhánh nào bị bỏ vì `CHECK`.
- Về số lần lặp của vòng for ở node 2: `Grid1D<double, 2>::DATA_DIMENSION` là hằng số 2 lúc biên dịch, nên chỉ làm được đúng 2 lần lặp (n = 2).
  - Không thể có 0 lần lặp, 1 lần lặp (n−1) hay 3 lần lặp (n+1) với kiểu này. Muốn khác thì phải đổi kiểu Grid, tức là ra ngoài CFG đã cho.
  - Với n = 2, các mốc "một số ở giữa" và "n−1" trùng với lần lặp thứ nhất.
- Nhánh đúng và nhánh sai của node 2 đều đã có test đi qua.

`C2 dự kiến = 2 / 2`

Lưu ý: file chỉ `#include` hai header ở mục 3.3 và dùng `ceres::Jet`. Nếu biên dịch báo thiếu `Jet`, cần thêm `#include "ceres/jet.h"`. Tôi không tự thêm vì đề chỉ cho phép hai include đó.

**D. File test**

```cpp
// FILE: u0439_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// P1: START -> 1 -> 2(đúng) -> 3 -> 4 -> 2(đúng) -> 3 -> 4 -> 2(sai) -> END
// Phủ: node 2: đúng, node 2: sai (vòng lặp chạy đúng 2 lần, DATA_DIMENSION = 2)
TEST(CubicInterpolatorEvaluateJet, TC1_LoopTwoIterations) {
  const double data[4] = {1.0, 2.0, 3.0, 4.0};
  ceres::Grid1D<double, 2> grid(data, 0, 2);
  ceres::CubicInterpolator<ceres::Grid1D<double, 2>> interpolator(grid);

  ceres::Jet<double, 4> x(0.5, 0);
  ceres::Jet<double, 4> f[2];

  interpolator.Evaluate(x, f);
}
```