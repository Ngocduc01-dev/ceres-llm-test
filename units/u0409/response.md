**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

CFG khớp với mã nguồn (`return token_;`).

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `num_threads` của `ThreadTokenProvider` thuộc [1, 5] | 3 |

**C. Nhánh không test**

- Không có nhánh nào, vì hàm không có điểm rẽ nhánh và không có vòng lặp.
- `C2 dự kiến = 0 / 0` (tổng số nhánh bằng 0, nên mọi dòng lệnh của hàm đều được chạy qua test P1).

**D. File test**

```cpp
// FILE: u0409_test.cc
#include "gtest/gtest.h"
#include "ceres/scoped_thread_token.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ScopedThreadTokenTokenTest, P1_ReturnToken) {
  ThreadTokenProvider provider(3);
  ScopedThreadToken scoped_token(&provider);
  int value = scoped_token.token();
  (void)value;
}

}  // namespace internal
}  // namespace ceres
```

Lưu ý: `ThreadTokenProvider` không nằm trong danh sách `#include` ở mục 3.3, nhưng được khai báo trong `scoped_thread_token.h` (qua `thread_token_provider.h`). Kiểu này cần có để tạo `ScopedThreadToken`.