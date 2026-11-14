// u1322 – ceres::Covariance::GetCovarianceBlock
// Trích từ internal/ceres/covariance.cc, dòng 60–67 (chỉ để xem, không compile)

bool Covariance::GetCovarianceBlock(const double* parameter_block1,
                                    const double* parameter_block2,
                                    double* covariance_block) const {
  return impl_->GetCovarianceBlockInTangentOrAmbientSpace(parameter_block1,
                                                          parameter_block2,
                                                          true,  // ambient
                                                          covariance_block);
}
