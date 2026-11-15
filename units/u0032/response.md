**A. Test paths**

Hàm `front()` không có điểm rẽ nhánh nào (CFG khớp với mã nguồn). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Mảng `FixedArray<int, 12>` có n phần tử, n từ 1 đến 5 (front() cần mảng không rỗng); giá trị phần tử val từ 0 đến 100 | n = 3, val = 42 (chọn ngẫu nhiên trong khoảng) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên tổng số nhánh là 0 và không có nhánh `CHECK` nào.

C2 dự kiến = 0 / 0 (không có nhánh nào; node 1 được chạy qua nên đạt độ phủ câu lệnh 100%)

**D. File test**

```cpp
// FILE: u0032_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayFront, SinglePath) {
  // n = 3, val = 42
  ceres::internal::FixedArray<int, 12> array(3, 42);
  int& first = array.front();
  (void)first;
}
```