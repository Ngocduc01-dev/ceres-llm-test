**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào, nên không có nhánh để chọn |

CFG khớp với mã nguồn. Dòng 47 là destructor `= default`, không có câu lệnh nào và không có điều kiện.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `program`: bất kỳ (destructor không dùng tới), `parameters`: mảng `double` tối đa 5 phần tử, giá trị bất kỳ | `program = nullptr`, `parameters = {0.5}` (giá trị cố định, không dùng số ngẫu nhiên) |

**C. Nhánh không test**

Không có. Unit có 0 điểm rẽ nhánh, không có vòng lặp và không có `CHECK`.

`C2 dự kiến = 0 / 0` (tổng số nhánh là 0, nên C2 được coi là đạt trọn vẹn nhờ P1 đi qua START → END; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0247_test.cc
#include "gtest/gtest.h"
#include "ceres/callbacks.h"

namespace ceres {
namespace internal {

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(StateUpdatingCallbackDestructorTest, P1_StartToEnd) {
  double parameters[1] = {0.5};
  StateUpdatingCallback* callback =
      new StateUpdatingCallback(nullptr, parameters);
  delete callback;  // gọi ~StateUpdatingCallback() một lần
}

}  // namespace internal
}  // namespace ceres
```