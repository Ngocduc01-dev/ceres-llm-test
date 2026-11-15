**CFG của unit** (không có điểm rẽ nhánh nào):

- START → node 1: `return isinf(f);` → END
- Số điểm rẽ nhánh: 0. Tổng số nhánh: 0.

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có nhánh nào (hàm không có điểm rẽ nhánh) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `f.a` là double bất kỳ (-100 đến 100), `f.v` gồm 2 phần tử trong (-100 đến 100); không có điều kiện đường đi | `f.a` = 3.7, `f.v` = (-12.5, 41.2) (sinh bằng seed cố định 12345, rồi cố định thành hằng số) |

**C. Nhánh không test:** không có (hàm không có điểm rẽ nhánh). Hàm bị đánh dấu `CERES_DEPRECATED_WITH_MSG` nên gọi sẽ sinh cảnh báo biên dịch, test tắt cảnh báo này cục bộ.

C2 dự kiến = 0 / 0 (không có nhánh; mọi câu lệnh duy nhất của hàm được chạy bởi TC1, tức phủ 100% câu lệnh).

**D. File test**

```cpp
// FILE: u0147_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

#if defined(_MSC_VER)
#pragma warning(disable : 4996)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

namespace ceres {
namespace {

// P1: START -> 1 -> END (không có nhánh nào)
TEST(IsInfiniteTest, P1_SingleStatement) {
  Jet<double, 2> f(3.7);
  f.v[0] = -12.5;
  f.v[1] = 41.2;
  bool result = IsInfinite(f);
  (void)result;  // Không kiểm tra kết quả trả về
}

}  // namespace
}  // namespace ceres
```