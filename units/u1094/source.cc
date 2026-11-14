// u1094 – ceres::StringToTrustRegionStrategyType
// Trích từ internal/ceres/types.cc, dòng 173–179 (chỉ để xem, không compile)

bool StringToTrustRegionStrategyType(std::string value,
                                     TrustRegionStrategyType* type) {
  UpperCase(&value);
  STRENUM(LEVENBERG_MARQUARDT);
  STRENUM(DOGLEG);
  return false;
}
