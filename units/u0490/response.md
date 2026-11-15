**A. Test paths**

Unit chỉ có 1 điểm rẽ nhánh: node 2 (`i < num_threads`). Tổng số nhánh = 2. Node 1 không phải điểm rẽ nhánh. Số lần lặp bằng `num_threads`, nên chọn giới hạn n = 5 để giữ dữ liệu nhỏ.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | node 2: sai (0 lần lặp) |
| P2 | START → 1 → 2 → 3 → 4 → 2 → END | node 2: đúng (1 lần), rồi sai |
| P3 | START → 1 → (2 → 3 → 4) ×2 → 2 → END | node 2: đúng ×2, rồi sai |
| P4 | START → 1 → (2 → 3 → 4) ×3 → 2 → END | node 2: đúng ×3 (số ở giữa), rồi sai |
| P5 | START → 1 → (2 → 3 → 4) ×4 → 2 → END | node 2: đúng ×4 (n−1), rồi sai |
| P6 | START → 1 → (2 → 3 → 4) ×5 → 2 → END | node 2: đúng ×5 (n), rồi sai |
| P7 | START → 1 → (2 → 3 → 4) ×6 → 2 → END | node 2: đúng ×6 (n+1), rồi sai |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `num_threads` ≤ 0 | 0 |
| TC2 | P2 | `num_threads` = 1 | 1 |
| TC3 | P3 | `num_threads` = 2 | 2 |
| TC4 | P4 | `num_threads` = 3 | 3 |
| TC5 | P5 | `num_threads` = 4 | 4 |
| TC6 | P6 | `num_threads` = 5 | 5 |
| TC7 | P7 | `num_threads` = 6 | 6 |

Số lần lặp bằng đúng `num_threads` nên các khoảng chỉ có một giá trị, không cần sinh số ngẫu nhiên. Các giá trị 0, 1, 2, 3, 4, 5, 6 ứng với các mức 0, 1, 2, giữa, n−1, n, n+1 của vòng lặp.

**C. Nhánh không test**

Không có. Nhánh đúng và nhánh sai của node 2 đều đi tới được.
`C2 dự kiến = 2 / 2` (dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0490_test.cc
#include "gtest/gtest.h"
#include "ceres/concurrent_queue.h"
#include "ceres/thread_token_provider.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> 2(sai) -> END
TEST(ThreadTokenProviderCtorTest, TC1_ZeroThreads) {
  ThreadTokenProvider provider(0);
}

// P2: START -> 1 -> 2(đúng) -> 3 -> 4 -> 2(sai) -> END
TEST(ThreadTokenProviderCtorTest, TC2_OneThread) {
  ThreadTokenProvider provider(1);
}

// P3: START -> 1 -> (2(đúng) -> 3 -> 4) x2 -> 2(sai) -> END
TEST(ThreadTokenProviderCtorTest, TC3_TwoThreads) {
  ThreadTokenProvider provider(2);
}

// P4: START -> 1 -> (2(đúng) -> 3 -> 4) x3 -> 2(sai) -> END
TEST(ThreadTokenProviderCtorTest, TC4_ThreeThreads) {
  ThreadTokenProvider provider(3);
}

// P5: START -> 1 -> (2(đúng) -> 3 -> 4) x4 -> 2(sai) -> END
TEST(ThreadTokenProviderCtorTest, TC5_FourThreads) {
  ThreadTokenProvider provider(4);
}

// P6: START -> 1 -> (2(đúng) -> 3 -> 4) x5 -> 2(sai) -> END
TEST(ThreadTokenProviderCtorTest, TC6_FiveThreads) {
  ThreadTokenProvider provider(5);
}

// P7: START -> 1 -> (2(đúng) -> 3 -> 4) x6 -> 2(sai) -> END
TEST(ThreadTokenProviderCtorTest, TC7_SixThreads) {
  ThreadTokenProvider provider(6);
}

}  // namespace internal
}  // namespace ceres
```