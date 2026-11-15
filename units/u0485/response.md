**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, tổng số nhánh = 0). Chỉ có 1 lệnh `CHECK` ở node 1. CFG khớp với mã nguồn.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | node 1: CHECK đúng (`options_.enable_fast_removal == true`); không có nhánh nào tính vào C2 |

Đường `START → 1 → DỪNG` (CHECK sai) không được test.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `Problem::Options::enable_fast_removal` = `true` (bắt buộc để CHECK đúng). Không có đầu vào nào khác, không dùng số ngẫu nhiên. | `enable_fast_removal = true` |

**C. Nhánh không test**

- Nhánh CHECK sai (node 1 → DỪNG): không test (làm chương trình dừng).
- Không có nhánh không thể đi tới nào khác.

C2 dự kiến = 0 / 0 (hàm không có điểm rẽ nhánh nên không có nhánh tính vào C2; test vẫn đi qua toàn bộ hàm, tức phủ 100% câu lệnh).

**D. File test**

```cpp
// FILE: u0485_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 (CHECK đúng) -> END
TEST(ProblemImplResidualBlockSet, FastRemovalEnabled) {
  ceres::Problem::Options options;
  options.enable_fast_removal = true;
  ceres::internal::ProblemImpl problem(options);
  problem.residual_block_set();
}
```