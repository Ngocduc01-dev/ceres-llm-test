# A. Test paths

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → 3 → END | node 2: đúng |
| P2 | START → 1 → 2 → 4 → 5 → END | node 2: sai, node 4: đúng |
| P3 | START → 1 → 2 → 4 → 6 → END | node 2: sai, node 4: sai |

# B. Bộ test case

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `value` sau khi viết hoa bằng `TRADITIONAL_DOGLEG`; `type` trỏ tới một `DoglegType` hợp lệ | `"traditional_dogleg"`, `&type` |
| TC2 | P2 | `value` sau khi viết hoa bằng `SUBSPACE_DOGLEG`; `type` trỏ tới một `DoglegType` hợp lệ | `"subspace_dogleg"`, `&type` |
| TC3 | P3 | `value` không bằng hai chuỗi Dogleg hợp lệ; `type` trỏ tới một `DoglegType` hợp lệ | `"unknown_dogleg"`, `&type` |

# C. Nhánh không test

Không có nhánh không test. Cả hai nhánh của node 2 và node 4 đều được đi qua.

C2 dự kiến = 4 / 4

# D. File test

```cpp
// FILE: u1095_test.cc
#include "gtest/gtest.h"
#include "ceres/types.h"

// P1: START -> 1 -> 2 (đúng) -> 3 -> END
TEST(StringToDoglegTypeTest, TraditionalDogleg) {
  ceres::DoglegType type = ceres::TRADITIONAL_DOGLEG;
  ceres::StringToDoglegType("traditional_dogleg", &type);
}

// P2: START -> 1 -> 2 (sai) -> 4 (đúng) -> 5 -> END
TEST(StringToDoglegTypeTest, SubspaceDogleg) {
  ceres::DoglegType type = ceres::TRADITIONAL_DOGLEG;
  ceres::StringToDoglegType("subspace_dogleg", &type);
}

// P3: START -> 1 -> 2 (sai) -> 4 (sai) -> 6 -> END
TEST(StringToDoglegTypeTest, UnknownDoglegType) {
  ceres::DoglegType type = ceres::TRADITIONAL_DOGLEG;
  ceres::StringToDoglegType("unknown_dogleg", &type);
}
```
