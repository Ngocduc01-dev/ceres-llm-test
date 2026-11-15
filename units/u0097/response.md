**A. Test paths**

Hàm có 0 điểm rẽ nhánh, CFG chỉ có một đường đi duy nhất. CFG khớp với mã nguồn. Dòng 512 là macro `CERES_DEPRECATED_WITH_MSG`, không ảnh hưởng luồng điều khiển.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `x` là số thực bất kỳ (không có điều kiện đường đi). Chọn trong [-100, 100] | `x = 37.5` |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên không có nhánh nào bị bỏ sót.

`C2 dự kiến = 0 / 0` (tổng số nhánh là 0, nên C2 được coi là đạt 100% khi P1 chạy qua).

**D. File test**

```cpp
// FILE: u0097_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(IsInfinite, P1_SingleStatement) {
  const double x = 37.5;
  // Không kiểm tra kết quả trả về; chỉ gọi hàm để đi qua node 1.
  // Hàm bị đánh dấu deprecated nên tắt cảnh báo xung quanh lệnh gọi.
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4996)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
  bool result = ceres::IsInfinite(x);
#if defined(_MSC_VER)
#pragma warning(pop)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
  (void)result;
}
```