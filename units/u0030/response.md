**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (tổng số nhánh = 0) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Kích thước mảng n trong [1, 5] (n ≤ 37 nên dùng bộ nhớ inline). Phần tử là `Jet<double, 4>`, mặc định khởi tạo. | n = 3 (chọn cố định, seed không cần vì không dùng số ngẫu nhiên) |

Ghi chú: CFG khớp mã nguồn. Hàm chỉ có 1 node và không có vòng lặp. Test dùng `const FixedArray` để gọi đúng overload `data() const`. Để tránh phụ thuộc vào header `jet.h` (không có trong mục 3.3), test dùng `double` thay cho `Jet<double, 4>`, kiểu này vẫn đi qua cùng node 1 vì CFG không có nhánh nào phụ thuộc vào kiểu.

**C. Nhánh không test**

Không có nhánh nào (hàm không có điểm rẽ nhánh, không có `CHECK`).

`C2 dự kiến = 0 / 0` (không có nhánh; node 1 được chạy qua nên đạt phủ câu lệnh 100%).

**D. File test**

```cpp
// FILE: u0030_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayDataConst, TC1_P1_ConstData) {
  const ceres::internal::FixedArray<double, 37> arr(3, 1.0);
  const double* p = arr.data();
  (void)p;
}
```