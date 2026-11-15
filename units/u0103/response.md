**A. Test paths**

Hàm có 0 điểm rẽ nhánh nên chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào. |

Ghi chú: CFG chỉ liệt kê node 1 (dòng 582). Dòng `return` (583) không có node riêng và chạy liền sau node 1. Theo mã nguồn, node 1 gồm cả hai dòng 582–583, không ảnh hưởng đến đường đi.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` trong (−1, 5], để `1 + f.a ≠ 0` và `log1p` không ra NaN. Các phần tử `f.v[0]`, `f.v[1]` trong [−5, 5]. | Dùng `std::mt19937` với seed cố định 42 và `uniform_real_distribution` để sinh `f.a` trong [−0.9, 5] và `f.v[0..1]` trong [−5, 5]. |

**C. Nhánh không test**

Không có nhánh nào (hàm không có điểm rẽ nhánh và không có `CHECK`).

`C2 dự kiến = 0 / 0` (tổng số nhánh bằng 0, nên mọi nhánh đều đã được phủ; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0103_test.cc
#include <random>

#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(Log1pJetTest, P1_StraightLine) {
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist_a(-0.9, 5.0);
  std::uniform_real_distribution<double> dist_v(-5.0, 5.0);

  ceres::Jet<double, 2> f;
  f.a = dist_a(gen);
  f.v[0] = dist_v(gen);
  f.v[1] = dist_v(gen);

  ceres::Jet<double, 2> result = ceres::log1p(f);
  (void)result;  // Không kiểm tra kết quả trả về.
}
```