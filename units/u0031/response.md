**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (0 điểm rẽ nhánh), chỉ có một đường đi duy nhất |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Kích thước mảng n ∈ [1, 5] (n ≤ 37 nên dùng bộ nhớ inline); giá trị phần tử Jet<double,4> không ảnh hưởng đường đi | n = 3; giá trị phần tử mặc định (không khởi tạo giá trị cụ thể) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên không có nhánh nào bị bỏ qua.
`C2 dự kiến = 0 / 0` (tổng số nhánh = 0, nên C2 coi như đạt toàn bộ khi node 1 được chạy qua).

**D. File test**

```cpp
// FILE: u0031_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END
TEST(FixedArrayDataTest, DataReturnsPointerP1) {
  FixedArray<Jet<double, 4>, 37> array(3);
  Jet<double, 4>* p = array.data();
  (void)p;
}

}  // namespace internal
}  // namespace ceres
```

Ghi chú: mục 3.3 chỉ liệt kê `gtest` và `fixed_array.h`, nhưng CFG dựng cho `Jet<double, 4>` nên file test cần thêm `#include "ceres/jet.h"` để có kiểu `Jet`. Constructor `FixedArray(size_type n, const allocator_type& a)` trong mã nguồn có tham số allocator mặc định, nên `array(3)` hợp lệ.