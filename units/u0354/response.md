**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (0 nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `num_total_jobs`: số nguyên từ 1 đến 5 (constructor không có điều kiện nào ràng buộc giá trị) | 3 |

**C. Nhánh không test**

Không có. Unit không có điểm rẽ nhánh nên không có nhánh nào cần phủ; 1 test đi qua node 1 là đạt phủ toàn bộ node và đường đi duy nhất.

C2 dự kiến = 0 / 0 (không có nhánh; mọi câu lệnh ở node 1 đều được chạy, tương đương 100%).

**D. File test**

```cpp
// FILE: u0354_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_invoke.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BlockUntilFinishedConstructorTest, TC1_P1_SingleStraightPath) {
  ceres::internal::BlockUntilFinished block_until_finished(3);
  SUCCEED();
}
```