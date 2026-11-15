**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 nhánh). CFG khớp với mã nguồn. Hai macro `CERES_DISABLE_DEPRECATED_WARNING` và `CERES_RESTORE_DEPRECATED_WARNING` chỉ là chỉ thị của trình biên dịch, không tạo nhánh.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (đường đi duy nhất) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | x là số thực bất kỳ (không có điều kiện ràng buộc), chọn trong [-10, 10] | x = 3.7 (seed cố định 0, chọn trong khoảng) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên không có nhánh nào bị bỏ.

`C2 dự kiến = 0 / 0` (không có nhánh; mọi câu lệnh ở node 1 đều được chạy bởi TC1, tức đạt 100% theo quy ước, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0127_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BesselJ1Test, TC1_SinglePath) {
  const double x = 3.7;
  double result = ceres::BesselJ1(x);
  (void)result;  // Không kiểm tra kết quả trả về
}
```