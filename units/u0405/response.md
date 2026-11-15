**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → END | Không có điểm rẽ nhánh nào |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | Không có tham số đầu vào. Chỉ cần tạo rồi huỷ một object của lớp con. | Không áp dụng |

**C. Nhánh không test**

- Không có. Hàm không có điểm rẽ nhánh và không có `CHECK`.
- C2 dự kiến = 0 / 0 (tổng số nhánh bằng 0). TC1 phủ toàn bộ đường đi duy nhất START → END, tức đạt 100% theo quy ước.
- Ghi chú: CFG khớp với mã nguồn, vì `= default` không chứa lệnh rẽ nhánh nào.

**D. File test**

```cpp
// FILE: u0405_test.cc
#include <memory>

#include "gtest/gtest.h"
#include "ceres/schur_eliminator.h"

namespace ceres {
namespace internal {

namespace {

// Lớp con tối thiểu để tạo được object, vì SchurEliminatorBase có hàm thuần ảo.
class FakeSchurEliminator : public SchurEliminatorBase {
 public:
  ~FakeSchurEliminator() override = default;

  void Init(int /*num_eliminate_blocks*/,
            bool /*assume_full_rank_ete*/,
            const CompressedRowBlockStructure* /*bs*/) override {}

  void Eliminate(const BlockSparseMatrixData& /*A*/,
                 const double* /*b*/,
                 const double* /*D*/,
                 BlockRandomAccessMatrix* /*lhs*/,
                 double* /*rhs*/) override {}

  void BackSubstitute(const BlockSparseMatrixData& /*A*/,
                      const double* /*b*/,
                      const double* /*D*/,
                      const double* /*z*/,
                      double* /*y*/) override {}
};

}  // namespace

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(SchurEliminatorBaseDestructorTest, DestroyDerivedObjectViaBasePointer) {
  std::unique_ptr<SchurEliminatorBase> obj(new FakeSchurEliminator());
  obj.reset();  // gọi ~SchurEliminatorBase() một lần
}

}  // namespace internal
}  // namespace ceres
```