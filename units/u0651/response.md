# Unit u0651
## A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh. |

## B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Theo chữ ký và tiền điều kiện trong prompt.md | Dữ liệu trong TEST tương ứng |

## C. Nhánh không test

Không có nhánh điều khiển trong CFG.
C2 dự kiến = 0 / 0.

## D. File test

```cpp
// FILE: u0651_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0651, CallsTarget) {
  double block_structure_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double values_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.BlockSparseMatrixData(block_structure_data, values_data);
}
```
