// u0972 – ceres::internal::DoglegStrategy::ComputeSubspaceModel
// Trích từ internal/ceres/dogleg_strategy.cc, dòng 647–716 (chỉ để xem, không compile)

bool DoglegStrategy::ComputeSubspaceModel(SparseMatrix* jacobian) {
  // Compute an orthogonal basis for the subspace using QR decomposition.
  Matrix basis_vectors(jacobian->num_cols(), 2);
  basis_vectors.col(0) = gradient_;
  basis_vectors.col(1) = gauss_newton_step_;
  Eigen::ColPivHouseholderQR<Matrix> basis_qr(basis_vectors);

  switch (basis_qr.rank()) {
    case 0:
      // This should never happen, as it implies that both the gradient
      // and the Gauss-Newton step are zero. In this case, the minimizer should
      // have stopped due to the gradient being too small.
      LOG(ERROR) << "Rank of subspace basis is 0. "
                 << "This means that the gradient at the current iterate is "
                 << "zero but the optimization has not been terminated. "
                 << "You may have found a bug in Ceres.";
      return false;

    case 1:
      // Gradient and Gauss-Newton step coincide, so we lie on one of the
      // major axes of the quadratic problem. In this case, we simply move
      // along the gradient until we reach the trust region boundary.
      subspace_is_one_dimensional_ = true;
      return true;

    case 2:
      subspace_is_one_dimensional_ = false;
      break;

    default:
      LOG(ERROR) << "Rank of the subspace basis matrix is reported to be "
                 << "greater than 2. As the matrix contains only two "
                 << "columns this cannot be true and is indicative of "
                 << "a bug.";
      return false;
  }

  // The subspace is two-dimensional, so compute the subspace model.
  // Given the basis U, this is
  //
  //   subspace_g_ = g_scaled^T U
  //
  // and
  //
  //   subspace_B_ = U^T (J_scaled^T J_scaled) U
  //
  // As J_scaled = J * D^-1, the latter becomes
  //
  //   subspace_B_ = ((U^T D^-1) J^T) (J (D^-1 U))
  //               = (J (D^-1 U))^T (J (D^-1 U))

  subspace_basis_ =
      basis_qr.householderQ() * Matrix::Identity(jacobian->num_cols(), 2);

  subspace_g_ = subspace_basis_.transpose() * gradient_;

  Eigen::Matrix<double, 2, Eigen::Dynamic, Eigen::RowMajor> Jb(
      2, jacobian->num_rows());
  Jb.setZero();

  Vector tmp;
  tmp = (subspace_basis_.col(0).array() / diagonal_.array()).matrix();
  jacobian->RightMultiplyAndAccumulate(tmp.data(), Jb.row(0).data());
  tmp = (subspace_basis_.col(1).array() / diagonal_.array()).matrix();
  jacobian->RightMultiplyAndAccumulate(tmp.data(), Jb.row(1).data());

  subspace_B_ = Jb * Jb.transpose();

  return true;
}
