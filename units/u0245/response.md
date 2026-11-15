**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `loss_function`: bất kỳ con trỏ hàm (kể cả `nullptr`), vì không có điều kiện nào ràng buộc. `user_data`: bất kỳ con trỏ `void*`. | `loss_function = nullptr`, `user_data = &data` với `int data = 3` (giá trị cố định, không dùng số ngẫu nhiên) |

**C. Nhánh không test**

- Không có nhánh nào cần loại, vì hàm không có điểm rẽ nhánh và không có `CHECK`.
- Lưu ý: `CallbackLossFunction` nằm trong anonymous namespace của `c_api.cc`. Theo mục 3.3 chỉ được dùng `#include "gtest/gtest.h"`, nên file test chỉ biên dịch được khi được build cùng translation unit của `c_api.cc`, ví dụ nếu hệ build chèn `c_api.cc` vào trước file test.
- `C2 dự kiến = 0 / 0` (tổng số nhánh là 0, nên C2 coi như đạt 100%; chỉ cần node 1 được chạy qua).

**D. File test**

```cpp
// FILE: u0245_test.cc
#include "gtest/gtest.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(CallbackLossFunctionConstructorTest, P1_ConstructWithNullCallbackAndUserData) {
  int data = 3;
  ceres_loss_function_t loss_function = nullptr;
  void* user_data = &data;

  CallbackLossFunction loss(loss_function, user_data);
}
```