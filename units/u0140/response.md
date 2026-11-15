**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh, tổng 0 nhánh). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh; node 1 chạy tuần tự |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | f.a, g.a: double bất kỳ (không có điều kiện ràng buộc), Jet<double, 1> | f.a = 2.5, g.a = -1.5 (chọn từ khoảng [-5, 5], seed cố định) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên không có nhánh nào cần phủ. Ghi chú: CFG khớp với mã nguồn (một câu lệnh `return` gọi `isgreaterequal` trên giá trị vô hướng); `enable_if_t` chỉ xử lý lúc biên dịch, không phải điểm rẽ nhánh lúc chạy.

`C2 dự kiến = 0 / 0` (không có nhánh; toàn bộ node 1 được chạy qua nên đạt phủ câu lệnh 100%).

**D. File test**

```cpp
// FILE: u0140_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(IsGreaterEqualJet, P1_SingleStatementPath) {
  // f.a = 2.5, g.a = -1.5 (chọn trong [-5, 5], giá trị cố định)
  Jet<double, 1> f(2.5);
  Jet<double, 1> g(-1.5);
  f.v[0] = 1.0;
  g.v[0] = 0.5;

  // Chỉ gọi hàm, không kiểm tra kết quả trả về
  (void)isgreaterequal(f, g);
}

}  // namespace
}  // namespace ceres
```