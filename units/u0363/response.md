**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `user_state`: mảng double có 1–5 phần tử; `size` ∈ [1, 5]; `index` ∈ [0, 10]. Hàm không nhận tham số và không có điều kiện đường đi. | `size = 3`, `index = 2`, `values = {1.0, 2.0, 3.0}` |

**C. Nhánh không test**

- Không có nhánh nào cần test: hàm có 0 điểm rẽ nhánh, nên không có nhánh nào bị bỏ sót.
- Ghi chú: CFG khớp với mã nguồn. Tên hàm `IsUpperBounded` nghe ngược với thân hàm (`upper_bounds_ == nullptr`), nhưng theo yêu cầu thì không kiểm tra kết quả trả về.
- `C2 dự kiến = 0 / 0` (không có nhánh nào, coi như đạt 100%; chưa chạy thật).

**D. File test**

```cpp
// FILE: u0363_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ParameterBlockIsUpperBoundedTest, TC1_StraightLine) {
  double values[3] = {1.0, 2.0, 3.0};
  ceres::internal::ParameterBlock block(values, 3, 2);
  block.IsUpperBounded();
}
```