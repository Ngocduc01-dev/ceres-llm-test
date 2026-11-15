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
