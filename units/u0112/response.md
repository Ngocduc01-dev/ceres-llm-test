**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 nhánh) và không có vòng lặp, nên chỉ có một test path.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` là số thực bất kỳ (không có điều kiện ràng buộc); `f.v` là vector 2 phần tử bất kỳ | `f.a = 0.7`, `f.v = (0.3, -1.2)` |

Ghi chú: giá trị được chọn cố định trong code (không dùng hàm sinh số ngẫu nhiên), nên kết quả giống nhau ở mọi lần chạy.

**C. Nhánh không test**

Không có nhánh nào bị bỏ (hàm không có điểm rẽ nhánh, không có `CHECK`). Mẫu số bằng 0 nên C2 không xác định theo công thức; coi như đạt phủ đầy đủ khi P1 được chạy qua.

`C2 dự kiến = 0 / 0` (không có nhánh; tất cả câu lệnh ở node 1 đều được chạy bởi TC1).

**D. File test**

```cpp
// FILE: u0112_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetAtanTest, P1_NoBranch) {
  Jet<double, 2> f;
  f.a = 0.7;
  f.v[0] = 0.3;
  f.v[1] = -1.2;

  Jet<double, 2> r = atan(f);
  (void)r;  // Không kiểm tra kết quả trả về.
}

}  // namespace
}  // namespace ceres
```