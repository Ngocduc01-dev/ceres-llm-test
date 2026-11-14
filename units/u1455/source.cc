// u1455 – ceres::internal::VisibilityBasedPreconditioner::Factorize
// Trích từ internal/ceres/visibility_based_preconditioner.cc, dòng 394–422 (chỉ để xem, không compile)

LinearSolverTerminationType VisibilityBasedPreconditioner::Factorize() {
  // Extract the BlockSparseMatrix that is used for actually storing
  // S and convert it into a CompressedRowSparseMatrix.
  const BlockSparseMatrix* bsm =
      down_cast<BlockRandomAccessSparseMatrix*>(m_.get())->matrix();
  const CompressedRowSparseMatrix::StorageType storage_type =
      sparse_cholesky_->StorageType();
  if (storage_type ==
      CompressedRowSparseMatrix::StorageType::UPPER_TRIANGULAR) {
    if (!m_crs_) {
      m_crs_ = bsm->ToCompressedRowSparseMatrix();
      m_crs_->set_storage_type(
          CompressedRowSparseMatrix::StorageType::UPPER_TRIANGULAR);
    } else {
      bsm->UpdateCompressedRowSparseMatrix(m_crs_.get());
    }
  } else {
    if (!m_crs_) {
      m_crs_ = bsm->ToCompressedRowSparseMatrixTranspose();
      m_crs_->set_storage_type(
          CompressedRowSparseMatrix::StorageType::LOWER_TRIANGULAR);
    } else {
      bsm->UpdateCompressedRowSparseMatrixTranspose(m_crs_.get());
    }
  }

  std::string message;
  return sparse_cholesky_->Factorize(m_crs_.get(), &message);
}
