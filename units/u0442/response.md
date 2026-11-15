**A. Test paths**

Mã nguồn chỉ có 1 điểm rẽ nhánh: vòng `for` ở node 2 (CFG của đề không đánh số node 1 là điểm rẽ, nên tôi dùng node 2). Tổng số nhánh là 2.

`Grid::DATA_DIMENSION = 2` là hằng số lúc biên dịch, nên vòng lặp luôn chạy đúng 2 lần.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → 2 → 3 → 4 → 2 → END | node 2: đúng (lần 1), node 2: đúng (lần 2), node 2: sai (thoát vòng) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Lưới 2×2 (`Grid2D<double, 2>`), dữ liệu là số thực bất kỳ. `r.a`, `c.a` bất kỳ (vì `Grid2D` tự chặn chỉ số). `r.v`, `c.v` bất kỳ. | Dữ liệu lưới `{1, 2, 3, 4, 5, 6, 7, 8}`, `r.a = 0.5`, `c.a = 0.5`, `r.v = 1.0`, `c.v = 2.0` |

Lý do chọn giá trị: không có điều kiện đường đi nào ràng buộc đầu vào, nên mọi giá trị hợp lệ đều đi qua P1. Tôi chọn các giá trị cố định, không dùng số ngẫu nhiên.

Ghi chú về kiểu `JetT`:
- Chỉ được `#include` hai file ở mục 3.3, nên không `#include "ceres/jet.h"`.
- Hàm chỉ dùng các thành viên `.a` và `.v`, nên tôi định nghĩa kiểu cục bộ `TestJet` (`a`, `v` kiểu `double`) làm `JetT`.

**C. Nhánh không test**

Số lần lặp của vòng `for` trong bộ test:

| Số lần lặp | Trạng thái | Lý do |
|---|---|---|
| 0 | Không làm được | `DATA_DIMENSION = 2`, vòng luôn lặp 2 lần |
| 1 | Không làm được | Như trên |
| số ở giữa | Không làm được | Như trên |
| n−1 | Không làm được | Như trên |
| n = 2 | Có test (TC1) | |
| n+1 | Không làm được | Như trên |

- Cả 2 nhánh (đúng và sai) của node 2 đều có test.
- Không có nhánh `CHECK` nào trong hàm.

`C2 dự kiến = 2 / 2` (dự kiến, chưa chạy thật)

**D. File test**

```cpp
// FILE: u0442_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

namespace ceres {
namespace {

// Kiểu thay thế Jet: chỉ cần thành viên a và v mà Evaluate sử dụng.
struct TestJet {
  double a;
  double v;
};

// P1: START -> 1 -> 2(đúng) -> 3 -> 4 -> 2(đúng) -> 3 -> 4 -> 2(sai) -> END
TEST(BiCubicInterpolatorEvaluateJet, TwoIterationsLoop) {
  const double data[8] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
  Grid2D<double, 2> grid(data, 0, 2, 0, 2);
  BiCubicInterpolator<Grid2D<double, 2>> interpolator(grid);

  TestJet r = {0.5, 1.0};
  TestJet c = {0.5, 2.0};
  TestJet f[2];
  f[0] = {0.0, 0.0};
  f[1] = {0.0, 0.0};

  interpolator.Evaluate(r, c, f);
}

}  // namespace
}  // namespace ceres
```