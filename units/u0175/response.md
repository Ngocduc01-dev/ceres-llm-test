**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, tổng 0 nhánh). CFG chỉ có một đường duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh (không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `a` là số thực bất kỳ, `a != 0` (để `1 / (a * a)` không chia cho 0); chọn `a` trong [0.5, 5.0] | `a = 2.5` (chọn ngẫu nhiên với seed cố định) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua vì unit không có điểm rẽ nhánh. Không có vòng lặp và không có `CHECK`.
Ghi chú: CFG khớp với mã nguồn (một câu lệnh khởi tạo duy nhất).

`C2 dự kiến = 0 / 0` (không có nhánh nào; đường đi duy nhất P1 được chạy qua, tức phủ 100% theo quy ước).

**D. File test**

```cpp
// FILE: u0175_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// Path P1: START -> 1 -> END
// a thuộc [0.5, 5.0], giá trị chọn (seed cố định): 2.5
TEST(ArctanLossConstructorTest, P1_SinglePath) {
  const double a = 2.5;
  ceres::ArctanLoss loss(a);
  (void)loss;
}
```