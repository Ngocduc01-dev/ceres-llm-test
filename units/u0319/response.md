**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `max_num_iterations` (constructor) là số nguyên bất kỳ, chọn từ 1 đến 5 | 3 |

**C. Nhánh không test**

Không có. Hàm huỷ `= default` không có điểm rẽ nhánh nào (tổng số nhánh = 0). Ghi chú: CFG khớp với mã nguồn. Destructor được gọi khi object ra khỏi phạm vi, nên test chỉ cần tạo object trong một khối `{ }` rồi để nó bị huỷ.

`C2 dự kiến = 0 / 0` (không có nhánh nào; đường START → END được đi qua 1 lần).

**D. File test**

```cpp
// FILE: u0319_test.cc
#include "gtest/gtest.h"
#include "ceres/iterative_refiner.h"

namespace ceres {
namespace internal {

// Path P1: START -> END
TEST(DenseIterativeRefinerDestructorTest, DestroyObject) {
  {
    DenseIterativeRefiner refiner(3);
  }  // destructor ~DenseIterativeRefiner() được gọi tại đây
  SUCCEED();
}

}  // namespace internal
}  // namespace ceres
```