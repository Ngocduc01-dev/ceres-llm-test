**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Tham số `size_type` không được dùng và không có điều kiện ràng buộc. Chọn kích thước mảng `n` trong khoảng 1 đến 5. | `n = 3` (chọn ngẫu nhiên, cố định) |

**C. Nhánh không test**

- Không có nhánh nào, vì hàm có 0 điểm rẽ nhánh và không có vòng lặp.
- Ghi chú về cách gọi: `EmptyInlinedStorage` là struct private lồng trong template `FixedArray<T, N, A>`, nên không thể viết `EmptyInlinedStorage obj;` ngoài class. Test này tạo `FixedArray<int, 0>`. Constructor public của nó khởi tạo `EmptyInlinedStorage` và gọi `AnnotateConstruct(n)`. Cách này không sửa mã nguồn và không dùng hack `#define private public`.

`C2 dự kiến = 0 / 0` (không có nhánh nào; hàm được chạy qua 1 test, đạt 100% câu lệnh; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0051_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// TC1 - P1: START -> END (không có điểm rẽ nhánh)
TEST(FixedArrayEmptyInlinedStorageTest, AnnotateConstruct_TC1_P1) {
  // FixedArray<int, 0> dùng EmptyInlinedStorage; constructor gọi
  // AnnotateConstruct(n) đúng một lần. Không kiểm tra kết quả.
  ceres::internal::FixedArray<int, 0> arr(3);
  (void)arr;
}
```