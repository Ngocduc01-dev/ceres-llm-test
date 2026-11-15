**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh, 0 nhánh). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` là số thực dương (log xác định), `f.a` ∈ [0.5, 5.0]; `f.v` là vector 2 phần tử, mỗi phần tử ∈ [-5.0, 5.0] | `f.a` = 2.3; `f.v` = (1.7, -3.1) (chọn cố định, tương đương seed cố định) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ (hàm không có điểm rẽ nhánh, không có `CHECK`, không có vòng lặp).

C2 dự kiến = 0 / 0 (không có nhánh; mọi câu lệnh của node 1 đều được chạy qua bởi TC1, nên đạt 100% theo quy ước).

Ghi chú: CFG khớp với mã nguồn. Node 1 cũng bao gồm dòng `return` ở dòng 568.

**D. File test**

```cpp
// FILE: u0101_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetLogTest, P1_SingleStraightPath) {
  Jet<double, 2> f;
  f.a = 2.3;
  f.v[0] = 1.7;
  f.v[1] = -3.1;

  Jet<double, 2> result = log(f);
  (void)result;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```