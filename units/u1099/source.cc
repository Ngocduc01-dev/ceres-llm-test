// u1099 – ceres::StringToVisibilityClusteringType
// Trích từ internal/ceres/types.cc, dòng 335–341 (chỉ để xem, không compile)

bool StringToVisibilityClusteringType(std::string value,
                                      VisibilityClusteringType* type) {
  UpperCase(&value);
  STRENUM(CANONICAL_VIEWS);
  STRENUM(SINGLE_LINKAGE);
  return false;
}
