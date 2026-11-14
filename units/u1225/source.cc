// u1225 – ceres::internal::ImplicitSchurComplement::AddDiagonalAndInvert
// Trích từ internal/ceres/implicit_schur_complement.cc, dòng 179–204 (chỉ để xem, không compile)

void ImplicitSchurComplement::AddDiagonalAndInvert(
    const double* D, BlockSparseMatrix* block_diagonal) {
  const CompressedRowBlockStructure* block_diagonal_structure =
      block_diagonal->block_structure();
  ParallelFor(options_.context,
              0,
              block_diagonal_structure->rows.size(),
              options_.num_threads,
              [block_diagonal_structure, D, block_diagonal](int row_block_id) {
                auto& row = block_diagonal_structure->rows[row_block_id];
                const int row_block_pos = row.block.position;
                const int row_block_size = row.block.size;
                const Cell& cell = row.cells[0];
                MatrixRef m(block_diagonal->mutable_values() + cell.position,
                            row_block_size,
                            row_block_size);

                if (D != nullptr) {
                  ConstVectorRef d(D + row_block_pos, row_block_size);
                  m += d.array().square().matrix().asDiagonal();
                }

                m = m.selfadjointView<Eigen::Upper>().llt().solve(
                    Matrix::Identity(row_block_size, row_block_size));
              });
}
