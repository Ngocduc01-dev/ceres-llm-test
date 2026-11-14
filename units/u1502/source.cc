// u1502 – ceres::internal::CovarianceImpl::ComputeCovarianceValuesUsingEigenSparseQR
// Trích từ internal/ceres/covariance_impl.cc, dòng 795–887 (chỉ để xem, không compile)

bool CovarianceImpl::ComputeCovarianceValuesUsingEigenSparseQR() {
  EventLogger event_logger(
      "CovarianceImpl::ComputeCovarianceValuesUsingEigenSparseQR");
  if (covariance_matrix_ == nullptr) {
    // Nothing to do, all zeros covariance matrix.
    return true;
  }

  CRSMatrix jacobian;
  problem_->Evaluate(evaluate_options_, nullptr, nullptr, nullptr, &jacobian);
  event_logger.AddEvent("Evaluate");

  using EigenSparseMatrix = Eigen::SparseMatrix<double, Eigen::ColMajor>;

  // Convert the matrix to column major order as required by SparseQR.
  EigenSparseMatrix sparse_jacobian =
      Eigen::Map<Eigen::SparseMatrix<double, Eigen::RowMajor>>(
          jacobian.num_rows,
          jacobian.num_cols,
          static_cast<int>(jacobian.values.size()),
          jacobian.rows.data(),
          jacobian.cols.data(),
          jacobian.values.data());
  event_logger.AddEvent("ConvertToSparseMatrix");

  Eigen::SparseQR<EigenSparseMatrix, Eigen::COLAMDOrdering<int>> qr;
  if (options_.column_pivot_threshold > 0) {
    qr.setPivotThreshold(options_.column_pivot_threshold);
  }

  qr.compute(sparse_jacobian);
  event_logger.AddEvent("QRDecomposition");

  if (qr.info() != Eigen::Success) {
    LOG(ERROR) << "Eigen::SparseQR decomposition failed.";
    return false;
  }

  if (qr.rank() < jacobian.num_cols) {
    LOG(ERROR) << "Jacobian matrix is rank deficient. "
               << "Number of columns: " << jacobian.num_cols
               << " rank: " << qr.rank();
    return false;
  }

  const int* rows = covariance_matrix_->rows();
  const int* cols = covariance_matrix_->cols();
  double* values = covariance_matrix_->mutable_values();

  // Compute the inverse column permutation used by QR factorization.
  Eigen::PermutationMatrix<Eigen::Dynamic, Eigen::Dynamic> inverse_permutation =
      qr.colsPermutation().inverse();

  // The following loop exploits the fact that the i^th column of A^{-1}
  // is given by the solution to the linear system
  //
  //  A x = e_i
  //
  // where e_i is a vector with e(i) = 1 and all other entries zero.
  //
  // Since the covariance matrix is symmetric, the i^th row and column
  // are equal.
  const int num_cols = jacobian.num_cols;
  const int num_threads = options_.num_threads;
  auto workspace = std::make_unique<double[]>(num_threads * num_cols);

  problem_->context()->EnsureMinimumThreads(num_threads);
  ParallelFor(
      problem_->context(), 0, num_cols, num_threads, [&](int thread_id, int r) {
        const int row_begin = rows[r];
        const int row_end = rows[r + 1];
        if (row_end != row_begin) {
          double* solution = workspace.get() + thread_id * num_cols;
          SolveRTRWithSparseRHS<int>(num_cols,
                                     qr.matrixR().innerIndexPtr(),
                                     qr.matrixR().outerIndexPtr(),
                                     &qr.matrixR().data().value(0),
                                     inverse_permutation.indices().coeff(r),
                                     solution);

          // Assign the values of the computed covariance using the
          // inverse permutation used in the QR factorization.
          for (int idx = row_begin; idx < row_end; ++idx) {
            const int c = cols[idx];
            values[idx] = solution[inverse_permutation.indices().coeff(c)];
          }
        }
      });

  event_logger.AddEvent("Inverse");

  return true;
}
