// u0736 – ceres::VisibilityClusteringTypeToString
// Trích từ internal/ceres/types.cc, dòng 326–333 (chỉ để xem, không compile)

const char* VisibilityClusteringTypeToString(VisibilityClusteringType type) {
  switch (type) {
    CASESTR(CANONICAL_VIEWS);
    CASESTR(SINGLE_LINKAGE);
    default:
      return "UNKNOWN";
  }
}
