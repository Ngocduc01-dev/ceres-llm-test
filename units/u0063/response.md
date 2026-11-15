**Ghi chú:** CFG khớp với mã nguồn. Hàm không có điểm rẽ nhánh nào (tổng số nhánh = 0). `static_assert` được kiểm tra lúc biên dịch nên không phải nhánh. Không có vòng lặp. Chỉ có 1 đường đi duy nhất.

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `input[0]`, `input[1]` trỏ tới double bất kỳ (mảng 1 phần tử mỗi khối); `output` trỏ tới 1 double | x = 1.5, y = −2.0 (seed cố định, mt19937 seed 42, khoảng [−5, 5]) |

**C. Nhánh không test:** không có.
`C2 dự kiến = 0 / 0` (hàm không có điểm rẽ nhánh; chỉ cần 1 test đi qua node 1 là phủ toàn bộ hàm, tức C1 = 100%).

**D. File test**

```cpp
// FILE: u0063_test.cc
#include <random>
#include <type_traits>
#include <utility>

#include "ceres/internal/variadic_evaluate.h"
#include "gtest/gtest.h"

namespace ceres {
namespace internal {

namespace {

struct BinaryScalarCost {
  bool operator()(const double* x, const double* y, double* out) const {
    out[0] = x[0] + y[0];
    return true;
  }
};

}  // namespace

// P1: START -> 1 -> END
TEST(VariadicEvaluateImplTest, TwoBlocksNonDynamic) {
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist(-5.0, 5.0);

  double x[1] = {dist(gen)};
  double y[1] = {dist(gen)};
  const double* input[2] = {x, y};
  double output[1] = {0.0};

  BinaryScalarCost functor;
  bool result = VariadicEvaluateImpl(functor,
                                     input,
                                     output,
                                     std::false_type{},
                                     std::integer_sequence<int, 0, 1>{});
  (void)result;  // Không kiểm tra kết quả trả về.
}

}  // namespace internal
}  // namespace ceres
```