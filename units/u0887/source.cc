// u0887 – ceres::internal::ProgramEvaluator::CreateJacobian
// Trích từ internal/ceres/program_evaluator.h, dòng 130–132 (chỉ để xem, không compile)

  std::unique_ptr<SparseMatrix> CreateJacobian() const final {
    return jacobian_writer_.CreateJacobian();
  }
