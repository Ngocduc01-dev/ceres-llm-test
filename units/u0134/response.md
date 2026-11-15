**A. Test paths**

Hàm có 0 điểm rẽ nhánh nên CFG chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` là bất kỳ số `double`, `f.v` gồm 2 phần tử `double` bất kỳ. Không có điều kiện đường đi nào ràng buộc. | `f.a = 3.7`, `f.v = {1.5, -2.0}` (giá trị cố định, không dùng sinh số ngẫu nhiên) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua: hàm không có điểm rẽ nhánh và không có `CHECK`. Không có vòng lặp.

`C2 dự kiến = 0 / 0` (tổng số nhánh bằng 0 nên coi là phủ đầy đủ, 100%; dự kiến, chưa chạy thật). CFG khớp với mã nguồn.

**D. File test**

```cpp
// FILE: u0134_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetIsNanTest, TC1_SinglePath) {
  ceres::Jet<double, 2> f;
  f.a = 3.7;
  f.v[0] = 1.5;
  f.v[1] = -2.0;
  bool result = ceres::isnan(f);
  (void)result;  // Không kiểm tra kết quả trả về
}
```