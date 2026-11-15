**Ghi chú:** CFG khớp với mã nguồn. Constructor chỉ có member initializer (`values(values)`, `m()`), không có điểm rẽ nhánh. Tổng số nhánh = 0.

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `values`: con trỏ `double*` bất kỳ, trỏ tới mảng tối đa 5 phần tử (không có điều kiện ràng buộc) | `values` trỏ tới mảng `double[3] = {1.5, 2.5, 3.5}` (cố định, không dùng số ngẫu nhiên) |

**C. Nhánh không test**

Không có nhánh nào (unit không có điểm rẽ nhánh, không có vòng lặp, không có `CHECK`).

`C2 dự kiến = 0 / 0` (không có nhánh nào; mọi câu lệnh, gồm node 1, đều được chạy bởi TC1).

**D. File test**

```cpp
// FILE: u0228_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_matrix.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(CellInfoConstructorTest, P1_ConstructWithValuesPointer) {
  double data[3] = {1.5, 2.5, 3.5};
  CellInfo cell_info(data);
  (void)cell_info;
}

}  // namespace internal
}  // namespace ceres
```