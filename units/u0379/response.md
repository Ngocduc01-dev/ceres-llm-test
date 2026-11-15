**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào |

Lưu ý: mã nguồn là `~PowerSeriesExpansionPreconditioner() = default;` (dòng 49 bị cắt ở dấu `=`). Hàm không có lệnh nào, nên CFG khớp với mã nguồn.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `isc`: bất kỳ, vì constructor không dùng đến con trỏ này; `max_num_spse_iterations` từ 1 đến 5; `spse_tolerance` từ 0.001 đến 0.1; `options`: mặc định | `isc = nullptr`; `max_num_spse_iterations = 3`; `spse_tolerance = 0.01`; `options = Preconditioner::Options()` |

Các giá trị trên được chọn cố định, không dùng hàm ngẫu nhiên, nên mỗi lần chạy cho cùng kết quả.

**C. Nhánh không test**

Không có nhánh nào, vì hàm có 0 điểm rẽ nhánh. Không có nhánh `CHECK`.

`C2 dự kiến = 0 / 0` (tổng số nhánh là 0, nên coi như phủ đủ 100%; đường START → END được chạy qua 1 lần). Đây là số dự kiến, chưa chạy thật.

**D. File test**

```cpp
// FILE: u0379_test.cc
#include "gtest/gtest.h"
#include "ceres/power_series_expansion_preconditioner.h"

namespace ceres {
namespace internal {

// P1: START -> END (destructor không có điểm rẽ nhánh)
TEST(PowerSeriesExpansionPreconditionerDestructorTest, TC1_P1_StartToEnd) {
  const ImplicitSchurComplement* isc = nullptr;
  const int max_num_spse_iterations = 3;
  const double spse_tolerance = 0.01;
  Preconditioner::Options options;

  // Destructor được gọi đúng một lần khi đối tượng bị huỷ.
  PowerSeriesExpansionPreconditioner* preconditioner =
      new PowerSeriesExpansionPreconditioner(
          isc, max_num_spse_iterations, spse_tolerance, options);
  delete preconditioner;
}

}  // namespace internal
}  // namespace ceres
```