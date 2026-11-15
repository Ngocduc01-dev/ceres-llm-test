**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh, 0 nhánh). CFG khớp với mã nguồn (node 1 gồm dòng 638–640). Không có vòng lặp, không có `CHECK`.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (đường đi duy nhất) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` bất kỳ trong (−1.5, 1.5) (tránh điểm kỳ dị π/2); `f.v` là vector 2 phần tử, mỗi phần tử trong [−5, 5] | seed cố định 12345; `f.a` và `f.v` được sinh bằng `std::mt19937` + `uniform_real_distribution` |

**C. Nhánh không test**

Không có nhánh nào (hàm không có điểm rẽ nhánh).
`C2 dự kiến = 0 / 0` (không có nhánh; toàn bộ câu lệnh trong node 1 được thực thi bởi TC1, tức C1 = 100%).

**D. File test**

```cpp
// FILE: u0111_test.cc
#include <random>

#include "ceres/jet.h"
#include "gtest/gtest.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetTanTest, SinglePathNoBranch) {
  std::mt19937 gen(12345);
  std::uniform_real_distribution<double> a_dist(-1.5, 1.5);
  std::uniform_real_distribution<double> v_dist(-5.0, 5.0);

  Jet<double, 2> f;
  f.a = a_dist(gen);
  f.v[0] = v_dist(gen);
  f.v[1] = v_dist(gen);

  Jet<double, 2> result = tan(f);
  (void)result;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```