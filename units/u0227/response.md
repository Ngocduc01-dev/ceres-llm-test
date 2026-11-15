**Ghi chú:** CFG khớp với mã nguồn (`CellInfo() = default;`, các thành viên `values`, `m` chỉ được khởi tạo mặc định, không có rẽ nhánh). Số điểm rẽ nhánh = 0, nên tổng số nhánh = 0.

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có đầu vào (constructor không tham số) | Không có |

**C. Nhánh không test**

Không có. Unit không có điểm rẽ nhánh và không có vòng lặp, không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có nhánh nào; test P1 phủ toàn bộ node 1, tức đạt 100% theo quy ước).

**D. File test**

```cpp
// FILE: u0227_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_matrix.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(CellInfoTest, DefaultConstructor_P1) {
  CellInfo cell_info;
  (void)cell_info;
}

}  // namespace internal
}  // namespace ceres
```