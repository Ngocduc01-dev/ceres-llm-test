**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 nhánh). CFG chỉ có một node 1 nên chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (đường thẳng) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | f.a ∈ [1, 10], g.a ∈ [1, 10] (g.a ≠ 0), f.v và g.v là vector 5 phần tử, mỗi phần tử ∈ [1, 10]. Dùng `Jet<double, 5>` | f.a = 7, g.a = 3, f.v = {2, 9, 4, 6, 1}, g.v = {5, 8, 3, 10, 7} (chọn ngẫu nhiên cố định, seed cố định) |

Ghi chú: CFG dựng cho `operator/<double, 16>`, nhưng template chạy đúng với N bất kỳ; dùng N = 5 để thoả giới hạn tối đa 5 phần tử. Mã nguồn khớp CFG (node 1 gồm dòng 375–377; dòng `return` ở dòng 377 cùng nằm trong node 1 về mặt luồng).

**C. Nhánh không test**

Không có nhánh nào cần bỏ qua, vì hàm không có điểm rẽ nhánh và không có vòng lặp. Không có `CHECK`.

`C2 dự kiến = 0 / 0` (tổng số nhánh = 0; C2 coi như đạt 100% khi đường đi duy nhất được chạy qua).

**D. File test**

```cpp
// FILE: u0087_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetDivisionTest, P1_StraightLine) {
  using J = ceres::Jet<double, 5>;

  J f;
  f.a = 7.0;
  f.v[0] = 2.0;
  f.v[1] = 9.0;
  f.v[2] = 4.0;
  f.v[3] = 6.0;
  f.v[4] = 1.0;

  J g;
  g.a = 3.0;
  g.v[0] = 5.0;
  g.v[1] = 8.0;
  g.v[2] = 3.0;
  g.v[3] = 10.0;
  g.v[4] = 7.0;

  J h = f / g;
  (void)h;
}
```