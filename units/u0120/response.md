**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh, 0 nhánh). CFG chỉ có một node 1, khớp với mã nguồn (dòng 708; dòng 709 là câu lệnh `return`, nằm cùng khối tuần tự).

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh rẽ |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` trong (0, 10], `f.v` gồm 2 phần tử trong [-5, 5] (kiểu `Jet<double, 2>`) | `f.a` = 3.7, `f.v` = (1.3, -2.4) (chọn ngẫu nhiên, cố định) |

**C. Nhánh không test**

Không có nhánh nào (hàm không có điểm rẽ nhánh, không có `CHECK`, không có vòng lặp).
`C2 dự kiến = 0 / 0` (không có nhánh nào; mọi câu lệnh đều được chạy bởi TC1, tức đạt C1 đầy đủ; chưa chạy thật).

**D. File test**

```cpp
// FILE: u0120_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có nhánh rẽ)
TEST(Log2JetTest, P1_NoBranch) {
  ceres::Jet<double, 2> f;
  f.a = 3.7;
  f.v[0] = 1.3;
  f.v[1] = -2.4;

  ceres::Jet<double, 2> r = ceres::log2(f);
  (void)r;  // Không kiểm tra kết quả trả về
}
```