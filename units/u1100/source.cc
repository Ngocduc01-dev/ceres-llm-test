// u1100 – ceres::StringtoLoggingType
// Trích từ internal/ceres/types.cc, dòng 364–369 (chỉ để xem, không compile)

bool StringtoLoggingType(std::string value, LoggingType* type) {
  UpperCase(&value);
  STRENUM(SILENT);
  STRENUM(PER_MINIMIZER_ITERATION);
  return false;
}
