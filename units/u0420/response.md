**Ghi chú:** CFG khớp với mã nguồn (không có điểm rẽ nhánh). Hàm là `static`, nhưng theo mục 3.3 vẫn tạo object `SuiteSparse obj;` rồi gọi method trên object đó.

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh; node 1: `return false` |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Hàm không có tham số; không có điều kiện đường đi | Không có (chỉ tạo `SuiteSparse obj;` bằng constructor mặc định) |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có vòng lặp. Không có `CHECK`.

`C2 dự kiến = 0 / 0` (tổng số nhánh = 2 × 0 = 0; coi như đạt 100% vì mọi node đều được chạy qua, dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0420_test.cc
#include "gtest/gtest.h"
#include "ceres/suitesparse.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (node 1: return false)
TEST(SuiteSparseIsNestedDissectionAvailable, TC1_ReturnFalsePath) {
  SuiteSparse obj;
  obj.IsNestedDissectionAvailable();
}

}  // namespace internal
}  // namespace ceres
```