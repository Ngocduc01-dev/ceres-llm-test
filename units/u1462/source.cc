// u1462 – ceres::internal::CompressedRowJacobianWriter::CreateEvaluatePreparers
// Trích từ internal/ceres/compressed_row_jacobian_writer.h, dòng 93–96 (chỉ để xem, không compile)

  std::unique_ptr<ScratchEvaluatePreparer[]> CreateEvaluatePreparers(
      int num_threads) {
    return ScratchEvaluatePreparer::Create(*program_, num_threads);
  }
