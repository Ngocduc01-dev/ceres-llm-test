// u0911 – ceres::internal::SchurEliminator::SchurEliminator<kRowBlockSize, kEBlockSize, kFBlockSize>
// Trích từ internal/ceres/schur_eliminator.h, dòng 229–232 (chỉ để xem, không compile)

  explicit SchurEliminator(const LinearSolver::Options& options)
      : num_threads_(options.num_threads), context_(options.context) {
    CHECK(context_ != nullptr);
  }
