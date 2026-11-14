// u1422 – ceres::internal::DenseJacobianWriter::CreateJacobian
// Trích từ internal/ceres/dense_jacobian_writer.h, dòng 66–69 (chỉ để xem, không compile)

  std::unique_ptr<SparseMatrix> CreateJacobian() const {
    return std::make_unique<DenseSparseMatrix>(
        program_->NumResiduals(), program_->NumEffectiveParameters());
  }
