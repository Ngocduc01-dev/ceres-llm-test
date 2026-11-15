**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nên không có nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có đầu vào (hàm không tham số, không có điều kiện, không có vòng lặp) | Không có. Dùng object `LinearSolver` con (class `TestLinearSolver`) với constructor mặc định |

**C. Nhánh không test**

Không có. Hàm có 0 điểm rẽ nhánh nên không có nhánh nào cần phủ. Mã nguồn (dòng 348–350) khớp với CFG: chỉ có `return {};`.

C2 dự kiến = 0 / 0 (không có nhánh; hàm được phủ hoàn toàn khi chạy P1, 1 test)

**D. File test**

```cpp
// FILE: u0331_test.cc
#include "gtest/gtest.h"
#include "ceres/execution_summary.h"
#include "ceres/linear_solver.h"

namespace ceres {
namespace internal {

namespace {

// Lớp con cụ thể để tạo được object (LinearSolver có hàm thuần ảo Solve).
class TestLinearSolver : public LinearSolver {
 public:
  Summary Solve(LinearOperator* A,
                const double* b,
                const PerSolveOptions& per_solve_options,
                double* x) override {
    return Summary();
  }
};

}  // namespace

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(LinearSolverStatisticsTest, P1_DefaultReturnsWithoutBranch) {
  TestLinearSolver solver;
  solver.Statistics();
}

}  // namespace internal
}  // namespace ceres
```