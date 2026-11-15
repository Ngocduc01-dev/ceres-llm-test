**A. Test paths**

Unit có 0 điểm rẽ nhánh. CFG khớp với mã nguồn: node 1 gồm member initializer `storage_(std::distance(first, last), a)` và thân hàm `CopyRange(...)`. Chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Số phần tử n trong [1, 5]; giá trị mỗi phần tử trong [1, 100]; `Iterator` = `const int*` (forward iterator hợp lệ); `FixedArray<int, 10>`, allocator mặc định | n = 3; dữ liệu {7, 42, 19} (chọn cố định, tương đương seed cố định) |

**C. Nhánh không test**

- Không có nhánh nào bị bỏ qua. Unit không có điểm rẽ nhánh và không có `CHECK`.
- Unit không có vòng lặp trong thân hàm. Vòng lặp nằm trong `std::distance` và `CopyRange`, nằm ngoài CFG của unit nên không xét.

`C2 dự kiến = 0 / 0` (không có nhánh nào cần phủ; node 1 được chạy qua nên coi như đạt 100%, dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0027_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// TC1 - P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayIteratorCtorTest, TC1_ConstructFromForwardIteratorRange) {
  const int data[3] = {7, 42, 19};
  const int* first = data;
  const int* last = data + 3;
  ceres::internal::FixedArray<int, 10> arr(first, last);
  (void)arr;
}
```