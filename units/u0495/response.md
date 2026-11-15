**A. Test paths**

Có 1 điểm rẽ nhánh (node 2, vòng `for`), tổng 2 nhánh. `DCHECK(src)` ở node 1 không tính, và không làm nó sai.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END | node 1: đúng, node 2: sai (0 lần lặp) |
| P2 | START → 1 → (2 → 3 → 4) ×1 → 2 → END | node 2: đúng ×1, rồi sai |
| P3 | START → 1 → (2 → 3 → 4) ×2 → 2 → END | node 2: đúng ×2, rồi sai |
| P4 | START → 1 → (2 → 3 → 4) ×3 → 2 → END | node 2: đúng ×3, rồi sai (số ở giữa) |
| P5 | START → 1 → (2 → 3 → 4) ×4 → 2 → END | node 2: đúng ×4, rồi sai (n−1) |
| P6 | START → 1 → (2 → 3 → 4) ×5 → 2 → END | node 2: đúng ×5, rồi sai (n) |

**B. Bộ test case**

Đầu vào: `M` (số lần lặp), `src` khác null với ít nhất `M` phần tử, `dst` có ít nhất `M` phần tử. Giá trị phần tử `src[i].a` được sinh bằng `std::mt19937` với seed cố định 495, trong khoảng [-10, 10].

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | M = 0 | M = 0 |
| TC2 | P2 | M = 1 | M = 1 |
| TC3 | P3 | M = 2 | M = 2 |
| TC4 | P4 | M từ 3 đến 3 (giữa 2 và 4) | M = 3 |
| TC5 | P5 | M = 4 | M = 4 |
| TC6 | P6 | M = 5 | M = 5 |

**C. Nhánh không test**

- Nhánh `DCHECK(src)` sai: không test (làm chương trình dừng).
- Không test số lần lặp n+1 = 6, vì mảng được giới hạn tối đa 5 phần tử.
- Không có nhánh nào không thể đi tới.

`C2 dự kiến = 2 / 2`

**D. File test**

```cpp
// FILE: u0495_test.cc
#include <random>

#include "ceres/internal/autodiff.h"
#include "gtest/gtest.h"

namespace ceres {
namespace internal {

namespace {

using JetD4 = Jet<double, 4>;

constexpr int kMaxSize = 5;

// Chuẩn bị mảng src (5 phần tử, giá trị sinh từ seed cố định) rồi gọi unit một lần.
void RunTake0thOrderPart(int M) {
  std::mt19937 gen(495);
  std::uniform_real_distribution<double> dist(-10.0, 10.0);

  JetD4 src[kMaxSize];
  double dst[kMaxSize] = {0.0, 0.0, 0.0, 0.0, 0.0};
  for (int i = 0; i < kMaxSize; ++i) {
    src[i] = JetD4(dist(gen));
  }

  Take0thOrderPart<JetD4, double*>(M, src, dst);
}

}  // namespace

// P1: node 1: đúng, node 2: sai (0 lần lặp)
TEST(Take0thOrderPartTest, ZeroIterations) { RunTake0thOrderPart(0); }

// P2: node 1: đúng, node 2: đúng x1 rồi sai (1 lần lặp)
TEST(Take0thOrderPartTest, OneIteration) { RunTake0thOrderPart(1); }

// P3: node 1: đúng, node 2: đúng x2 rồi sai (2 lần lặp)
TEST(Take0thOrderPartTest, TwoIterations) { RunTake0thOrderPart(2); }

// P4: node 1: đúng, node 2: đúng x3 rồi sai (số lần lặp ở giữa)
TEST(Take0thOrderPartTest, ThreeIterations) { RunTake0thOrderPart(3); }

// P5: node 1: đúng, node 2: đúng x4 rồi sai (n-1 lần lặp)
TEST(Take0thOrderPartTest, FourIterations) { RunTake0thOrderPart(4); }

// P6: node 1: đúng, node 2: đúng x5 rồi sai (n lần lặp)
TEST(Take0thOrderPartTest, FiveIterations) { RunTake0thOrderPart(5); }

}  // namespace internal
}  // namespace ceres
```