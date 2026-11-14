// u1464 – ceres::internal::DynamicCompressedRowJacobianWriter::CreateEvaluatePreparers
// Trích từ internal/ceres/dynamic_compressed_row_jacobian_writer.cc, dòng 46–49 (chỉ để xem, không compile)

std::unique_ptr<ScratchEvaluatePreparer[]>
DynamicCompressedRowJacobianWriter::CreateEvaluatePreparers(int num_threads) {
  return ScratchEvaluatePreparer::Create(*program_, num_threads);
}
