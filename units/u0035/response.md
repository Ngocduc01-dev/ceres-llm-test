**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (0 điểm rẽ nhánh); chỉ có node 1 (`return *(end() - 1)`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Mảng `FixedArray<int, 12>` có kích thước n từ 1 đến 5 (cần n ≥ 1 để `end() - 1` hợp lệ); các phần tử là số nguyên bất kỳ | n = 3, phần tử là `{4, 7, 2}` (giá trị chọn ngẫu nhiên trong khoảng) |

**C. Nhánh không test**

- Không có nhánh nào bị bỏ qua: hàm không có điểm rẽ nhánh, không có vòng lặp, không có `CHECK`.
- Ghi chú: CFG khớp với mã nguồn (một câu lệnh `return`).
- `C2 dự kiến = 0 / 0` (tổng số nhánh bằng 0 nên C2 coi như đạt 100%, chỉ cần node 1 được chạy qua; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0035_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

#include <initializer_list>
#include <memory>

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayBackConst, P1_ReturnLastElement) {
  const ceres::internal::FixedArray<int, 12> array(
      {4, 7, 2}, std::allocator<int>());
  array.back();
}
```