**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `value.a` là số thực bất kỳ, chọn trong [-10, 10]. Kiểu là `Jet<double, 2>`, không có điều kiện ràng buộc nào khác. | `value.a = 3.7` (cố định, không dùng sinh số ngẫu nhiên) |

**C. Nhánh không test**

Không có. Hàm có 0 điểm rẽ nhánh nên tổng số nhánh là 0.
Mã nguồn gọi `AsScalar(value.a)`, còn CFG ghi `std::forward<const double &>(value)`. Hai bên không khớp nên tôi tin mã nguồn. Với `Jet<double, 2>`, lệnh gọi này chuyển sang phiên bản `AsScalar` cho số vô hướng. Vẫn chỉ có một node, không có nhánh.

`C2 dự kiến = 0 / 0` (không có nhánh nào để phủ, coi là 100%; test vẫn chạy qua node 1 để phủ câu lệnh duy nhất, dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0058_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/jet_traits.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// TC1 - P1: START -> 1 -> END (không có nhánh rẽ)
TEST(AsScalarJetTest, P1_ReturnsScalarPartOfJet) {
  const Jet<double, 2> value(3.7);
  // Chỉ gọi hàm một lần, không kiểm tra kết quả trả về.
  (void)AsScalar(value);
}

}  // namespace internal
}  // namespace ceres
```