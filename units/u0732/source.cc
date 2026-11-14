// u0732 – ceres::DoglegTypeToString
// Trích từ internal/ceres/types.cc, dòng 181–188 (chỉ để xem, không compile)

const char* DoglegTypeToString(DoglegType type) {
  switch (type) {
    CASESTR(TRADITIONAL_DOGLEG);
    CASESTR(SUBSPACE_DOGLEG);
    default:
      return "UNKNOWN";
  }
}
