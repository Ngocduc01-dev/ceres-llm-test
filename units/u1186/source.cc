// u1186 – ceres::internal::LinearLeastSquaresProblem3
// Trích từ internal/ceres/linear_least_squares_problems.cc, dòng 440–525 (chỉ để xem, không compile)

std::unique_ptr<LinearLeastSquaresProblem> LinearLeastSquaresProblem3() {
  int num_rows = 5;
  int num_cols = 2;

  auto problem = std::make_unique<LinearLeastSquaresProblem>();

  problem->b = std::make_unique<double[]>(num_rows);
  problem->D = std::make_unique<double[]>(num_cols);
  problem->num_eliminate_blocks = 2;

  auto* bs = new CompressedRowBlockStructure;
  auto values = std::make_unique<double[]>(num_rows * num_cols);

  for (int c = 0; c < num_cols; ++c) {
    bs->cols.emplace_back();
    bs->cols.back().size = 1;
    bs->cols.back().position = c;
  }

  int nnz = 0;

  // Row 1
  {
    values[nnz++] = 1;
    bs->rows.emplace_back();
    CompressedRow& row = bs->rows.back();
    row.block.size = 1;
    row.block.position = 0;
    row.cells.emplace_back(0, 0);
  }

  // Row 2
  {
    values[nnz++] = 3;
    bs->rows.emplace_back();
    CompressedRow& row = bs->rows.back();
    row.block.size = 1;
    row.block.position = 1;
    row.cells.emplace_back(0, 1);
  }

  // Row 3
  {
    values[nnz++] = 5;
    bs->rows.emplace_back();
    CompressedRow& row = bs->rows.back();
    row.block.size = 1;
    row.block.position = 2;
    row.cells.emplace_back(1, 2);
  }

  // Row 4
  {
    values[nnz++] = 7;
    bs->rows.emplace_back();
    CompressedRow& row = bs->rows.back();
    row.block.size = 1;
    row.block.position = 3;
    row.cells.emplace_back(1, 3);
  }

  // Row 5
  {
    values[nnz++] = 9;
    bs->rows.emplace_back();
    CompressedRow& row = bs->rows.back();
    row.block.size = 1;
    row.block.position = 4;
    row.cells.emplace_back(1, 4);
  }

  auto A = std::make_unique<BlockSparseMatrix>(bs);
  memcpy(A->mutable_values(), values.get(), nnz * sizeof(*A->values()));

  for (int i = 0; i < num_cols; ++i) {
    problem->D.get()[i] = 1;
  }

  for (int i = 0; i < num_rows; ++i) {
    problem->b.get()[i] = i;
  }

  problem->A = std::move(A);

  return problem;
}
