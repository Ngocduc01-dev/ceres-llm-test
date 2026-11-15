**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Kích thước mảng `n` từ 1 đến 5 (không có điều kiện đường đi, hàm không có tham số dùng đến) | `n = 3` |

**C. Nhánh không test**

- Không có nhánh nào, vì hàm không có điểm rẽ nhánh.
- Ghi chú: `EmptyInlinedStorage` là struct private lồng trong `FixedArray`, nên không tạo trực tiếp `EmptyInlinedStorage obj;` được mà không sửa mã nguồn. Test dùng `FixedArray<int, 0>`, có `EmptyInlinedStorage` làm storage nội tuyến. Destructor của `FixedArray` gọi `storage_.AnnotateDestruct(size())`, tức là gọi đúng unit này.
- C2 dự kiến = 0 / 0 (không có nhánh; unit được chạy qua P1 duy nhất, tức 100%).

**D. File test**

```cpp
// FILE: u0052_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// P1: START -> END (không có điểm rẽ nhánh)
// EmptyInlinedStorage::AnnotateDestruct được gọi gián tiếp trong destructor
// của FixedArray<int, 0> khi đối tượng ra khỏi phạm vi.
TEST(FixedArrayEmptyInlinedStorageTest, AnnotateDestructPathP1) {
  {
    ceres::internal::FixedArray<int, 0> arr(3);
  }
  SUCCEED();
}
```