**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | Không có điểm rẽ nhánh. Node 2: `CHECK` đúng (`pool_.Wait` trả về true) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `num_threads` từ 1 đến 5. Hàng đợi phải có ít nhất 1 token, nếu không `Wait` sẽ chặn mãi. | `num_threads = 3` (chọn ngẫu nhiên với seed cố định) |

**C. Nhánh không test**

- Node 2, nhánh `CHECK` sai (→ DỪNG): không test (làm chương trình dừng).
- Hàm không có điểm rẽ nhánh và không có vòng lặp nên không có nhánh C2 nào khác.

`C2 dự kiến = 0 / 0` (không có nhánh nào ngoài `CHECK`). Đường đi duy nhất P1 được phủ hoàn toàn nên độ phủ dự kiến là 100%.

**D. File test**

```cpp
// FILE: u0491_test.cc
#include "gtest/gtest.h"
#include "ceres/concurrent_queue.h"
#include "ceres/thread_token_provider.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> 2 (CHECK đúng) -> END
TEST(ThreadTokenProviderAcquire, TC1_AcquireWithAvailableToken) {
  ThreadTokenProvider provider(3);
  provider.Acquire();
}

}  // namespace internal
}  // namespace ceres
```