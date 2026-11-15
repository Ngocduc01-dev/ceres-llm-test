**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `ptr` là con trỏ hợp lệ tới mảng `double` 4 phần tử (2 khối tham số × 2 chiều). Mỗi phần tử nằm trong [-10, 10]. | `{0.37, -2.5, 4.1, 7.8}` |

**C. Nhánh không test:** không có. Hàm không có điểm rẽ nhánh và không có `CHECK`.

`C2 dự kiến = 0 / 0` (tổng số nhánh bằng 0, nên C2 coi như đạt đầy đủ khi đường START → END được chạy qua).

Ghi chú: CFG được dựng cho `T = Jet<double, 4>`. Test dùng `T = double` để chỉ cần hai `#include` ở mục 3.3. Mã nguồn không có điểm rẽ nhánh theo kiểu `T`, nên CFG không đổi.

**D. File test**

```cpp
// FILE: u0061_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/parameter_dims.h"

namespace ceres {
namespace internal {

// P1: START -> END (không có điểm rẽ nhánh)
TEST(ParameterDimsGetUnpackedParameters, TC1_P1_StartToEnd) {
  ParameterDims<false, 2, 2> obj;
  double values[4] = {0.37, -2.5, 4.1, 7.8};
  auto result = obj.GetUnpackedParameters(values);
  (void)result;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```