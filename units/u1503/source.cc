// u1503 – ceres::internal::CovarianceImpl::ComputeCovarianceValuesUsingDenseSVD
// Trích từ internal/ceres/covariance_impl.cc, dòng 704–793 (chỉ để xem, không compile)

bool CovarianceImpl::ComputeCovarianceValuesUsingDenseSVD() {
  EventLogger event_logger(
      "CovarianceImpl::ComputeCovarianceValuesUsingDenseSVD");
  if (covariance_matrix_ == nullptr) {
    // Nothing to do, all zeros covariance matrix.
    return true;
  }

  CRSMatrix jacobian;
  problem_->Evaluate(evaluate_options_, nullptr, nullptr, nullptr, &jacobian);
  event_logger.AddEvent("Evaluate");

  Matrix dense_jacobian(jacobian.num_rows, jacobian.num_cols);
  dense_jacobian.setZero();
  for (int r = 0; r < jacobian.num_rows; ++r) {
    for (int idx = jacobian.rows[r]; idx < jacobian.rows[r + 1]; ++idx) {
      const int c = jacobian.cols[idx];
      dense_jacobian(r, c) = jacobian.values[idx];
    }
  }
  event_logger.AddEvent("ConvertToDenseMatrix");

  Eigen::BDCSVD<Matrix> svd(dense_jacobian,
                            Eigen::ComputeThinU | Eigen::ComputeThinV);

  event_logger.AddEvent("SingularValueDecomposition");

  const Vector singular_values = svd.singularValues();
  const int num_singular_values = singular_values.rows();
  Vector inverse_squared_singular_values(num_singular_values);
  inverse_squared_singular_values.setZero();

  const double max_singular_value = singular_values[0];
  const double min_singular_value_ratio =
      sqrt(options_.min_reciprocal_condition_number);

  const bool automatic_truncation = (options_.null_space_rank < 0);
  const int max_rank = std::min(num_singular_values,
                                num_singular_values - options_.null_space_rank);

  // Compute the squared inverse of the singular values. Truncate the
  // computation based on min_singular_value_ratio and
  // null_space_rank. When either of these two quantities are active,
  // the resulting covariance matrix is a Moore-Penrose inverse
  // instead of a regular inverse.
  for (int i = 0; i < max_rank; ++i) {
    const double singular_value_ratio = singular_values[i] / max_singular_value;
    if (singular_value_ratio < min_singular_value_ratio) {
      // Since the singular values are in decreasing order, if
      // automatic truncation is enabled, then from this point on
      // all values will fail the ratio test and there is nothing to
      // do in this loop.
      if (automatic_truncation) {
        break;
      } else {
        LOG(ERROR) << "Error: Covariance matrix is near rank deficient "
                   << "and the user did not specify a non-zero"
                   << "Covariance::Options::null_space_rank "
                   << "to enable the computation of a Pseudo-Inverse. "
                   << "Reciprocal condition number: "
                   << singular_value_ratio * singular_value_ratio << " "
                   << "min_reciprocal_condition_number: "
                   << options_.min_reciprocal_condition_number;
        return false;
      }
    }

    inverse_squared_singular_values[i] =
        1.0 / (singular_values[i] * singular_values[i]);
  }

  Matrix dense_covariance = svd.matrixV() *
                            inverse_squared_singular_values.asDiagonal() *
                            svd.matrixV().transpose();
  event_logger.AddEvent("PseudoInverse");

  const int num_rows = covariance_matrix_->num_rows();
  const int* rows = covariance_matrix_->rows();
  const int* cols = covariance_matrix_->cols();
  double* values = covariance_matrix_->mutable_values();

  for (int r = 0; r < num_rows; ++r) {
    for (int idx = rows[r]; idx < rows[r + 1]; ++idx) {
      const int c = cols[idx];
      values[idx] = dense_covariance(r, c);
    }
  }
  event_logger.AddEvent("CopyToCovarianceMatrix");
  return true;
}
