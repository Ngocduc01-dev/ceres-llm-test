// u1172 – ceres::internal::LinearLeastSquaresProblem0
// Trích từ internal/ceres/linear_least_squares_problems.cc, dòng 90–135 (chỉ để xem, không compile)

std::unique_ptr<LinearLeastSquaresProblem> LinearLeastSquaresProblem0() {
  auto problem = std::make_unique<LinearLeastSquaresProblem>();

  auto A = std::make_unique<TripletSparseMatrix>(3, 2, 6);
  problem->b = std::make_unique<double[]>(3);
  problem->D = std::make_unique<double[]>(2);

  problem->x = std::make_unique<double[]>(2);
  problem->x_D = std::make_unique<double[]>(2);

  int* Ai = A->mutable_rows();
  int* Aj = A->mutable_cols();
  double* Ax = A->mutable_values();

  int counter = 0;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 2; ++j) {
      Ai[counter] = i;
      Aj[counter] = j;
      ++counter;
    }
  }

  Ax[0] = 1.;
  Ax[1] = 2.;
  Ax[2] = 3.;
  Ax[3] = 4.;
  Ax[4] = 6;
  Ax[5] = -10;
  A->set_num_nonzeros(6);
  problem->A = std::move(A);

  problem->b[0] = 8;
  problem->b[1] = 18;
  problem->b[2] = -18;

  problem->x[0] = 2.0;
  problem->x[1] = 3.0;

  problem->D[0] = 1;
  problem->D[1] = 2;

  problem->x_D[0] = 1.78448275;
  problem->x_D[1] = 2.82327586;
  return problem;
}
