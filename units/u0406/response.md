**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → END | Không có điểm rẽ nhánh nào (đường thẳng duy nhất) |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `start` là số nguyên bất kỳ, chọn trong [0, 100] (không có điều kiện ràng buộc) | `start = 37` (chọn ngẫu nhiên, cố định) |

**C. Nhánh không test**

- Không có. Hàm không có điểm rẽ nhánh và không có `CHECK`.
- Lưu ý: `Chunk` là struct lồng trong phần không public của `SchurEliminator`, nên file test dùng `#define private public` / `#define protected public` trước khi include `ceres/schur_eliminator.h`. Mã nguồn Ceres không bị sửa.
- Lưu ý: các header chuẩn và gtest được include trước để tránh ảnh hưởng của macro.
- `C2 dự kiến = 0 / 0` (không có nhánh nào, coi như đạt 100%, dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0406_test.cc
#include <algorithm>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

// Chunk là struct lồng không public của SchurEliminator; mở quyền truy cập
// chỉ để test, không sửa mã nguồn Ceres.
#define private public
#define protected public
#include "ceres/schur_eliminator.h"
#undef private
#undef protected

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(SchurEliminatorChunkTest, ConstructWithStart) {
  const int start = 37;  // chọn cố định trong khoảng [0, 100]
  ceres::internal::SchurEliminator<>::Chunk chunk(start);
  (void)chunk;
}
```