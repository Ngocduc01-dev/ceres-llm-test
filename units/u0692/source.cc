// u0692 – ceres::internal::TypedPreconditioner::Update
// Trích từ internal/ceres/preconditioner.h, dòng 184–186 (chỉ để xem, không compile)

  bool Update(const LinearOperator& A, const double* D) final {
    return UpdateImpl(*down_cast<const MatrixType*>(&A), D);
  }
