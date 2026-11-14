// u1372 – ceres::internal::BlockSparseJacobiPreconditioner::UpdateImpl
// Trích từ internal/ceres/block_jacobi_preconditioner.cc, dòng 58–114 (chỉ để xem, không compile)

bool BlockSparseJacobiPreconditioner::UpdateImpl(const BlockSparseMatrix& A,
                                                 const double* D) {
  const CompressedRowBlockStructure* bs = A.block_structure();
  const double* values = A.values();
  m_->SetZero();

  ParallelFor(options_.context,
              0,
              bs->rows.size(),
              options_.num_threads,
              [this, bs, values](int i) {
                const int row_block_size = bs->rows[i].block.size;
                const std::vector<Cell>& cells = bs->rows[i].cells;
                for (const auto& cell : cells) {
                  const int block_id = cell.block_id;
                  const int col_block_size = bs->cols[block_id].size;
                  int r, c, row_stride, col_stride;
                  CellInfo* cell_info = m_->GetCell(
                      block_id, block_id, &r, &c, &row_stride, &col_stride);
                  MatrixRef m(cell_info->values, row_stride, col_stride);
                  ConstMatrixRef b(
                      values + cell.position, row_block_size, col_block_size);
                  auto lock =
                      MakeConditionalLock(options_.num_threads, cell_info->m);
                  // clang-format off
                  MatrixTransposeMatrixMultiply<Eigen::Dynamic, Eigen::Dynamic,
                      Eigen::Dynamic,Eigen::Dynamic, 1>(
                          values + cell.position, row_block_size,col_block_size,
                          values + cell.position, row_block_size,col_block_size,
                          cell_info->values,r, c,row_stride,col_stride);
                  // clang-format on
                }
              });

  if (D != nullptr) {
    // Add the diagonal.
    ParallelFor(options_.context,
                0,
                bs->cols.size(),
                options_.num_threads,
                [this, bs, D](int i) {
                  const int block_size = bs->cols[i].size;
                  int r, c, row_stride, col_stride;
                  CellInfo* cell_info =
                      m_->GetCell(i, i, &r, &c, &row_stride, &col_stride);
                  MatrixRef m(cell_info->values, row_stride, col_stride);
                  m.block(r, c, block_size, block_size).diagonal() +=
                      ConstVectorRef(D + bs->cols[i].position, block_size)
                          .array()
                          .square()
                          .matrix();
                });
  }

  m_->Invert();
  return true;
}
