**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 nhánh, không có vòng lặp, không có `CHECK`). CFG chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh; đi qua node 1 (`const T tmp = exp(f.a)`, kèm `return Jet<T, N>(tmp, tmp * f.v)`) |

Ghi chú: CFG chỉ có node 1, nhưng mã nguồn còn dòng 590 (`return`). Hai dòng này chạy liền nhau, không rẽ nhánh nên không đổi kết quả.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` ∈ [-2, 2]; `f.v` (Jet<double, 2>) mỗi phần tử ∈ [-2, 2] | seed cố định 42 (`std::mt19937`), `f.a` = giá trị sinh ra, `f.v[0]`, `f.v[1]` = hai giá trị tiếp theo |

**C. Nhánh không test**

Không có nhánh nào (tổng số nhánh = 0).
`C2 dự kiến = 0 / 0` (không có điểm rẽ nhánh nên mọi câu lệnh đều chạy qua khi gọi hàm một lần; coi như đạt 100%; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0104_test.cc
#include <random>

#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetExpTest, SinglePath) {
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist(-2.0, 2.0);

  ceres::Jet<double, 2> f;
  f.a = dist(gen);
  f.v[0] = dist(gen);
  f.v[1] = dist(gen);

  ceres::Jet<double, 2> r = ceres::exp(f);
  (void)r;  // Không kiểm tra kết quả trả về
}
```