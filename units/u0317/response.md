**A. Test paths**

Destructor `= default` không có điểm rẽ nhánh nào (CFG khớp mã nguồn). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có nhánh (0 điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `max_num_iterations` từ 1 đến 5 (tạo object rồi huỷ khi ra khỏi phạm vi) | 3 (chọn ngẫu nhiên trong khoảng) |

**C. Nhánh không test**

Không có nhánh nào (tổng số nhánh = 0, không có vòng lặp, không có `CHECK`).
`C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ; đường đi P1 được chạy qua khi object bị huỷ).

**D. File test**

```cpp
// FILE: u0317_test.cc
#include "gtest/gtest.h"
#include "ceres/iterative_refiner.h"

namespace ceres {
namespace internal {

// Path P1: START -> END (destructor mặc định, không có nhánh)
TEST(SparseIterativeRefinerDestructorTest, DestroyObject) {
  {
    SparseIterativeRefiner refiner(3);
  }  // destructor ~SparseIterativeRefiner() được gọi ở đây
  SUCCEED();
}

}  // namespace internal
}  // namespace ceres
```