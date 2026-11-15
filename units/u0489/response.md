**Ghi chú:** CFG thiếu lệnh ở dòng 84 `STLDeleteContainerPointers(...)`. Theo mã nguồn, node 3 gồm dòng 84 và dòng 85. Hàm có 1 điểm rẽ nhánh (node 1), nên tổng số nhánh là 2. Vòng lặp xoá phần tử nằm trong hàm khác (`STLDeleteContainerPointers`), không thuộc unit này, nên không áp dụng quy tắc vòng lặp.

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | node 1: đúng |
| P2 | START → 1 → 3 → END | node 1: sai |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `container == nullptr` | `nullptr` kiểu `std::vector<int*>*` |
| TC2 | P2 | `container != nullptr`; số phần tử từ 1 đến 5, mỗi phần tử là con trỏ cấp phát bằng `new` | vector gồm 3 phần tử (giá trị 10, 20, 30) |

**C. Nhánh không test:** không có. Cả 2 nhánh đều có test.
`C2 dự kiến = 2 / 2`

**D. File test**

```cpp
// FILE: u0489_test.cc
#include "gtest/gtest.h"
#include "ceres/stl_util.h"

namespace ceres {

// P1: node 1: đúng
TEST(STLDeleteElementsTest, NullContainer) {
  STLDeleteElements<std::vector<int*>>(nullptr);
}

// P2: node 1: sai
TEST(STLDeleteElementsTest, NonNullContainer) {
  std::vector<int*> container;
  container.push_back(new int(10));
  container.push_back(new int(20));
  container.push_back(new int(30));
  STLDeleteElements(&container);
}

}  // namespace ceres
```