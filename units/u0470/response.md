**A. Test paths**

Điểm rẽ nhánh: node 2 và node 3, tổng 4 nhánh.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 6 → 3 → 4 → END | node 2: sai, node 3: đúng |
| P2 | START → 1 → 2 → 3 → 5 → END | node 2: đúng, node 3: sai |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | a ≥ 0, b > 0 (để ctor không CHECK sai); x = (s−a)/b > 36.7 ⇒ s > a + 36.7·b = 74.9 | a = 1.5, b = 2.0, s = 100.0 |
| TC2 | P2 | a ≥ 0, b > 0; x ≤ 36.7 ⇒ s ≤ 74.9 | a = 1.5, b = 2.0, s = 3.0 |

**C. Nhánh không test**

- Không có nhánh nào là "không thể đi tới" hay "CHECK sai". Hai `CHECK` trong constructor không được tính và cũng không bị làm sai.
- Node 2 (nhánh sai → 6) chỉ chạy ở lần gọi đầu tiên của tiến trình, nên TC1 được đặt trước TC2 và gọi hàm lần đầu. GoogleTest chạy các test theo thứ tự khai báo trong file.
- CFG không khớp mã nguồn: `kLog2Pow53` là `static constexpr`, được khởi tạo lúc biên dịch và không có guard lúc chạy. Theo mã nguồn, node 2 và node 6 không phải nhánh thật. Tôi vẫn tính chúng vào tổng số nhánh theo CFG.

`C2 dự kiến = 4 / 4`. Đây là số dự kiến, chưa chạy thật. Nếu theo mã nguồn thì chỉ có node 3, tức 2/2.

**D. File test**

```cpp
// FILE: u0470_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// P1: START -> 1 -> 2(sai) -> 6 -> 3(đúng) -> 4 -> END
// Phải là test đầu tiên gọi Evaluate để node 2 đi nhánh "sai" (khởi tạo lần đầu).
TEST(TolerantLossEvaluate, XGreaterThanThreshold) {
  ceres::TolerantLoss loss(1.5, 2.0);
  double rho[3];
  loss.Evaluate(100.0, rho);
}

// P2: START -> 1 -> 2(đúng) -> 3(sai) -> 5 -> END
TEST(TolerantLossEvaluate, XNotGreaterThanThreshold) {
  ceres::TolerantLoss loss(1.5, 2.0);
  double rho[3];
  loss.Evaluate(3.0, rho);
}
```