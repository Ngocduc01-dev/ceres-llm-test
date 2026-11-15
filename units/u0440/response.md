**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, tổng 0 nhánh). Chỉ có `CHECK_LT`, không tính nhánh. Không có vòng lặp.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | node 2: đúng (`begin < end`) |
| (không test) | START → 1 → 2 → DỪNG | node 2: sai (`begin >= end`), `CHECK` làm chương trình dừng |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `data`: mảng `int` 5 phần tử; `begin` ∈ [0, 2]; `end` ∈ [begin+1, 5] | `data = {3, 1, 4, 1, 5}`, `begin = 1`, `end = 4` |

**C. Nhánh không test**

- Nhánh sai của node 2 (`CHECK_LT(begin, end)` sai): không test (làm chương trình dừng). Nhánh này không tính vào mẫu số C2.
- Không có nhánh không thể đi tới.

`C2 dự kiến = 0 / 0` (hàm không có điểm rẽ nhánh; tất cả câu lệnh được chạy qua bởi TC1, tương ứng 100%).

**D. File test**

```cpp
// FILE: u0440_test.cc
#include "gtest/gtest.h"
#include "ceres/cubic_interpolation.h"

// Path P1: START -> 1 -> 2 (đúng: begin < end) -> END
TEST(Grid1DConstructor, BeginLessThanEnd) {
  const int data[5] = {3, 1, 4, 1, 5};
  const int begin = 1;
  const int end = 4;
  ceres::Grid1D<int> grid(data, begin, end);
  (void)grid;
}
```