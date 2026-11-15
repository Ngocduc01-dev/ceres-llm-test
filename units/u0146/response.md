**A. Test paths**

CFG: `START → 1 → END`
- Node 1: `return isnormal(f);` (một khối lệnh chạy liền, không có rẽ nhánh).
- Hàm không có `if`, `for`, `while`, `switch` hay `?:`, nên có 0 điểm rẽ nhánh và 0 nhánh.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` (phần giá trị) là số thực bất kỳ; đạo hàm `f.v[0..1]` bất kỳ (không có điều kiện đường đi) | `f.a = 3.7`, `f.v = {1.0, 0.0}` (chọn bằng `Jet<double, 2>(3.7, 0)`) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nào. Nhánh của `CHECK` cũng không có.

`C2 dự kiến = 0 / 0` (không có nhánh nào; hàm được phủ hoàn toàn bởi 1 test đi qua node 1, dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0146_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// IsNormal bị đánh dấu deprecated, tắt cảnh báo để tránh lỗi khi build với -Werror.
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4996)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

namespace ceres {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(IsNormalJetTest, TC1_P1_SingleStatementPath) {
  const Jet<double, 2> f(3.7, 0);
  const bool result = IsNormal(f);
  (void)result;  // Không kiểm tra kết quả trả về
  SUCCEED();
}

}  // namespace ceres

#if defined(_MSC_VER)
#pragma warning(pop)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
```