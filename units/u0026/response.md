**A. Test paths**

Unit không có điểm rẽ nhánh nào (CFG: START → 1 → END). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | n: 1..5 (tránh n = 0 cho gọn); val: bất kỳ double; a: allocator mặc định | n = 3, val = 2.5 (chọn cố định, seed cố định) |

**C. Nhánh không test**

Không có nhánh nào (tổng số nhánh = 0). Ghi chú: node 1 gồm member initializer `storage_(n, a)` và lời gọi `ConstructRange(...)`. Các vòng lặp/rẽ nhánh bên trong `storage_` và `ConstructRange` thuộc hàm khác, không tính vào unit này.

`C2 dự kiến = 0 / 0` (không có nhánh; mọi câu lệnh của unit được chạy bởi TC1, dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0026_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayConstructorValTest, TC1_SizeAndValue) {
  const ceres::internal::FixedArray<double>::size_type n = 3;
  const double val = 2.5;
  ceres::internal::FixedArray<double> array(n, val);
}
```