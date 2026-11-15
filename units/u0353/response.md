**Ghi chú:** CFG không khớp mã nguồn (các hằng số dịch bit khác: CFG ghi 13, 8, 13, 12, 16, 5, 3, 10, 15; mã nguồn là 43, 9, 8, 38, 23, 5, 35, 49, 11). Theo yêu cầu, tin mã nguồn. Hàm không có điểm rẽ nhánh, chỉ có node 1.

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | a, b, c: bất kỳ uint64_t (không có điều kiện ràng buộc) | Sinh bằng std::mt19937_64 với seed cố định 12345 (3 giá trị liên tiếp) |

**C. Nhánh không test:** Không có. Hàm không có vòng lặp và không có `CHECK`.
`C2 dự kiến = 0 / 0` (không có nhánh; không có điểm rẽ nhánh nên mọi câu lệnh đều được chạy qua bởi 1 test, tương đương 100%).

**D. File test**

```cpp
// FILE: u0353_test.cc
#include <cstdint>
#include <random>

#include "gtest/gtest.h"
#include "ceres/pair_hash.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(HashMixTest, SinglePathNoBranch) {
  std::mt19937_64 rng(12345);
  uint64_t a = rng();
  uint64_t b = rng();
  uint64_t c = rng();
  hash_mix(a, b, c);
}

}  // namespace internal
}  // namespace ceres
```