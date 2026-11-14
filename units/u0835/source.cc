// u0835 – ceres::internal::CgnrLinearOperator::CgnrLinearOperator
// Trích từ internal/ceres/cgnr_solver.cc, dòng 87–95 (chỉ để xem, không compile)

  CgnrLinearOperator(const LinearOperator& A,
                     const double* D,
                     ContextImpl* context,
                     int num_threads)
      : A_(A),
        D_(D),
        z_(Vector::Zero(A.num_rows())),
        context_(context),
        num_threads_(num_threads) {}
