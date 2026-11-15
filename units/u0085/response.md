**A. Test paths**

Hàm không có điểm rẽ nhánh và không có vòng lặp nên chỉ có một đường đi. CFG khớp với mã nguồn.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (node 1 là chuỗi lệnh tuần tự) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` ∈ [-10, 10], `f.v` (4 phần tử) ∈ [-10, 10], `s` ∈ [-10, 10] (kiểu double, không có điều kiện ràng buộc) | `f.a = 3.0`, `f.v = (1.0, -2.0, 4.0, 5.0)`, `s = 2.0` (cố định, không dùng sinh số ngẫu nhiên) |

**C. Nhánh không test**

Không có. Các điểm không áp dụng: không có vòng lặp, không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có điểm rẽ nhánh nên không có nhánh nào cần phủ; độ phủ coi như đạt 100% khi P1 được chạy).

**D. File test**

```cpp
// FILE: u0085_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorMultiplyJetScalar, P1_SequentialPath) {
  using JetType = ceres::Jet<double, 4>;

  JetType f;
  f.a = 3.0;
  f.v[0] = 1.0;
  f.v[1] = -2.0;
  f.v[2] = 4.0;
  f.v[3] = 5.0;

  const double s = 2.0;

  JetType result = ceres::operator*(f, s);
  (void)result;  // Không kiểm tra kết quả trả về
}
```