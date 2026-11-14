// u1373 – ceres::internal::(anonymous)::OrderingForSparseNormalCholeskyUsingEigenSparse
// Trích từ internal/ceres/reorder_program.cc, dòng 169–210 (chỉ để xem, không compile)

void OrderingForSparseNormalCholeskyUsingEigenSparse(
    const LinearSolverOrderingType linear_solver_ordering_type,
    const TripletSparseMatrix& tsm_block_jacobian_transpose,
    int* ordering) {
#ifndef CERES_USE_EIGEN_SPARSE
  LOG(FATAL) << "SPARSE_NORMAL_CHOLESKY cannot be used with EIGEN_SPARSE "
                "because Ceres was not built with support for "
                "Eigen's SimplicialLDLT decomposition. "
                "This requires enabling building with -DEIGENSPARSE=ON.";
#else

  // TODO(sameeragarwal): This conversion from a TripletSparseMatrix
  // to a Eigen::Triplet matrix is unfortunate, but unavoidable for
  // now. It is not a significant performance penalty in the grand
  // scheme of things. The right thing to do here would be to get a
  // compressed row sparse matrix representation of the jacobian and
  // go from there. But that is a project for another day.
  using SparseMatrix = Eigen::SparseMatrix<int>;

  const SparseMatrix block_jacobian =
      CreateBlockJacobian(tsm_block_jacobian_transpose);
  const SparseMatrix block_hessian =
      block_jacobian.transpose() * block_jacobian;

  Eigen::PermutationMatrix<Eigen::Dynamic, Eigen::Dynamic, int> perm;
  if (linear_solver_ordering_type == ceres::AMD) {
    Eigen::AMDOrdering<int> amd_ordering;
    amd_ordering(block_hessian, perm);
  } else {
#ifndef CERES_NO_EIGEN_METIS
    Eigen::MetisOrdering<int> metis_ordering;
    metis_ordering(block_hessian, perm);
#else
    perm.setIdentity(block_hessian.rows());
#endif
  }

  for (int i = 0; i < block_hessian.rows(); ++i) {
    ordering[i] = perm.indices()[i];
  }
#endif  // CERES_USE_EIGEN_SPARSE
}
