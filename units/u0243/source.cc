// u0243 – ceres_init
// Trích từ internal/ceres/c_api.cc, dòng 51–56 (chỉ để xem, không compile)

void ceres_init() {
  // This is not ideal, but it's not clear what to do if there is no gflags and
  // no access to command line arguments.
  char message[] = "<unknown>";
  google::InitGoogleLogging(message);
}
