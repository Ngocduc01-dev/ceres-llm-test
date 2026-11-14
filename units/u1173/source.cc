// u1173 – ceres::internal::LinearLeastSquaresProblem4
// Trích từ internal/ceres/linear_least_squares_problems.cc, dòng 547–625 (chỉ để xem, không compile)

std::unique_ptr<LinearLeastSquaresProblem> LinearLeastSquaresProblem4() {
  int num_rows = 3;
  int num_cols = 7;

  auto problem = std::make_unique<LinearLeastSquaresProblem>();

  problem->b = std::make_unique<double[]>(num_rows);
  problem->D = std::make_unique<double[]>(num_cols);
  problem->num_eliminate_blocks = 1;

  auto* bs = new CompressedRowBlockStructure;
  auto values = std::make_unique<double[]>(num_rows * num_cols);

  // Column block structure
  bs->cols.emplace_back();
  bs->cols.back().size = 2;
  bs->cols.back().position = 0;

  bs->cols.emplace_back();
  bs->cols.back().size = 3;
  bs->cols.back().position = 2;

  bs->cols.emplace_back();
  bs->cols.back().size = 2;
  bs->cols.back().position = 5;

  int nnz = 0;

  // Row 1 & 2
  {
    bs->rows.emplace_back();
    CompressedRow& row = bs->rows.back();
    row.block.size = 2;
    row.block.position = 0;

    row.cells.emplace_back(0, nnz);
    values[nnz++] = 1;
    values[nnz++] = 2;
    values[nnz++] = 1;
    values[nnz++] = 4;

    row.cells.emplace_back(2, nnz);
    values[nnz++] = 1;
    values[nnz++] = 1;
    values[nnz++] = 5;
    values[nnz++] = 6;
  }

  // Row 3
  {
    bs->rows.emplace_back();
    CompressedRow& row = bs->rows.back();
    row.block.size = 1;
    row.block.position = 2;

    row.cells.emplace_back(1, nnz);
    values[nnz++] = 9;
    values[nnz++] = 0;
    values[nnz++] = 0;

    row.cells.emplace_back(2, nnz);
    values[nnz++] = 3;
    values[nnz++] = 1;
  }

  auto A = std::make_unique<BlockSparseMatrix>(bs);
  memcpy(A->mutable_values(), values.get(), nnz * sizeof(*A->values()));

  for (int i = 0; i < num_cols; ++i) {
    problem->D.get()[i] = (i + 1) * 100;
  }

  for (int i = 0; i < num_rows; ++i) {
    problem->b.get()[i] = i;
  }

  problem->A = std::move(A);
  return problem;
}
