// u1323 – ceres::Covariance::GetCovarianceBlockInTangentSpace
// Trích từ internal/ceres/covariance.cc, dòng 69–77 (chỉ để xem, không compile)

bool Covariance::GetCovarianceBlockInTangentSpace(
    const double* parameter_block1,
    const double* parameter_block2,
    double* covariance_block) const {
  return impl_->GetCovarianceBlockInTangentOrAmbientSpace(parameter_block1,
                                                          parameter_block2,
                                                          false,  // tangent
                                                          covariance_block);
}
