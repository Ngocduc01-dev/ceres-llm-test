// u1362 – ceres::internal::LinearLeastSquaresProblem1
// Trích từ internal/ceres/linear_least_squares_problems.cc, dòng 188–297 (chỉ để xem, không compile)

std::unique_ptr<LinearLeastSquaresProblem> LinearLeastSquaresProblem1() {
  int num_rows = 6;
  int num_cols = 5;

  auto problem = std::make_unique<LinearLeastSquaresProblem>();

  auto A = std::make_unique<TripletSparseMatrix>(
      num_rows, num_cols, num_rows * num_cols);
  problem->b = std::make_unique<double[]>(num_rows);
  problem->D = std::make_unique<double[]>(num_cols);
  problem->num_eliminate_blocks = 2;

  problem->x = std::make_unique<double[]>(num_cols);
  problem->x[0] = -2.3061;
  problem->x[1] = 0.3172;
  problem->x[2] = 0.2102;
  problem->x[3] = 2.1367;
  problem->x[4] = 0.1388;

  int* rows = A->mutable_rows();
  int* cols = A->mutable_cols();
  double* values = A->mutable_values();

  int nnz = 0;

  // Row 1
  {
    rows[nnz] = 0;
    cols[nnz] = 0;
    values[nnz++] = 1;

    rows[nnz] = 0;
    cols[nnz] = 2;
    values[nnz++] = 2;
  }

  // Row 2
  {
    rows[nnz] = 1;
    cols[nnz] = 0;
    values[nnz++] = 3;

    rows[nnz] = 1;
    cols[nnz] = 3;
    values[nnz++] = 4;
  }

  // Row 3
  {
    rows[nnz] = 2;
    cols[nnz] = 1;
    values[nnz++] = 5;

    rows[nnz] = 2;
    cols[nnz] = 4;
    values[nnz++] = 6;
  }

  // Row 4
  {
    rows[nnz] = 3;
    cols[nnz] = 1;
    values[nnz++] = 7;

    rows[nnz] = 3;
    cols[nnz] = 2;
    values[nnz++] = 8;
  }

  // Row 5
  {
    rows[nnz] = 4;
    cols[nnz] = 1;
    values[nnz++] = 9;

    rows[nnz] = 4;
    cols[nnz] = 2;
    values[nnz++] = 1;
  }

  // Row 6
  {
    rows[nnz] = 5;
    cols[nnz] = 2;
    values[nnz++] = 1;

    rows[nnz] = 5;
    cols[nnz] = 3;
    values[nnz++] = 1;

    rows[nnz] = 5;
    cols[nnz] = 4;
    values[nnz++] = 1;
  }

  A->set_num_nonzeros(nnz);
  CHECK(A->IsValid());

  problem->A = std::move(A);

  for (int i = 0; i < num_cols; ++i) {
    problem->D.get()[i] = 1;
  }

  for (int i = 0; i < num_rows; ++i) {
    problem->b.get()[i] = i;
  }

  return problem;
}
