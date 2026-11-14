// u0847 – ceres::internal::CovarianceImpl::covariance_matrix
// Trích từ internal/ceres/covariance_impl.h, dòng 83–85 (chỉ để xem, không compile)

  const CompressedRowSparseMatrix* covariance_matrix() const {
    return covariance_matrix_.get();
  }
