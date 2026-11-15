**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh), nên chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Jet<double, 2> `a` được tạo bằng `Jet(value, k)` với value ∈ [-10, 10], k ∈ {0, 1}; `s` kiểu double ∈ [-10, 10]. Không có điều kiện ràng buộc nào khác | a = Jet<double, 2>(3.5, 0), s = 1.25 |

**C. Nhánh không test**

Không có nhánh nào (hàm không có điểm rẽ nhánh). CFG khớp với mã nguồn.

C2 dự kiến = 0 / 0 (tổng số nhánh = 0; đường đi duy nhất P1 được chạy qua, nên coi như phủ đủ 100%).

**D. File test**

```cpp
// FILE: u0073_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorMinusAssignScalarTest, TC1_P1_SinglePath) {
  ceres::Jet<double, 2> a(3.5, 0);
  const double s = 1.25;
  a -= s;
}
```