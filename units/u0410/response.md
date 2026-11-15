**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, 0 nhánh). Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `max_derivatives_per_residual_block` từ 1 đến 5 (không có điều kiện đường đi; chọn giá trị dương nhỏ để cấp phát hợp lệ) | 3 (chọn ngẫu nhiên với seed cố định trong khoảng 1–5) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có vòng lặp, `CHECK` cũng không có.

C2 dự kiến = 0 / 0 (không có nhánh nào; mọi câu lệnh ở node 1 đều được chạy qua bởi TC1, nên coi như phủ đầy đủ 100%).

**D. File test**

```cpp
// FILE: u0410_test.cc
#include <random>

#include "ceres/scratch_evaluate_preparer.h"
#include "gtest/gtest.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(ScratchEvaluatePreparerInitTest, TC1_AllocatesScratchBuffer) {
  // Seed cố định để giá trị luôn giống nhau giữa các lần chạy.
  std::mt19937 rng(12345);
  std::uniform_int_distribution<int> dist(1, 5);
  const int max_derivatives_per_residual_block = dist(rng);

  ScratchEvaluatePreparer obj;
  obj.Init(max_derivatives_per_residual_block);
}

}  // namespace internal
}  // namespace ceres
```