**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào (đường đi tuần tự duy nhất) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `user_state`: con trỏ tới mảng double tối đa 5 phần tử (hoặc bất kỳ con trỏ hợp lệ); `size`: 1..5; `index`: 0..5 (không có điều kiện ràng buộc) | `user_state` = mảng `{1.5, -2.0, 3.25}`; `size` = 3; `index` = 2 (sinh bằng `std::mt19937` seed cố định 12345, ánh xạ vào khoảng; giá trị đã cố định trong code) |

**C. Nhánh không test:** Không có. Hàm không có điểm rẽ nhánh, không có vòng lặp, không có `CHECK` trong constructor này.
`C2 dự kiến = 0 / 0` (tổng số nhánh = 0 nên C2 coi như đạt đầy đủ, 100%; chỉ cần node 1 được chạy qua bởi TC1).

**D. File test**

```cpp
// FILE: u0356_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ParameterBlockConstructorTest, P1_ConstructWithThreeArgs) {
  double user_state[3] = {1.5, -2.0, 3.25};
  const int size = 3;   // khoảng 1..5, giá trị chọn cố định
  const int index = 2;  // khoảng 0..5, giá trị chọn cố định

  ParameterBlock block(user_state, size, index);
  (void)block;  // không kiểm tra kết quả
}

}  // namespace internal
}  // namespace ceres
```