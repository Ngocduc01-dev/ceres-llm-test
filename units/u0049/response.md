**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Tham số `size_type` không được đặt tên và không được dùng, nên không ràng buộc. Với `FixedArray<int, 20>` thì kích thước n ∈ [1, 5] | n = 3 (chọn ngẫu nhiên, cố định) |

**C. Nhánh không test**

Không có. Hàm có 0 điểm rẽ nhánh và không có `CHECK`.

C2 dự kiến = 0 / 0 (không có nhánh nào; đường START → END được chạy qua 1 lần, tương đương 100%).

Ghi chú: `NonEmptyInlinedStorage` là nested struct private của `FixedArray`, nên không tạo trực tiếp `NonEmptyInlinedStorage obj;` được ở ngoài class. Test tạo `FixedArray<int, 20>` và để destructor của nó gọi `storage_.AnnotateDestruct(size())`. Cách này vẫn chạy đúng unit trên object `NonEmptyInlinedStorage`.

**D. File test**

```cpp
// FILE: u0049_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

namespace ceres {
namespace internal {

// P1: START -> END (không có điểm rẽ nhánh)
// AnnotateDestruct được gọi khi FixedArray bị huỷ (kết thúc phạm vi khối bên dưới).
TEST(NonEmptyInlinedStorageAnnotateDestruct, P1_StartToEnd) {
  {
    FixedArray<int, 20> arr(3);
  }
  SUCCEED();
}

}  // namespace internal
}  // namespace ceres
```