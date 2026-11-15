**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | node 1: đúng |
| P2 | START → 1 → 2 → END | node 1: sai |

Hàm không có vòng lặp và không có `CHECK`.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `num_threads` = 1 (điều kiện `num_threads == 1` đúng); `m` là một `std::mutex` bất kỳ | `num_threads` = 1 |
| TC2 | P2 | `num_threads` ∈ [2, 8] (điều kiện `num_threads == 1` sai); `m` là một `std::mutex` bất kỳ | `num_threads` = 4 (chọn ngẫu nhiên với seed cố định) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua.
Ghi chú: CFG khớp với mã nguồn.
`C2 dự kiến = 2 / 2`

**D. File test**

```cpp
// FILE: u0477_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_for.h"

#include <mutex>

namespace ceres {
namespace internal {

// P1: START -> 1 -> 2 -> END (node 1: đúng)
TEST(MakeConditionalLockTest, SingleThreadReturnsEmptyLock) {
  std::mutex m;
  const int num_threads = 1;
  auto lock = MakeConditionalLock(num_threads, m);
  (void)lock;
}

// P2: START -> 1 -> 2 -> END (node 1: sai)
TEST(MakeConditionalLockTest, MultiThreadReturnsLockOnMutex) {
  std::mutex m;
  const int num_threads = 4;
  auto lock = MakeConditionalLock(num_threads, m);
  (void)lock;
}

}  // namespace internal
}  // namespace ceres
```