**A. Test paths**

Ghi chú: CFG khớp với mã nguồn. Node 2 gồm `++begin` và `delete *temp` (dòng 51–53) và không có rẽ nhánh. Test dùng `std::vector<int*>` thay cho `vector<mutex*>`. Cả hai đều là con trỏ cấp phát bằng `new`, nên CFG không đổi.

Điểm rẽ nhánh duy nhất là node 1, nên có 2 nhánh. Số lần lặp bị chặn bởi số phần tử n của dải `[begin, end)`. Với giới hạn tối đa 5 phần tử, n = 5 nên chọn 0, 1, 2, 3 (giữa), 4 (n−1), 5 (n) lần lặp.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | node 1: sai (0 lần lặp) |
| P2 | START → 1 → 2 → 1 → END | node 1: đúng, rồi sai (1 lần lặp) |
| P3 | START → 1 → 2 → 1 → 2 → 1 → END | node 1: đúng, đúng, rồi sai (2 lần lặp) |
| P4 | START → (1 → 2) × 3 → 1 → END | node 1: đúng × 3, rồi sai (3 lần lặp) |
| P5 | START → (1 → 2) × 4 → 1 → END | node 1: đúng × 4, rồi sai (4 lần lặp = n−1) |
| P6 | START → (1 → 2) × 5 → 1 → END | node 1: đúng × 5, rồi sai (5 lần lặp = n) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | số phần tử = 0 (`begin == end`) | vector rỗng |
| TC2 | P2 | số phần tử = 1; giá trị phần tử bất kỳ | {17} |
| TC3 | P3 | số phần tử = 2; giá trị phần tử bất kỳ | {5, 83} |
| TC4 | P4 | số phần tử = 3; giá trị phần tử bất kỳ | {29, 61, 4} |
| TC5 | P5 | số phần tử = 4; giá trị phần tử bất kỳ | {12, 90, 37, 58} |
| TC6 | P6 | số phần tử = 5; giá trị phần tử bất kỳ | {71, 3, 46, 25, 99} |

**C. Nhánh không test**

- Không có nhánh không thể đi tới và không có nhánh `CHECK`.
- Số lần lặp n+1 = 6 không làm được vì vượt giới hạn 5 phần tử của yêu cầu.
- `C2 dự kiến = 2 / 2` (dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0487_test.cc
#include "gtest/gtest.h"
#include "ceres/stl_util.h"

namespace ceres {
namespace internal {

namespace {

// Tạo vector con trỏ int cấp phát động từ các giá trị cho trước.
std::vector<int*> MakePointers(const std::vector<int>& values) {
  std::vector<int*> result;
  for (size_t i = 0; i < values.size(); ++i) {
    result.push_back(new int(values[i]));
  }
  return result;
}

}  // namespace

// P1: node 1: sai (0 lần lặp)
TEST(STLDeleteContainerPointersTest, TC1_ZeroIterations) {
  std::vector<int*> v;
  STLDeleteContainerPointers(v.begin(), v.end());
}

// P2: node 1: đúng, sai (1 lần lặp)
TEST(STLDeleteContainerPointersTest, TC2_OneIteration) {
  std::vector<int*> v = MakePointers({17});
  STLDeleteContainerPointers(v.begin(), v.end());
}

// P3: node 1: đúng, đúng, sai (2 lần lặp)
TEST(STLDeleteContainerPointersTest, TC3_TwoIterations) {
  std::vector<int*> v = MakePointers({5, 83});
  STLDeleteContainerPointers(v.begin(), v.end());
}

// P4: node 1: đúng x3, sai (3 lần lặp, giá trị ở giữa)
TEST(STLDeleteContainerPointersTest, TC4_ThreeIterations) {
  std::vector<int*> v = MakePointers({29, 61, 4});
  STLDeleteContainerPointers(v.begin(), v.end());
}

// P5: node 1: đúng x4, sai (4 lần lặp = n-1)
TEST(STLDeleteContainerPointersTest, TC5_FourIterations) {
  std::vector<int*> v = MakePointers({12, 90, 37, 58});
  STLDeleteContainerPointers(v.begin(), v.end());
}

// P6: node 1: đúng x5, sai (5 lần lặp = n)
TEST(STLDeleteContainerPointersTest, TC6_FiveIterations) {
  std::vector<int*> v = MakePointers({71, 3, 46, 25, 99});
  STLDeleteContainerPointers(v.begin(), v.end());
}

}  // namespace internal
}  // namespace ceres
```