**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 vòng lặp, không có `CHECK`). CFG khớp với mã nguồn.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có nhánh nào (đường đi duy nhất, thực thi dòng 676) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` là số thực double bất kỳ (không có điều kiện ràng buộc), `f.v` là vector 2 phần tử bất kỳ | `f.a = 2.7`, `f.v = (0.3, -1.4)` |

**C. Nhánh không test**

Không có nhánh nào cần loại trừ vì hàm không có điểm rẽ nhánh.
`C2 dự kiến = 0 / 0` (tổng số nhánh = 0; mọi câu lệnh trong hàm đều được chạy bởi TC1, tức là hàm được phủ hoàn toàn).

**D. File test**

```cpp
// FILE: u0116_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(JetFloorTest, P1_NoBranch) {
  Jet<double, 2> f;
  f.a = 2.7;
  f.v[0] = 0.3;
  f.v[1] = -1.4;
  Jet<double, 2> r = floor(f);
  (void)r;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```