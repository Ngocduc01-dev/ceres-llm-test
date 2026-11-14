// u1509 – ceres::Covariance::GetCovarianceMatrix
// Trích từ internal/ceres/covariance.cc, dòng 79–85 (chỉ để xem, không compile)

bool Covariance::GetCovarianceMatrix(
    const std::vector<const double*>& parameter_blocks,
    double* covariance_matrix) const {
  return impl_->GetCovarianceMatrixInTangentOrAmbientSpace(parameter_blocks,
                                                           true,  // ambient
                                                           covariance_matrix);
}
