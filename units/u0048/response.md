**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Số phần tử `n` của `FixedArray<int, 20>`, 1 ≤ n ≤ 5 (n ≤ 20 nên dùng bộ nhớ inline) | n = 3 |

**C. Nhánh không test**

- Không có nhánh nào bị bỏ qua, vì hàm có 0 điểm rẽ nhánh và thân hàm rỗng.
- `NonEmptyInlinedStorage` là kiểu private của `FixedArray`, nên không thể tạo trực tiếp `NonEmptyInlinedStorage obj;` từ bên ngoài. Test tạo `FixedArray<int, 20>` với `n = 3`. Constructor của nó gọi `storage_.AnnotateConstruct(n)` trên `NonEmptyInlinedStorage`.
- `C2 dự kiến = 0 / 0` (không có nhánh nào; hàm chỉ cần được gọi một lần, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0048_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// P1: START -> END (không có điểm rẽ nhánh)
TEST(FixedArrayNonEmptyInlinedStorageTest, AnnotateConstruct_TC1) {
  // NonEmptyInlinedStorage là kiểu private của FixedArray, nên đi qua constructor
  // của FixedArray<int, 20>: constructor này gọi AnnotateConstruct(3) trên storage inline.
  ceres::internal::FixedArray<int, 20> arr(3);
  SUCCEED();
}
```