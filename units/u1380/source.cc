// u1380 – ceres::internal::CovarianceImpl::ComputeCovarianceValuesUsingSuiteSparseQR
// Trích từ internal/ceres/covariance_impl.cc, dòng 535–702 (chỉ để xem, không compile)

bool CovarianceImpl::ComputeCovarianceValuesUsingSuiteSparseQR() {
  EventLogger event_logger(
      "CovarianceImpl::ComputeCovarianceValuesUsingSparseQR");

#ifndef CERES_NO_SUITESPARSE
  if (covariance_matrix_ == nullptr) {
    // Nothing to do, all zeros covariance matrix.
    return true;
  }

  CRSMatrix jacobian;
  problem_->Evaluate(evaluate_options_, nullptr, nullptr, nullptr, &jacobian);
  event_logger.AddEvent("Evaluate");

  // Construct a compressed column form of the Jacobian.
  const int num_rows = jacobian.num_rows;
  const int num_cols = jacobian.num_cols;
  const int num_nonzeros = jacobian.values.size();

  std::vector<SuiteSparse_long> transpose_rows(num_cols + 1, 0);
  std::vector<SuiteSparse_long> transpose_cols(num_nonzeros, 0);
  std::vector<double> transpose_values(num_nonzeros, 0);

  for (int idx = 0; idx < num_nonzeros; ++idx) {
    transpose_rows[jacobian.cols[idx] + 1] += 1;
  }

  for (int i = 1; i < transpose_rows.size(); ++i) {
    transpose_rows[i] += transpose_rows[i - 1];
  }

  for (int r = 0; r < num_rows; ++r) {
    for (int idx = jacobian.rows[r]; idx < jacobian.rows[r + 1]; ++idx) {
      const int c = jacobian.cols[idx];
      const int transpose_idx = transpose_rows[c];
      transpose_cols[transpose_idx] = r;
      transpose_values[transpose_idx] = jacobian.values[idx];
      ++transpose_rows[c];
    }
  }

  for (int i = transpose_rows.size() - 1; i > 0; --i) {
    transpose_rows[i] = transpose_rows[i - 1];
  }
  transpose_rows[0] = 0;

  cholmod_sparse cholmod_jacobian;
  cholmod_jacobian.nrow = num_rows;
  cholmod_jacobian.ncol = num_cols;
  cholmod_jacobian.nzmax = num_nonzeros;
  cholmod_jacobian.nz = nullptr;
  cholmod_jacobian.p = reinterpret_cast<void*>(transpose_rows.data());
  cholmod_jacobian.i = reinterpret_cast<void*>(transpose_cols.data());
  cholmod_jacobian.x = reinterpret_cast<void*>(transpose_values.data());
  cholmod_jacobian.z = nullptr;
  cholmod_jacobian.stype = 0;  // Matrix is not symmetric.
  cholmod_jacobian.itype = CHOLMOD_LONG;
  cholmod_jacobian.xtype = CHOLMOD_REAL;
  cholmod_jacobian.dtype = CHOLMOD_DOUBLE;
  cholmod_jacobian.sorted = 1;
  cholmod_jacobian.packed = 1;

  cholmod_common cc;
  cholmod_l_start(&cc);

  cholmod_sparse* R = nullptr;
  SuiteSparse_long* permutation = nullptr;

  // Compute a Q-less QR factorization of the Jacobian. Since we are
  // only interested in inverting J'J = R'R, we do not need Q. This
  // saves memory and gives us R as a permuted compressed column
  // sparse matrix.
  //
  // TODO(sameeragarwal): Currently the symbolic factorization and the
  // numeric factorization is done at the same time, and this does not
  // explicitly account for the block column and row structure in the
  // matrix. When using AMD, we have observed in the past that
  // computing the ordering with the block matrix is significantly
  // more efficient, both in runtime as well as the quality of
  // ordering computed. So, it maybe worth doing that analysis
  // separately.
  const SuiteSparse_long rank = SuiteSparseQR<double>(
      SPQR_ORDERING_BESTAMD,
      options_.column_pivot_threshold < 0 ? SPQR_DEFAULT_TOL
                                          : options_.column_pivot_threshold,
      static_cast<int64_t>(cholmod_jacobian.ncol),
      &cholmod_jacobian,
      &R,
      &permutation,
      &cc);
  event_logger.AddEvent("Numeric Factorization");
  if (R == nullptr) {
    LOG(ERROR) << "Something is wrong. SuiteSparseQR returned R = nullptr.";
    free(permutation);
    cholmod_l_finish(&cc);
    return false;
  }

  if (rank < cholmod_jacobian.ncol) {
    LOG(WARNING) << "Jacobian matrix is rank deficient. "
                 << "Number of columns: " << cholmod_jacobian.ncol
                 << " rank: " << rank;
    free(permutation);
    cholmod_l_free_sparse(&R, &cc);
    cholmod_l_finish(&cc);
    return false;
  }

  std::vector<int> inverse_permutation(num_cols);
  if (permutation) {
    for (SuiteSparse_long i = 0; i < num_cols; ++i) {
      inverse_permutation[permutation[i]] = i;
    }
  } else {
    for (SuiteSparse_long i = 0; i < num_cols; ++i) {
      inverse_permutation[i] = i;
    }
  }

  const int* rows = covariance_matrix_->rows();
  const int* cols = covariance_matrix_->cols();
  double* values = covariance_matrix_->mutable_values();

  // The following loop exploits the fact that the i^th column of A^{-1}
  // is given by the solution to the linear system
  //
  //  A x = e_i
  //
  // where e_i is a vector with e(i) = 1 and all other entries zero.
  //
  // Since the covariance matrix is symmetric, the i^th row and column
  // are equal.
  const int num_threads = options_.num_threads;
  auto workspace = std::make_unique<double[]>(num_threads * num_cols);

  problem_->context()->EnsureMinimumThreads(num_threads);
  ParallelFor(
      problem_->context(), 0, num_cols, num_threads, [&](int thread_id, int r) {
        const int row_begin = rows[r];
        const int row_end = rows[r + 1];
        if (row_end != row_begin) {
          double* solution = workspace.get() + thread_id * num_cols;
          SolveRTRWithSparseRHS<SuiteSparse_long>(
              num_cols,
              static_cast<SuiteSparse_long*>(R->i),
              static_cast<SuiteSparse_long*>(R->p),
              static_cast<double*>(R->x),
              inverse_permutation[r],
              solution);
          for (int idx = row_begin; idx < row_end; ++idx) {
            const int c = cols[idx];
            values[idx] = solution[inverse_permutation[c]];
          }
        }
      });

  free(permutation);
  cholmod_l_free_sparse(&R, &cc);
  cholmod_l_finish(&cc);
  event_logger.AddEvent("Inversion");
  return true;

#else  // CERES_NO_SUITESPARSE

  return false;

#endif  // CERES_NO_SUITESPARSE
}
