**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 nhánh). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | x là số thực bất kỳ (không có điều kiện ràng buộc), chọn trong [-10, 10] | x = 3.7 |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có `CHECK`.

C2 dự kiến = 0 / 0 (không có nhánh nào; đường đi duy nhất P1 được chạy qua, tức phủ 100% câu lệnh và đường đi).

**D. File test**

```cpp
// FILE: u0126_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BesselJ0Test, TC1_SingleStraightPath) {
  const double x = 3.7;
  double r = ceres::BesselJ0(x);
  (void)r;  // Không kiểm tra kết quả trả về
}
```