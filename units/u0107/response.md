**A. Test paths**

Hàm `cos` không có điểm rẽ nhánh nào (CFG khớp với mã nguồn: một node 1 gồm lời gọi `cos`, `sin`, `operator*` và dựng `Jet`, rồi tới END). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` ∈ [-10, 10]; `f.v` là vector 7 phần tử (kiểu `Jet<double, 7>`), mỗi phần tử ∈ [-10, 10] | Seed cố định 42 (`std::mt19937`); `f.a` = 0.7 và `f.v` = {-3.2, 1.5, 0.4, 2.8, -0.9, 4.1, -1.7} (giá trị cố định, dùng thay cho giá trị sinh ngẫu nhiên) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ (hàm không có điểm rẽ nhánh, không có `CHECK`).
`C2 dự kiến = 0 / 0` (không có nhánh; mọi câu lệnh đều được chạy bởi TC1, tức là đạt 100% theo quy ước).

**D. File test**

```cpp
// FILE: u0107_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(JetCosTest, P1_SinglePath) {
  Jet<double, 7> f;
  f.a = 0.7;
  f.v[0] = -3.2;
  f.v[1] = 1.5;
  f.v[2] = 0.4;
  f.v[3] = 2.8;
  f.v[4] = -0.9;
  f.v[5] = 4.1;
  f.v[6] = -1.7;

  Jet<double, 7> r = cos(f);
  (void)r;
}

}  // namespace
}  // namespace ceres
```