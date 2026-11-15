**A. Test paths**

Hàm `front() const` không có điểm rẽ nhánh nào (0 điểm rẽ nhánh, tổng số nhánh = 0). CFG khớp với mã nguồn. Chỉ có một đường đi duy nhất.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Mảng `FixedArray<int, 12>` có kích thước n từ 1 đến 5, mỗi phần tử là số nguyên từ 0 đến 100. Object phải là `const`. | n = 3, giá trị {42, 17, 85} (chọn cố định, tương đương seed cố định) |

**C. Nhánh không test**

Không có nhánh nào bị bỏ (hàm không có điểm rẽ nhánh; `CHECK` không có trong hàm này).

`C2 dự kiến = 0 / 0` (không có nhánh; test P1 phủ toàn bộ node 1, tức 100% câu lệnh).

**D. File test**

```cpp
// FILE: u0033_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

#include <memory>

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FixedArrayFrontConstTest, P1_FrontOnConstArray) {
  const ceres::internal::FixedArray<int, 12> array({42, 17, 85},
                                                   std::allocator<int>());
  const int& first = array.front();
  (void)first;  // Không kiểm tra kết quả trả về
}
```