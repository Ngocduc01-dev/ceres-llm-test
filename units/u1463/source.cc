// u1463 – ceres::internal::DenseJacobianWriter::CreateEvaluatePreparers
// Trích từ internal/ceres/dense_jacobian_writer.h, dòng 61–64 (chỉ để xem, không compile)

  std::unique_ptr<ScratchEvaluatePreparer[]> CreateEvaluatePreparers(
      int num_threads) {
    return ScratchEvaluatePreparer::Create(*program_, num_threads);
  }
