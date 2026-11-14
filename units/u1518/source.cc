// u1518 – ceres::internal::CovarianceImpl::ComputeCovarianceValues
// Trích từ internal/ceres/covariance_impl.cc, dòng 500–533 (chỉ để xem, không compile)

bool CovarianceImpl::ComputeCovarianceValues() {
  if (options_.algorithm_type == DENSE_SVD) {
    return ComputeCovarianceValuesUsingDenseSVD();
  }

  if (options_.algorithm_type == SPARSE_QR) {
    if (options_.sparse_linear_algebra_library_type == EIGEN_SPARSE) {
      return ComputeCovarianceValuesUsingEigenSparseQR();
    }

    if (options_.sparse_linear_algebra_library_type == SUITE_SPARSE) {
#if !defined(CERES_NO_SUITESPARSE)
      return ComputeCovarianceValuesUsingSuiteSparseQR();
#else
      LOG(ERROR) << "SuiteSparse is required to use the SPARSE_QR algorithm "
                 << "with "
                 << "Covariance::Options::sparse_linear_algebra_library_type "
                 << "= SUITE_SPARSE.";
      return false;
#endif
    }

    LOG(ERROR) << "Unsupported "
               << "Covariance::Options::sparse_linear_algebra_library_type "
               << "= "
               << SparseLinearAlgebraLibraryTypeToString(
                      options_.sparse_linear_algebra_library_type);
    return false;
  }

  LOG(ERROR) << "Unsupported Covariance::Options::algorithm_type = "
             << CovarianceAlgorithmTypeToString(options_.algorithm_type);
  return false;
}
