**A. Test paths**

CFG của unit (không có điểm rẽ nhánh nào):

`START → node 1 (return isnan(f)) → END`

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh. Đường đi duy nhất. |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có điều kiện đường đi. `f.a` là số thực bất kỳ, các đạo hàm `f.v[i]` cũng bất kỳ. Chọn `f.a` trong [-10, 10] | `Jet<double, 2> f(3.5, 0)`, tức `a = 3.5`, `v = {1, 0}` (giá trị cố định, không dùng hàm sinh số ngẫu nhiên) |

**C. Nhánh không test**

- Không có nhánh nào bị bỏ qua, vì hàm không có điểm rẽ nhánh và không có `CHECK`.
- Không có vòng lặp, nên không cần test số lần lặp.
- `C2 dự kiến = 0 / 0` (không có nhánh nào; đường đi duy nhất P1 được chạy qua, tức độ phủ câu lệnh là 100%).

**D. File test**

```cpp
// FILE: u0145_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Hàm IsNaN bị đánh dấu deprecated, tắt cảnh báo để tránh lỗi khi build với -Werror.
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4996)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

namespace ceres {

// TC1 - Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetIsNaNTest, TC1_P1_StraightLine) {
  Jet<double, 2> f(3.5, 0);
  bool result = IsNaN(f);
  static_cast<void>(result);  // Không kiểm tra kết quả trả về
}

}  // namespace ceres

#if defined(_MSC_VER)
#pragma warning(pop)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
```