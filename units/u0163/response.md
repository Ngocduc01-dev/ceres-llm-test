**A. Test paths**

CFG: `START → 1 → END`. Node 1 là `return NumTraits<T>::max_digits10();`. Hàm không có điểm rẽ nhánh nào, nên tổng số nhánh là 0 và không có vòng lặp.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (đường đi duy nhất) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào. Kiểu template `T` phải có `NumTraits<T>::max_digits10()`, ví dụ `double`. | `NumTraits<ceres::Jet<double, 2>>`, tạo bằng constructor mặc định |

**C. Nhánh không test**

Không có nhánh nào bị bỏ qua và không có `CHECK`.

`C2 dự kiến = 0 / 0` (hàm không có điểm rẽ nhánh nên coi như đạt 100%; test chỉ để đi qua node 1).

**D. File test**

```cpp
// FILE: u0163_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(NumTraitsJetMaxDigits10, P1_SingleStatement) {
  Eigen::NumTraits<ceres::Jet<double, 2>> obj;
  int result = obj.max_digits10();
  (void)result;  // Không kiểm tra kết quả trả về
}
```