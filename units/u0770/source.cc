// u0770 – ceres::TerminationTypeToString
// Trích từ internal/ceres/types.cc, dòng 343–353 (chỉ để xem, không compile)

const char* TerminationTypeToString(TerminationType type) {
  switch (type) {
    CASESTR(CONVERGENCE);
    CASESTR(NO_CONVERGENCE);
    CASESTR(FAILURE);
    CASESTR(USER_SUCCESS);
    CASESTR(USER_FAILURE);
    default:
      return "UNKNOWN";
  }
}
