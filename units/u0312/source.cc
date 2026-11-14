// u0312 – ceres::internal::ImplicitSchurComplement::num_rows
// Trích từ internal/ceres/implicit_schur_complement.h, dòng 137–137 (chỉ để xem, không compile)

  int num_rows() const final { return A_->num_cols_f(); }
