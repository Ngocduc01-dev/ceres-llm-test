**A. Test paths**

Hàm có 0 điểm rẽ nhánh, nên chỉ có 1 đường đi. CFG khớp với mã nguồn. Phép so sánh `==` trong lambda ở dòng 62 là biểu thức trả về giá trị, không phải điểm rẽ nhánh trong CFG.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `num_total_jobs` = 0, để `wait` thoát ngay vì `num_total_jobs_finished_` (khởi tạo 0) bằng `num_total_jobs_`. Cách này không cần đa luồng và không bị treo. | 0 |

**C. Nhánh không test**

Không có. Vòng lặp: `wait` có vòng kiểm tra điều kiện bên trong thư viện chuẩn, không nằm trong CFG của unit. Test chỉ chạy 0 lần chờ để tránh đa luồng và treo chương trình.

`C2 dự kiến = 0 / 0` (không có nhánh nào, nên coi như đạt 100%; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0355_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_invoke.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BlockUntilFinishedBlock, TC1_NoJobsReturnsImmediately) {
  ceres::internal::BlockUntilFinished block_until_finished(0);
  block_until_finished.Block();
}
```