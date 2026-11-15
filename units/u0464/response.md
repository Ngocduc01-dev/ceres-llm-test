**A. Test paths**

CFG khớp với mã nguồn. Hàm có 1 điểm rẽ nhánh (node 2), nên tổng số nhánh là 2.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | node 2: sai (0 lần lặp) |
| P2 | START → 1 → 2 → 3 → 4 → 2 → END | node 2: đúng, sai (1 lần lặp) |
| P3 | START → 1 → (2 → 3 → 4) ×2 → 2 → END | node 2: đúng ×2, rồi sai (2 lần lặp) |
| P4 | START → 1 → (2 → 3 → 4) ×3 → 2 → END | node 2: đúng ×3, rồi sai (3 lần lặp) |
| P5 | START → 1 → (2 → 3 → 4) ×4 → 2 → END | node 2: đúng ×4, rồi sai (4 lần lặp) |
| P6 | START → 1 → (2 → 3 → 4) ×5 → 2 → END | node 2: đúng ×5, rồi sai (5 lần lặp) |

**B. Bộ test case**

Số lần lặp bằng `size`. Chọn n = 5, nên cần các số lần lặp 0, 1, 2, 3 (ở giữa), 4 (n−1), 5 (n). Giá trị phần tử lấy trong khoảng [−5, 5], đã chọn ngẫu nhiên với seed cố định và ghi cứng trong code.

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | size = 0; mảng có ≥ 1 phần tử | size = 0, array = {7} |
| TC2 | P2 | size = 1; phần tử ∈ [−5, 5] | size = 1, array = {3} |
| TC3 | P3 | size = 2; phần tử ∈ [−5, 5] | size = 2, array = {4, −2} |
| TC4 | P4 | size = 3; phần tử ∈ [−5, 5] | size = 3, array = {2, 2, −1} (có trùng) |
| TC5 | P5 | size = 4; phần tử ∈ [−5, 5] | size = 4, array = {5, 0, 5, −3} (có trùng) |
| TC6 | P6 | size = 5; phần tử ∈ [−5, 5] | size = 5, array = {1, −4, 1, 3, −4} (có trùng) |

**C. Nhánh không test**

- Không có nhánh nào bị bỏ (không có `CHECK` trong hàm).
- Số lần lặp n+1 = 6 không làm được: vòng lặp luôn chạy đúng `size` lần, và mảng bị giới hạn tối đa 5 phần tử.

`C2 dự kiến = 2 / 2`

**D. File test**

```cpp
// FILE: u0464_test.cc
#include "gtest/gtest.h"
#include "ceres/array_utils.h"

namespace ceres {
namespace internal {

// Path P1: node 2: sai (0 lần lặp)
TEST(MapValuesToContiguousRangeTest, ZeroIterations) {
  int array[1] = {7};
  MapValuesToContiguousRange(0, array);
}

// Path P2: node 2: đúng, sai (1 lần lặp)
TEST(MapValuesToContiguousRangeTest, OneIteration) {
  int array[1] = {3};
  MapValuesToContiguousRange(1, array);
}

// Path P3: node 2: đúng x2, sai (2 lần lặp)
TEST(MapValuesToContiguousRangeTest, TwoIterations) {
  int array[2] = {4, -2};
  MapValuesToContiguousRange(2, array);
}

// Path P4: node 2: đúng x3, sai (3 lần lặp, giá trị giữa)
TEST(MapValuesToContiguousRangeTest, ThreeIterations) {
  int array[3] = {2, 2, -1};
  MapValuesToContiguousRange(3, array);
}

// Path P5: node 2: đúng x4, sai (4 lần lặp, n-1)
TEST(MapValuesToContiguousRangeTest, FourIterations) {
  int array[4] = {5, 0, 5, -3};
  MapValuesToContiguousRange(4, array);
}

// Path P6: node 2: đúng x5, sai (5 lần lặp, n)
TEST(MapValuesToContiguousRangeTest, FiveIterations) {
  int array[5] = {1, -4, 1, 3, -4};
  MapValuesToContiguousRange(5, array);
}

}  // namespace internal
}  // namespace ceres
```