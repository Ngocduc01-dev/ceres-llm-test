**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số. Đối tượng là `FixedArray<int, 0>` với kích thước 0, vì N = 0 nên dùng `EmptyInlinedStorage` | Kích thước = 0 |

**C. Nhánh không test**

- Không có nhánh nào cần loại. Hàm không có điểm rẽ nhánh và không có `CHECK`.
- Lưu ý: `EmptyInlinedStorage` nhiều khả năng là kiểu `private` của `FixedArray`. Vì không được sửa mã nguồn, test tạo `FixedArray<int, 0>` và gọi `data()` của nó. Hàm này chuyển tiếp tới `EmptyInlinedStorage::data()` (node 1). Nếu `EmptyInlinedStorage` là `public`, có thể thay bằng `EmptyInlinedStorage obj; obj.data();`.
- `C2 dự kiến = 0 / 0` (không có nhánh nào, node 1 được chạy hết nên coi là 100%, dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0050_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// TC1 - P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayEmptyInlinedStorageData, ReturnsNullptrPath) {
  ceres::internal::FixedArray<int, 0> arr(0);
  arr.data();
}
```