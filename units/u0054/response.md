**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào (node 1: `return data_`) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `n` (size_type) từ 1 đến 5; `a` là `std::allocator<int>` mặc định | `n` = 3 (chọn ngẫu nhiên trong khoảng, cố định sẵn trong code) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có `CHECK`, nên cũng không có vòng lặp cần xét.
Ghi chú: `Storage` là class `private` bên trong `FixedArray`. File test dùng `#define private public` sau khi include các header chuẩn, để tạo trực tiếp object `Storage`. Mã nguồn Ceres không bị sửa.

`C2 dự kiến = 0 / 0` (hàm không có nhánh, node 1 được chạy qua nên đạt 100% theo quy ước)

**D. File test**

```cpp
// FILE: u0054_test.cc
#include <algorithm>
#include <array>
#include <cstddef>
#include <iterator>
#include <memory>
#include <tuple>
#include <type_traits>

// Storage là class private của FixedArray: mở quyền truy cập chỉ trong file test.
#define private public
#include "ceres/internal/fixed_array.h"
#undef private

#include "gtest/gtest.h"

namespace {

using FixedArrayInt20 = ceres::internal::FixedArray<int, 20>;
using StorageType = FixedArrayInt20::Storage;

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayStorageBeginTest, P1_ReturnsData) {
  FixedArrayInt20::allocator_type allocator;
  StorageType storage(3, allocator);  // n = 3, trong khoảng [1, 5]
  storage.begin();
}

}  // namespace
```