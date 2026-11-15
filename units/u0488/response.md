**A. Test paths**

Điểm rẽ nhánh duy nhất là node 1 (`while (begin != new_end)`), nên có 2 nhánh. Số lần lặp bằng số phần tử khác nhau sau `unique`.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | node 1: sai (0 lần lặp) |
| P2 | START → 1 → 2 → 1 → END | node 1: đúng, đúng→sai (1 lần lặp) |
| P3 | START → (1 → 2) ×2 → 1 → END | node 1: đúng ×2, rồi sai (2 lần lặp) |
| P4 | START → (1 → 2) ×3 → 1 → END | node 1: đúng ×3, rồi sai (3 lần lặp, giá trị ở giữa) |
| P5 | START → (1 → 2) ×4 → 1 → END | node 1: đúng ×4, rồi sai (n−1 lần lặp) |
| P6 | START → (1 → 2) ×5 → 1 → END | node 1: đúng ×5, rồi sai (n lần lặp) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | vector rỗng (size = 0) | `{}` |
| TC2 | P2 | size = 1, con trỏ khác nhau | `{new int(7)}` |
| TC3 | P3 | size = 2, con trỏ khác nhau | `{new int(3), new int(9)}` |
| TC4 | P4 | size = 3, con trỏ khác nhau | 3 con trỏ `new int(...)` |
| TC5 | P5 | size = 4, con trỏ khác nhau | 4 con trỏ `new int(...)` |
| TC6 | P6 | size = 5 (tối đa theo yêu cầu), con trỏ khác nhau | 5 con trỏ `new int(...)` |

**C. Nhánh không test**

- Không có nhánh không thể đi tới và không có `CHECK`.
- Số lần lặp n+1 = 6 không làm được vì đầu vào bị giới hạn tối đa 5 phần tử.
- Ghi chú: CFG dựng với `CostFunction*`, nhưng hàm là template nên test dùng `int*` (`#include` ở mục 3.3 không có `CostFunction`). Luồng điều khiển không đổi.

`C2 dự kiến = 2 / 2`

**D. File test**

```cpp
// FILE: u0488_test.cc
#include <vector>

#include "gtest/gtest.h"
#include "ceres/stl_util.h"

// Path P1: START -> 1 -> END (node 1: sai, 0 lần lặp)
TEST(STLDeleteUniqueContainerPointersTest, ZeroElements) {
  std::vector<int*> v;
  ceres::STLDeleteUniqueContainerPointers(v.begin(), v.end());
}

// Path P2: START -> 1 -> 2 -> 1 -> END (node 1: đúng rồi sai, 1 lần lặp)
TEST(STLDeleteUniqueContainerPointersTest, OneElement) {
  std::vector<int*> v;
  v.push_back(new int(7));
  ceres::STLDeleteUniqueContainerPointers(v.begin(), v.end());
}

// Path P3: (1 -> 2) x2 -> 1 -> END (node 1: đúng x2 rồi sai, 2 lần lặp)
TEST(STLDeleteUniqueContainerPointersTest, TwoElements) {
  std::vector<int*> v;
  v.push_back(new int(3));
  v.push_back(new int(9));
  ceres::STLDeleteUniqueContainerPointers(v.begin(), v.end());
}

// Path P4: (1 -> 2) x3 -> 1 -> END (node 1: đúng x3 rồi sai, 3 lần lặp)
TEST(STLDeleteUniqueContainerPointersTest, ThreeElements) {
  std::vector<int*> v;
  v.push_back(new int(5));
  v.push_back(new int(2));
  v.push_back(new int(8));
  ceres::STLDeleteUniqueContainerPointers(v.begin(), v.end());
}

// Path P5: (1 -> 2) x4 -> 1 -> END (node 1: đúng x4 rồi sai, 4 lần lặp)
TEST(STLDeleteUniqueContainerPointersTest, FourElements) {
  std::vector<int*> v;
  v.push_back(new int(1));
  v.push_back(new int(6));
  v.push_back(new int(4));
  v.push_back(new int(10));
  ceres::STLDeleteUniqueContainerPointers(v.begin(), v.end());
}

// Path P6: (1 -> 2) x5 -> 1 -> END (node 1: đúng x5 rồi sai, 5 lần lặp)
TEST(STLDeleteUniqueContainerPointersTest, FiveElements) {
  std::vector<int*> v;
  v.push_back(new int(11));
  v.push_back(new int(3));
  v.push_back(new int(7));
  v.push_back(new int(2));
  v.push_back(new int(9));
  ceres::STLDeleteUniqueContainerPointers(v.begin(), v.end());
}
```