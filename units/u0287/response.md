**A. Test paths**

Hàm không có điểm rẽ nhánh nào (0 điểm, 0 nhánh), nên chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có nhánh rẽ (câu lệnh `return subspace_g_;` nằm trọn trong một đoạn lệnh tuần tự) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `subspace_g()` không có tham số. Để constructor không dừng vì `CHECK` thì cần: `linear_solver != nullptr`, `min_lm_diagonal > 0`, `min_lm_diagonal <= max_lm_diagonal`, `max_radius > 0`. | `linear_solver` = stub, `initial_radius` = 1.0, `max_radius` = 10.0, `min_lm_diagonal` = 1e-6, `max_lm_diagonal` = 1e6 |

**C. Nhánh không test**

Không có. Hàm không có nhánh nào, và không có nhánh `CHECK` trong hàm này. Các `CHECK` trong constructor được thoả bằng dữ liệu hợp lệ.

`C2 dự kiến = 0 / 0` (không có nhánh nào, nên coi là phủ hoàn toàn; dự kiến, chưa chạy thật). Test vẫn chạy qua node duy nhất của hàm (START → END).

**D. File test**

```cpp
// FILE: u0287_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

namespace ceres {
namespace internal {

namespace {

// Linear solver giả, chỉ để constructor của DoglegStrategy có con trỏ
// linear_solver khác nullptr (thoả CHECK). Hàm Solve không được gọi.
class StubLinearSolver : public LinearSolver {
 public:
  Summary Solve(LinearOperator* A,
                const double* b,
                const PerSolveOptions& per_solve_options,
                double* x) override {
    return Summary();
  }
};

}  // namespace

// Path P1: START -> END (không có nhánh rẽ)
TEST(DoglegStrategySubspaceGTest, TC1_P1_ReturnsSubspaceG) {
  StubLinearSolver linear_solver;

  TrustRegionStrategy::Options options;
  options.linear_solver = &linear_solver;
  options.initial_radius = 1.0;
  options.max_radius = 10.0;
  options.min_lm_diagonal = 1e-6;
  options.max_lm_diagonal = 1e6;

  DoglegStrategy strategy(options);
  Vector g = strategy.subspace_g();
  (void)g;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```