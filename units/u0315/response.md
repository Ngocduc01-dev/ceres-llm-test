**A. Test paths**

Hàm có 0 điểm rẽ nhánh, nên chỉ có một đường đi. CFG khớp với mã nguồn.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | row, col, index: số nguyên bất kỳ, chọn trong [0, 5] | row = 3, col = 1, index = 4 |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có vòng lặp hay `CHECK`.

C2 dự kiến = 0 / 0 (tổng số nhánh bằng 0, mọi câu lệnh ở node 1 đều được chạy bởi TC1, nên coi là phủ đủ 100%).

**D. File test**

```cpp
// FILE: u0315_test.cc
#include "gtest/gtest.h"
#include "ceres/inner_product_computer.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ProductTermTest, ConstructorTC1) {
  InnerProductComputer::ProductTerm term(3, 1, 4);
  (void)term;
}

}  // namespace internal
}  // namespace ceres
```