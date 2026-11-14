// u1185 – ceres::internal::LinearLeastSquaresProblem2
// Trích từ internal/ceres/linear_least_squares_problems.cc, dòng 300–422 (chỉ để xem, không compile)

std::unique_ptr<LinearLeastSquaresProblem> LinearLeastSquaresProblem2() {
  int num_rows = 6;
  int num_cols = 5;

  auto problem = std::make_unique<LinearLeastSquaresProblem>();

  problem->b = std::make_unique<double[]>(num_rows);
  problem->D = std::make_unique<double[]>(num_cols);
  problem->num_eliminate_blocks = 2;

  problem->x = std::make_unique<double[]>(num_cols);
  problem->x[0] = -2.3061;
  problem->x[1] = 0.3172;
  problem->x[2] = 0.2102;
  problem->x[3] = 2.1367;
  problem->x[4] = 0.1388;

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
    values[nnz++] = 2;

    bs->rows.emplace_back();
    CompressedRow& row = bs->rows.back();
    row.block.size = 1;
    row.block.position = 0;
    row.cells.emplace_back(0, 0);
    row.cells.emplace_back(2, 1);
  }

  // Row 2
  {
    values[nnz++] = 3;
    values[nnz++] = 4;

    bs->rows.emplace_back();
    CompressedRow& row = bs->rows.back();
    row.block.size = 1;
    row.block.position = 1;
    row.cells.emplace_back(0, 2);
    row.cells.emplace_back(3, 3);
  }

  // Row 3
  {
    values[nnz++] = 5;
    values[nnz++] = 6;

    bs->rows.emplace_back();
    CompressedRow& row = bs->rows.back();
    row.block.size = 1;
    row.block.position = 2;
    row.cells.emplace_back(1, 4);
    row.cells.emplace_back(4, 5);
  }

  // Row 4
  {
    values[nnz++] = 7;
    values[nnz++] = 8;

    bs->rows.emplace_back();
    CompressedRow& row = bs->rows.back();
    row.block.size = 1;
    row.block.position = 3;
    row.cells.emplace_back(1, 6);
    row.cells.emplace_back(2, 7);
  }

  // Row 5
  {
    values[nnz++] = 9;
    values[nnz++] = 1;

    bs->rows.emplace_back();
    CompressedRow& row = bs->rows.back();
    row.block.size = 1;
    row.block.position = 4;
    row.cells.emplace_back(1, 8);
    row.cells.emplace_back(2, 9);
  }

  // Row 6
  {
    values[nnz++] = 1;
    values[nnz++] = 1;
    values[nnz++] = 1;

    bs->rows.emplace_back();
    CompressedRow& row = bs->rows.back();
    row.block.size = 1;
    row.block.position = 5;
    row.cells.emplace_back(2, 10);
    row.cells.emplace_back(3, 11);
    row.cells.emplace_back(4, 12);
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
