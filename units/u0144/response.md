**CFG của unit**

```
START → node 1: return isfinite(f) → END
```

Hàm không có điểm rẽ nhánh nào (không có `if`, vòng lặp, `switch` hay `?:`). Lệnh `isfinite(f)` là một lời gọi hàm khác, không tính là điểm rẽ nhánh của unit này. Tổng số nhánh là 0.

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `T = double`, `N = 2`. Giá trị `a` là số thực bất kỳ, không có điều kiện đường đi ràng buộc. | `Jet<double, 2> f(2.5, 0)` (a = 2.5, v = {1, 0}) |

**C. Nhánh không test**

- Không có nhánh nào bị bỏ qua. Không có `CHECK` và không có nhánh không thể đi tới.
- `C2 dự kiến = 0 / 0`. Hàm không có nhánh nên C2 đạt 100% một cách tầm thường, miễn là hàm được chạy qua node 1.

**D. File test**

```cpp
// FILE: u0144_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Hàm IsFinite bị đánh dấu deprecated, tắt cảnh báo để tránh lỗi khi biên dịch với -Werror.
#if defined(_MSC_VER)
#pragma warning(disable : 4996)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

// TC1 - P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(JetIsFiniteTest, TC1_P1_StraightLine) {
  ceres::Jet<double, 2> f(2.5, 0);
  ceres::IsFinite(f);
}
```