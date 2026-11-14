// u1423 – ceres::internal::DynamicCompressedRowJacobianWriter::CreateJacobian
// Trích từ internal/ceres/dynamic_compressed_row_jacobian_writer.cc, dòng 51–57 (chỉ để xem, không compile)

std::unique_ptr<SparseMatrix>
DynamicCompressedRowJacobianWriter::CreateJacobian() const {
  return std::make_unique<DynamicCompressedRowSparseMatrix>(
      program_->NumResiduals(),
      program_->NumEffectiveParameters(),
      0 /* max_num_nonzeros */);
}
