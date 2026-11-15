**A. Test paths**

Hàm không có điểm rẽ nhánh (0 điểm rẽ nhánh, 0 vòng lặp), nên chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | a, b, c ∈ [0, 4294967295] (uint32_t), không có điều kiện ràng buộc | a = 2654435769, b = 1013904223, c = 1664525 (cố định, tương đương lấy ngẫu nhiên với seed cố định) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên không có nhánh nào bị bỏ sót, không có vòng lặp, không có `CHECK`.

`C2 dự kiến = 0 / 0` (tổng số nhánh bằng 0, nên mọi đường đi trong CFG đều đã được phủ; chưa chạy thật).

**D. File test**

```cpp
// FILE: u0352_test.cc
#include <cstdint>

#include "gtest/gtest.h"
#include "ceres/pair_hash.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(HashMixTest, SinglePathNoBranches) {
  uint32_t a = 2654435769u;
  uint32_t b = 1013904223u;
  uint32_t c = 1664525u;
  hash_mix(a, b, c);
  SUCCEED();
}

}  // namespace internal
}  // namespace ceres
```