// u0783 – ceres::internal::AreJacobianColumnsOrdered
// Trích từ internal/ceres/reorder_program.cc, dòng 609–642 (chỉ để xem, không compile)

bool AreJacobianColumnsOrdered(
    const LinearSolverType linear_solver_type,
    const PreconditionerType preconditioner_type,
    const SparseLinearAlgebraLibraryType sparse_linear_algebra_library_type,
    const LinearSolverOrderingType linear_solver_ordering_type) {
  if (sparse_linear_algebra_library_type == SUITE_SPARSE) {
    if (linear_solver_type == SPARSE_NORMAL_CHOLESKY ||
        (linear_solver_type == CGNR && preconditioner_type == SUBSET)) {
      return true;
    }
    if (linear_solver_type == SPARSE_SCHUR &&
        linear_solver_ordering_type == ceres::AMD) {
      return true;
    }
    return false;
  }

  if (sparse_linear_algebra_library_type == ceres::EIGEN_SPARSE) {
    if (linear_solver_type == SPARSE_NORMAL_CHOLESKY ||
        linear_solver_type == SPARSE_SCHUR ||
        (linear_solver_type == CGNR && preconditioner_type == SUBSET)) {
      return true;
    }
    return false;
  }

  if (sparse_linear_algebra_library_type == ceres::ACCELERATE_SPARSE) {
    // Apple's accelerate framework does not allow direct access to
    // ordering algorithms, so jacobian columns are never pre-ordered.
    return false;
  }

  return false;
}
