**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (tuần tự) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | max_parameters_per_residual_block ∈ [1,5]; max_scratch_doubles_needed_for_evaluate ∈ [1,5]; max_residuals_per_residual_block ∈ [1,5]; num_parameters ∈ [1,5] | 3, 4, 2, 5 |

**C. Nhánh không test**

- Không có nhánh nào (hàm có 0 điểm rẽ nhánh, không có vòng lặp, không có `CHECK`).
- `C2 dự kiến = 0 / 0` (không có nhánh nào; node 1 được chạy qua bởi TC1, nên cũng đạt C1).

Lưu ý:
- `EvaluateScratch` là struct nằm trong phần `private` của `ProgramEvaluator`. File test dùng `#define private public` trước khi include header của Ceres để truy cập được, không sửa mã nguồn.
- Phải include thêm `scratch_evaluate_preparer.h` và `dense_jacobian_writer.h`, vì `ProgramEvaluator<ScratchEvaluatePreparer, DenseJacobianWriter>` cần hai kiểu này đầy đủ khi được khởi tạo. Đây là hai include ngoài mục 3.3.

**D. File test**

```cpp
// FILE: u0400_test.cc
#include "gtest/gtest.h"

#define private public
#include "ceres/program_evaluator.h"
#include "ceres/scratch_evaluate_preparer.h"
#include "ceres/dense_jacobian_writer.h"
#undef private

namespace ceres {
namespace internal {

using TestProgramEvaluator =
    ProgramEvaluator<ScratchEvaluatePreparer, DenseJacobianWriter>;
using EvaluateScratch = TestProgramEvaluator::EvaluateScratch;

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EvaluateScratchInitTest, TC1_P1_SequentialPath) {
  EvaluateScratch obj;
  obj.Init(/*max_parameters_per_residual_block=*/3,
           /*max_scratch_doubles_needed_for_evaluate=*/4,
           /*max_residuals_per_residual_block=*/2,
           /*num_parameters=*/5);
}

}  // namespace internal
}  // namespace ceres
```