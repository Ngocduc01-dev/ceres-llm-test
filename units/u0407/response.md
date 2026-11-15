**A. Test paths**

Unit không có điểm rẽ nhánh và không có vòng lặp. CFG khớp mã nguồn (node 1 là `STLDeleteElements(&rhs_locks_)`), nên chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (0 điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `options.num_threads` ≥ 1. `options.context` phải khác `nullptr` vì constructor có `CHECK`. Template `<kRowBlockSize, kEBlockSize, kFBlockSize>` mỗi tham số nhận 2 hoặc 3, hoặc `Eigen::Dynamic`. | `num_threads = 1`, `context` = một `ContextImpl` cục bộ, template `<2, 2, 2>`. `Init` không được gọi nên `rhs_locks_` rỗng. |

**C. Nhánh không test**

- Không có nhánh nào bị bỏ. Unit không có điểm rẽ nhánh, nên không có nhánh không thể đi tới và không có nhánh `CHECK` cần loại.
- `CHECK` (nếu có) nằm ở constructor, không thuộc unit này. Test truyền `context` hợp lệ để không làm chương trình dừng.
- `C2 dự kiến = 0 / 0` (tổng số nhánh bằng 0 nên C2 coi như đạt 100%; test đi qua node 1 và END).

**D. File test**

```cpp
// FILE: u0407_test.cc
#include "gtest/gtest.h"
#include "ceres/schur_eliminator.h"
#include "ceres/schur_eliminator_impl.h"
#include "ceres/stl_util.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(SchurEliminatorDestructorTest, DestroyWithoutInit) {
  ContextImpl context;
  LinearSolver::Options options;
  options.num_threads = 1;
  options.context = &context;

  auto* eliminator = new SchurEliminator<2, 2, 2>(options);
  delete eliminator;  // gọi ~SchurEliminator() đúng một lần
}

}  // namespace internal
}  // namespace ceres
```

Lưu ý: `ContextImpl` được kéo vào qua `ceres/linear_solver.h` (include từ `schur_eliminator.h`). Nếu biên dịch báo thiếu kiểu này, hãy thêm `#include "ceres/context_impl.h"`.