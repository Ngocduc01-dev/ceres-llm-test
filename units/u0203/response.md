**A. Test paths**

Hàm có 0 điểm rẽ nhánh, tổng số nhánh = 0. CFG khớp với mã nguồn (dòng 297: chỉ có member initializer `pointer_(pointer)`). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `pointer`: con trỏ `const double*` hợp lệ trỏ tới mảng 3 phần tử (ma trận 1x3), mỗi phần tử trong [-10, 10] | `{2.0, -7.0, 5.0}` (chọn ngẫu nhiên, cố định) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua (hàm không có điểm rẽ nhánh, không có `CHECK`, không có vòng lặp).

`C2 dự kiến = 0 / 0` (không có nhánh nào; mọi node, gồm node 1, đều được chạy qua bởi TC1, nên độ phủ câu lệnh 100%).

**D. File test**

```cpp
// FILE: u0203_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

namespace ceres {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(MatrixAdapterConstructorTest, P1_ConstructFromPointer) {
  const double data[3] = {2.0, -7.0, 5.0};
  MatrixAdapter<const double, 1, 3> adapter(data);
  (void)adapter;
}

}  // namespace ceres
```