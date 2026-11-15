**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh, tổng 0 nhánh). CFG khớp với mã nguồn: node 1 là câu lệnh `return` duy nhất (toán tử `-` chỉ là phép toán, không rẽ nhánh).

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (đường đi duy nhất) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `x.a` ∈ [-2, 2] (không có điều kiện ràng buộc); `x.v` là vectơ 2 phần tử, mỗi phần tử ∈ [-2, 2] | `x.a` = 0.37; `x.v` = (-1.2, 0.8) (chọn cố định, đại diện cho lựa chọn ngẫu nhiên với seed cố định) |

**C. Nhánh không test**

Không có nhánh nào (hàm không có điểm rẽ nhánh, không có `CHECK`).

`C2 dự kiến = 0 / 0` (không có nhánh nào; toàn bộ câu lệnh node 1 được chạy qua bởi TC1, nên độ phủ coi như đầy đủ).

**D. File test**

```cpp
// FILE: u0125_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetErfcTest, TC1_SingleStraightLinePath) {
  Jet<double, 2> x;
  x.a = 0.37;
  x.v[0] = -1.2;
  x.v[1] = 0.8;

  Jet<double, 2> r = erfc(x);
  (void)r;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```