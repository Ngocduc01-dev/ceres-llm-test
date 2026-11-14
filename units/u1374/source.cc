// u1374 – ceres::internal::SubsetPreconditioner::UpdateImpl
// Trích từ internal/ceres/subset_preconditioner.cc, dòng 68–115 (chỉ để xem, không compile)

bool SubsetPreconditioner::UpdateImpl(const BlockSparseMatrix& A,
                                      const double* D) {
  auto* m = const_cast<BlockSparseMatrix*>(&A);
  const CompressedRowBlockStructure* bs = m->block_structure();

  // A = [P]
  //     [Q]

  // Now add D to A if needed.
  if (D != nullptr) {
    // A = [P]
    //     [Q]
    //     [D]
    std::unique_ptr<BlockSparseMatrix> regularizer(
        BlockSparseMatrix::CreateDiagonalMatrix(D, bs->cols));
    m->AppendRows(*regularizer);
  }

  if (inner_product_computer_ == nullptr) {
    inner_product_computer_ = InnerProductComputer::Create(
        *m,
        options_.subset_preconditioner_start_row_block,
        bs->rows.size(),
        sparse_cholesky_->StorageType());
  }

  // Compute inner_product = [Q'*Q + D'*D]
  inner_product_computer_->Compute();

  // Unappend D if needed.
  if (D != nullptr) {
    // A = [P]
    //     [Q]
    m->DeleteRowBlocks(bs->cols.size());
  }

  std::string message;
  // Compute L. s.t., LL' = Q'*Q + D'*D
  const LinearSolverTerminationType termination_type =
      sparse_cholesky_->Factorize(inner_product_computer_->mutable_result(),
                                  &message);
  if (termination_type != LinearSolverTerminationType::SUCCESS) {
    LOG(ERROR) << "Preconditioner factorization failed: " << message;
    return false;
  }

  return true;
}
