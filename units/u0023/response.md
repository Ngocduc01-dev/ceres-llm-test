**A. Test paths**

Unit có 0 điểm rẽ nhánh nên chỉ có 1 đường đi duy nhất, không có vòng lặp. Mã nguồn khớp với CFG (đệ quy tới `integer_sequence<int, 2>` rồi `integer_sequence<int>` rỗng, đều không có rẽ nhánh).

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `parameters[0]`, `parameters[1]`: mỗi khối 2 số double, mỗi số trong [-10, 10]. `x`: mảng 4 `Jet<double, 4>` | Sinh bằng `std::mt19937` seed 42 trong [-10, 10] |

**C. Nhánh không test**

Không có. `C2 dự kiến = 0 / 0` (không có nhánh nào, nên mọi node đều được phủ bởi TC1).

**D. File test**

```cpp
// FILE: u0023_test.cc
#include <array>
#include <random>
#include <utility>

#include "gtest/gtest.h"
#include "ceres/internal/autodiff.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(Make1stOrderPerturbationsApply, P1_TwoBlocksOfSizeTwo) {
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist(-10.0, 10.0);

  double block0[2] = {dist(gen), dist(gen)};
  double block1[2] = {dist(gen), dist(gen)};
  const double* parameters[2] = {block0, block1};

  Jet<double, 4> x[4];

  Make1stOrderPerturbations<std::integer_sequence<int, 2, 2>> obj;
  obj.Apply(parameters, x);
}

}  // namespace internal
}  // namespace ceres
```

Lưu ý: nếu biên dịch báo `Jet` là kiểu chưa đầy đủ (incomplete type) vì `autodiff.h` không kéo theo `ceres/jet.h`, cần thêm `#include "ceres/jet.h"`. Tôi không thêm sẵn vì mục 3.3 chỉ cho phép hai `#include` đã nêu, và chưa chạy biên dịch thật.