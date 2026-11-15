**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (chỉ có node 1: `return size_`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `size` từ 1 đến 5 (mảng `double` có `size` phần tử); `index` từ 0 đến 5 | `size = 3`, `index = 2` |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên không có nhánh nào bị bỏ qua.

`C2 dự kiến = 0 / 0` (tổng số nhánh = 0, nên C2 coi như đạt hoàn toàn: mọi node đều được chạy qua bởi P1).

**D. File test**

```cpp
// FILE: u0357_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// Path P1: START -> 1 -> END
TEST(ParameterBlockSizeTest, P1_ReturnsSize) {
  double values[3] = {1.0, 2.0, 3.0};
  ceres::internal::ParameterBlock block(values, 3, 2);
  block.Size();
}
```