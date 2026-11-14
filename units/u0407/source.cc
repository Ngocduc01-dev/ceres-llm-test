// u0407 – ceres::internal::SchurEliminator::~SchurEliminator<kRowBlockSize, kEBlockSize, kFBlockSize>
// Trích từ internal/ceres/schur_eliminator_impl.h, dòng 74–77 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
SchurEliminator<kRowBlockSize, kEBlockSize, kFBlockSize>::~SchurEliminator() {
  STLDeleteElements(&rhs_locks_);
}
