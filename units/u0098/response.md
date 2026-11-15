**A. Test paths**

CFG ghi 0 điểm rẽ nhánh, khớp với mã nguồn (một câu `return std::isnan(x)`). Vì vậy chỉ có một đường đi.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `x` là số thực double bất kỳ, không có điều kiện đường đi, lấy khoảng [-10, 10] | `x = 3.5` |

**C. Nhánh không test**

Không có. Hàm không có điểm rẽ nhánh và không có `CHECK`. Vòng lặp: không có.

`C2 dự kiến = 0 / 0` (không có nhánh nào nên coi như đạt 100%, dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0098_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Tắt cảnh báo deprecated vì hàm IsNaN được đánh dấu CERES_DEPRECATED_WITH_MSG.
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4996)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(IsNaNTest, P1_StraightLine) {
  const double x = 3.5;  // chọn trong khoảng [-10, 10]
  (void)ceres::IsNaN(x);
}

#if defined(_MSC_VER)
#pragma warning(pop)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
```