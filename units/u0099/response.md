**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh. Node 1 là lệnh tuần tự `return std::isnormal(x)`. |

CFG khớp với mã nguồn. Hàm chỉ có một lệnh return nên không có vòng lặp và không có `CHECK`.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `x` là số thực `double` bất kỳ, không có ràng buộc từ đường đi (chọn trong [1.0, 100.0]) | `x = 37.5` (cố định, không dùng hàm sinh số ngẫu nhiên) |

**C. Nhánh không test**

Không có. Hàm có 0 điểm rẽ nhánh, nên tổng số nhánh là 0 và một test đi qua P1 là đủ phủ toàn bộ hàm.

`C2 dự kiến = 0 / 0 (không có nhánh nào, coi như 100%; test đi qua 1/1 đường đi của hàm)`

**D. File test**

```cpp
// FILE: u0099_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// IsNormal bị đánh dấu deprecated, tắt cảnh báo để tránh lỗi khi build có -Werror.
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4996)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(IsNormalTest, TC1_P1_StraightLine) {
  const double x = 37.5;
  (void)ceres::IsNormal(x);
}

#if defined(_MSC_VER)
#pragma warning(pop)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
```