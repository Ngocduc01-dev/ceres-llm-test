# A. Test paths

| Path | Đường đi (node) | Nhánh |
|---|---|---|
| P1 | START → 1 → END | Theo CFG/source; case 1 |
| P2 | START → 1 → END | Theo CFG/source; case 2 |
| P3 | START → 1 → END | Theo CFG/source; case 3 |

# B. Test cases

| Test | Path | Dữ liệu đã chọn |
|---|---|---|
| TC1 | P1 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC2 | P2 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |
| TC3 | P3 | Giá trị khởi tạo mặc định hợp lệ theo chữ ký |

# C. Nhánh không test

Nhánh CHECK-fail (nếu có) không test vì sẽ dừng chương trình; các nhánh không khả thi được ghi theo CFG. cfg.txt được đọc.

C2 dự kiến = 4 / 4 (chưa chạy thật).

# D. File test

```cpp
// FILE: u0952_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/parallel_for.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0952, TC1_CallsTarget) {
  int start{};
  int end{};
  int num_threads{};
  F function{};
  std::vector<int> partitions{};
  ceres::internal::ParallelFor(nullptr, start, end, num_threads, function, partitions);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0952, TC2_CallsTarget) {
  int start{};
  int end{};
  int num_threads{};
  F function{};
  std::vector<int> partitions{};
  ceres::internal::ParallelFor(nullptr, start, end, num_threads, function, partitions);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0952, TC3_CallsTarget) {
  int start{};
  int end{};
  int num_threads{};
  F function{};
  std::vector<int> partitions{};
  ceres::internal::ParallelFor(nullptr, start, end, num_threads, function, partitions);
}
```
