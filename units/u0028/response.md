**A. Test paths**

Hàm có 0 điểm rẽ nhánh, nên CFG chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `n` (số phần tử của `FixedArray<int, 20>`): 1 đến 5 (không có điều kiện đường đi; chọn n ≤ 5 để mảng nhỏ) | n = 3 |

**C. Nhánh không test**

- Không có nhánh nào bị bỏ. Hàm không có điểm rẽ nhánh và không có `CHECK`.
- Không có vòng lặp, nên không cần xét số lần lặp.
- CFG khớp với mã nguồn dòng 177.
- `C2 dự kiến = 0 / 0` (tổng số nhánh là 0, nên coi như phủ hết; TC1 phủ toàn bộ câu lệnh duy nhất của hàm).

**D. File test**

```cpp
// FILE: u0028_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArraySizeTest, P1_ReturnsStorageSize) {
  using Array = FixedArray<int, 20>;
  const Array::size_type n = 3;  // giá trị chọn trong khoảng 1..5
  const Array array(n, Array::allocator_type());
  Array::size_type result = array.size();
  (void)result;  // không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```