**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Số phần tử `n` của `FixedArray<int, 20>`, 1 ≤ n ≤ 5. Với n ≤ 20, mảng dùng vùng nhớ inline nên `NonEmptyInlinedStorage::data()` được gọi. | n = 3 (chọn cố định, không dùng số ngẫu nhiên) |

**C. Nhánh không test:** không có. Hàm không có điểm rẽ nhánh nào.
`C2 dự kiến = 0 / 0` (tổng số nhánh là 0, nên coi như phủ đầy đủ; node 1 được chạy qua trong TC1).

Ghi chú: `NonEmptyInlinedStorage` là struct private lồng trong `FixedArray`, nên không thể khai báo `NonEmptyInlinedStorage obj;` trực tiếp từ bên ngoài. Không được sửa mã nguồn Ceres, nên test tạo `FixedArray<int, 20>` với n ≤ 20. Constructor của `FixedArray` gọi `inlined_storage_.data()`, tức là chính unit cần test.

**D. File test**

```cpp
// FILE: u0047_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// TC1 - P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayNonEmptyInlinedStorageData, P1_ReturnBufferPointer) {
  // n = 3 <= 20 nên FixedArray dùng vùng nhớ inline,
  // qua đó gọi NonEmptyInlinedStorage::data().
  ceres::internal::FixedArray<int, 20> array(3);
  (void)array.data();
}
```