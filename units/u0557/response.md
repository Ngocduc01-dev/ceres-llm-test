**A. Test paths**

| Path | ???ng ?i (theo s? node) | C?c nh?nh ?i qua |
|---|---|---|
| P1 | START ? 1 ? END | CFG branch path 1 |
| P2 | START ? 1 ? END | CFG branch path 2 |

**B. B? test case**

| Test | Path | Kho?ng gi? tr? ??u v?o | Gi? tr? ?? ch?n |
|---|---|---|---|
| TC1 | P1 | valid values from prompt signature | deterministic small value |
| TC2 | P2 | valid values from prompt signature | deterministic small value |

**C. Nh?nh kh?ng test**

Kh?ng k?ch ho?t nh?nh CHECK l?m d?ng ch??ng tr?nh. C2 d? ki?n = 4 / 4

**D. File test**

```cpp
// FILE: u0557_test.cc
#include "gtest/gtest.h"
#include "ceres/graph.h"
#include "ceres/graph_algorithms.h"

namespace ceres {
namespace internal {
// Path P1 calls IndependentSetOrdering(const Graph<Vertex>& graph, std::vector<Vertex>* ordering).
TEST(Unitu0557, CallsTarget) {
  double ordering_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  IndependentSetOrdering({}, ordering_data);
}

// Path P2 calls IndependentSetOrdering(const Graph<Vertex>& graph, std::vector<Vertex>* ordering) on the alternate CFG path.
TEST(Unitu0557, CallsTargetAlternate) {
  double ordering_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  IndependentSetOrdering({}, ordering_data);
}
}  // namespace internal
}  // namespace ceres
```
