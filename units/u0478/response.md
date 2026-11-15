**A. Test paths**

Ghi chú: mã nguồn dùng `if constexpr`, nên điều kiện `kPassThreadId` được quyết định lúc biên dịch và không tạo điểm rẽ nhánh lúc chạy. Số điểm rẽ nhánh là 0, khớp với CFG. CFG chỉ dựng cho một lần khởi tạo, là nhánh `else`, tức node 2 gọi `function(args...)` không có `thread_id`. Theo mã nguồn, nhánh `if` (gọi kèm `thread_id`) cũng tồn tại, nhưng nằm ở một lần khởi tạo khác. Vì vậy tôi thêm 1 test cho mỗi lần khởi tạo.

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → END (khởi tạo `kPassThreadId = false`, CFG đã cho) | node 1: `kPassThreadId` sai lúc biên dịch, gọi `function(args...)` |
| P2 | START → 1 → END (khởi tạo `kPassThreadId = true`, không có trong CFG) | node 1: `kPassThreadId` đúng lúc biên dịch, gọi `function(thread_id, args...)` |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | `function` là lambda `(int&)`, không nhận `int` đầu tiên. `thread_id` thuộc 0..4, `value` thuộc 1..5 | `thread_id = 3`, `value = 2` |
| TC2 | P2 | `function` là lambda `(int, int&)`, gọi được với `(int, int&)`. `thread_id` thuộc 0..4, `value` thuộc 1..5 | `thread_id = 1`, `value = 4` |

**C. Nhánh không test**

Không có nhánh nào bị bỏ. Hàm không có vòng lặp và không có `CHECK`.

`C2 dự kiến = 0 / 0` (không có điểm rẽ nhánh lúc chạy). Cả hai nhánh `if constexpr` vẫn được phủ qua 2 lần khởi tạo, bởi TC1 và TC2.

**D. File test**

```cpp
// FILE: u0478_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_invoke.h"

namespace ceres::internal {

// Path P1: START -> 1 -> 2 -> END (kPassThreadId = false, goi function(args...))
TEST(InvokeWithThreadIdTest, FunctionWithoutThreadId) {
  const int thread_id = 3;
  int value = 2;
  auto function = [](int& v) { v += 1; };
  InvokeWithThreadId(thread_id, function, value);
}

// Path P2: START -> 1 -> END (kPassThreadId = true, goi function(thread_id, args...))
TEST(InvokeWithThreadIdTest, FunctionWithThreadId) {
  const int thread_id = 1;
  int value = 4;
  auto function = [](int tid, int& v) { v += tid; };
  InvokeWithThreadId(thread_id, function, value);
}

}  // namespace ceres::internal
```