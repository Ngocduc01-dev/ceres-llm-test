**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh (0 điểm rẽ nhánh); node 1: `return rhs_` |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `LinearSolver::Options` mặc định (không có ràng buộc nào từ điều kiện đường đi, vì hàm không có điều kiện); object được tạo bằng constructor `ImplicitSchurComplement(const LinearSolver::Options&)`, chưa gọi `Init` | Options mặc định, không dùng số ngẫu nhiên |

Ghi chú: CFG khớp với mã nguồn (dòng 139). Không có vòng lặp, không có `CHECK`, nên không cần test số lần lặp.

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh nên tổng số nhánh là 0 và chỉ có một đường đi duy nhất.

`C2 dự kiến = 0 / 0` (không có nhánh nào; toàn bộ đường đi START → 1 → END được chạy qua, tức coi như đạt 100%, dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0314_test.cc
#include "gtest/gtest.h"
#include "ceres/implicit_schur_complement.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ImplicitSchurComplementRhsTest, TC1_P1_ReturnRhs) {
  LinearSolver::Options options;
  ImplicitSchurComplement schur_complement(options);
  const Vector& result = schur_complement.rhs();
  (void)result;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
```