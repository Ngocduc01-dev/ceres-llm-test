**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào |

CFG khớp với mã nguồn: `~Preprocessor() = default;` không có điểm rẽ nhánh và không có vòng lặp.

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có đầu vào. Chỉ cần tạo rồi huỷ một object của class con, thông qua con trỏ lớp cha. | Không có (không dùng số ngẫu nhiên) |

**C. Nhánh không test**

Không có, vì unit không có nhánh nào.

`C2 dự kiến = 0 / 0` (không có nhánh nào để phủ nên coi như đạt 100%; dự kiến, chưa chạy thật).

**D. File test**

```cpp
// FILE: u0387_test.cc
#include "gtest/gtest.h"
#include "ceres/preprocessor.h"

namespace ceres {
namespace internal {

namespace {

// Lớp con tối thiểu để có thể tạo object (Preprocessor có hàm thuần ảo).
class TestPreprocessor : public Preprocessor {
 public:
  bool Preprocess(const Solver::Options& /*options*/,
                  ProblemImpl* /*problem*/,
                  PreprocessedProblem* /*pp*/) override {
    return true;
  }
};

}  // namespace

// P1: START -> END (destructor không có nhánh)
TEST(PreprocessorDestructorTest, DestroyThroughBasePointer) {
  Preprocessor* preprocessor = new TestPreprocessor();
  delete preprocessor;  // gọi ~TestPreprocessor() rồi ~Preprocessor() đúng một lần
}

}  // namespace internal
}  // namespace ceres
```