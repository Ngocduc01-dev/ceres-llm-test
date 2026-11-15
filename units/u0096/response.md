**A. Test paths**

Hàm không có điểm rẽ nhánh (khớp với mã nguồn; dòng 510 chỉ là attribute `CERES_DEPRECATED_WITH_MSG`, không ảnh hưởng luồng điều khiển). Chỉ có 1 đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `x` là số thực bất kỳ (không có điều kiện đường đi) | `x = 3.25` (cố định, seed không cần vì không dùng sinh số ngẫu nhiên) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên tổng số nhánh = 0.
`C2 dự kiến = 0 / 0` (không có nhánh nào, mọi câu lệnh đều được phủ bởi TC1).

Lưu ý: `IsFinite` được đánh dấu `CERES_DEPRECATED_WITH_MSG` nên gọi hàm có thể sinh cảnh báo deprecated khi biên dịch. File test dùng `#pragma` để tắt cảnh báo này, tránh lỗi nếu bật `-Werror`.

**D. File test**

```cpp
// FILE: u0096_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

#if defined(_MSC_VER)
#pragma warning(disable : 4996)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(IsFinite, P1_TC1_NoBranch) {
  double x = 3.25;
  // Không kiểm tra kết quả trả về, chỉ gọi hàm một lần.
  (void)ceres::IsFinite(x);
}
```