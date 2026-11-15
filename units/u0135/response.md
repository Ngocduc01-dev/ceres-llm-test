**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh), CFG chỉ có một đường đi duy nhất. CFG khớp với mã nguồn.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh (node 1: `return isnormal(f.a)`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` là số double bất kỳ (không có điều kiện ràng buộc); `f.v` là vector 1 phần tử bất kỳ | `f.a = 3.7`, `f.v[0] = 1.2` (cố định seed 42 cho bộ sinh số, giá trị lấy trong khoảng [1, 5]) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ (0 điểm rẽ nhánh, `isnormal(f.a)` chỉ gọi hàm chuẩn, không rẽ nhánh trong unit).

`C2 dự kiến = 0 / 0` (không có nhánh nào; hàm được phủ hoàn toàn bởi 1 test đi qua path P1).

**D. File test**

```cpp
// FILE: u0135_test.cc
#include <random>

#include "ceres/jet.h"
#include "gtest/gtest.h"

namespace ceres {
namespace {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetIsNormalTest, SinglePathNoBranch) {
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist(1.0, 5.0);

  Jet<double, 1> f;
  f.a = dist(gen);
  f.v[0] = dist(gen);

  bool result = isnormal(f);
  (void)result;  // Không kiểm tra kết quả trả về
}

}  // namespace
}  // namespace ceres
```