// u1510 – ceres::Covariance::GetCovarianceMatrixInTangentSpace
// Trích từ internal/ceres/covariance.cc, dòng 87–93 (chỉ để xem, không compile)

bool Covariance::GetCovarianceMatrixInTangentSpace(
    const std::vector<const double*>& parameter_blocks,
    double* covariance_matrix) const {
  return impl_->GetCovarianceMatrixInTangentOrAmbientSpace(parameter_blocks,
                                                           false,  // tangent
                                                           covariance_matrix);
}
