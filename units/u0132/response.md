**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào (hàm chỉ có 1 node tuần tự) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` là số thực `double` bất kỳ (không có điều kiện ràng buộc); `f.v` là vector 1 phần tử | `f.a = 3.7`, `f.v[0] = 1.2` (cố định, không dùng số ngẫu nhiên) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua: hàm không có điểm rẽ nhánh và không có `CHECK`, nên không có vòng lặp cần xét.
`C2 dự kiến = 0 / 0` (không có nhánh; hàm được phủ hoàn toàn khi node 1 chạy qua, tức 100% câu lệnh).

**D. File test**

```cpp
// FILE: u0132_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetIsFiniteTest, P1_SequentialReturn) {
  Jet<double, 1> f;
  f.a = 3.7;
  f.v[0] = 1.2;
  // Không kiểm tra kết quả trả về, chỉ gọi hàm để chạy qua node 1.
  (void)isfinite(f);
}

}  // namespace internal
}  // namespace ceres
```