**CFG của unit** (không có điểm rẽ nhánh; `end()` là lời gọi hàm khác, không tính):

- node 1: `return end();`
- START → 1 → END

Tổng số điểm rẽ nhánh: 0, tổng số nhánh: 0.

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `n` (kích thước mảng) từ 1 đến 5, giá trị khởi tạo `val` từ 0 đến 100 (seed cố định 12345) | n = 3, val = 42 |

**C. Nhánh không test:** Không có. Hàm không có điểm rẽ nhánh nào.
`C2 dự kiến = 0 / 0` (hàm chỉ có một đường đi duy nhất, nên coi như đạt 100% khi P1 được chạy).

**D. File test:**

```cpp
// FILE: u0039_test.cc
#include <memory>
#include <random>

#include "ceres/internal/fixed_array.h"
#include "gtest/gtest.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayCend, SinglePath) {
  std::mt19937 gen(12345);
  std::uniform_int_distribution<int> size_dist(1, 5);
  std::uniform_int_distribution<int> val_dist(0, 100);
  const size_t n = static_cast<size_t>(size_dist(gen));
  const int val = val_dist(gen);

  ceres::internal::FixedArray<int, 5> arr(n, val, std::allocator<int>());
  auto it = arr.cend();
  (void)it;
}
```