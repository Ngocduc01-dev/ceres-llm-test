**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào (tổng số nhánh = 0) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `minimizer_type` ∈ {LINE_SEARCH, TRUST_REGION}; `log_to_stdout` ∈ {true, false} | `minimizer_type = TRUST_REGION`, `log_to_stdout = false` |

**C. Nhánh không test:** Không có (hàm không có điểm rẽ nhánh nào, không có `CHECK`). Ghi chú: CFG khớp với mã nguồn (`= default`).
`C2 dự kiến = 0 / 0` (không có nhánh nào; unit được phủ hoàn toàn khi destructor chạy một lần, tức 100%).

**D. File test**

```cpp
// FILE: u0250_test.cc
#include "gtest/gtest.h"
#include "ceres/callbacks.h"

namespace ceres {
namespace internal {

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(LoggingCallbackDestructorTest, P1_DestroyObject) {
  // Object được cấp phát động; delete sẽ gọi ~LoggingCallback() đúng một lần.
  LoggingCallback* callback =
      new LoggingCallback(TRUST_REGION, /*log_to_stdout=*/false);
  delete callback;
}

}  // namespace internal
}  // namespace ceres
```