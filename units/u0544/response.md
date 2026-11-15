# Unit u0544
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → 4 → 5 → END | Theo CFG của prompt.md. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không ghi nhận nhánh không thể test từ CFG cung cấp.
C2 dự kiến = 2 / 2.

## D. File test

```cpp
// FILE: u0544_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/memory.h"
#include <memory>

// Path P1: START -> 1 -> 2 -> 3 -> 4 -> 5 -> 2 -> END.
TEST(Unit_u0544, PathP1) {
  std::allocator<double> alloc;
  alignas(double) unsigned char storage[sizeof(double)];
  double* first = reinterpret_cast<double*>(storage);
  ceres::internal::ConstructRange(alloc, first, first + 1, 1.0);
  std::allocator_traits<std::allocator<double>>::destroy(alloc, first);
}
```
