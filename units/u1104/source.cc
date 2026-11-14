// u1104 – ceres::internal::CreateTranspose
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 783–807 (chỉ để xem, không compile)

std::unique_ptr<CompressedRowBlockStructure> CreateTranspose(
    const CompressedRowBlockStructure& bs) {
  auto transpose = std::make_unique<CompressedRowBlockStructure>();

  transpose->rows.resize(bs.cols.size());
  for (int i = 0; i < bs.cols.size(); ++i) {
    transpose->rows[i].block = bs.cols[i];
    transpose->rows[i].nnz = 0;
  }

  transpose->cols.resize(bs.rows.size());
  for (int i = 0; i < bs.rows.size(); ++i) {
    auto& row = bs.rows[i];
    transpose->cols[i] = row.block;

    const int nrows = row.block.size;
    for (auto& cell : row.cells) {
      transpose->rows[cell.block_id].cells.emplace_back(i, cell.position);
      const int ncols = transpose->rows[cell.block_id].block.size;
      transpose->rows[cell.block_id].nnz += nrows * ncols;
    }
  }
  ComputeCumulativeNumberOfNonZeros(transpose->rows);
  return transpose;
}
