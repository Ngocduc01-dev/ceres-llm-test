// u1023 – ceres::internal::StringPrintf
// Trích từ internal/ceres/stringprintf.cc, dòng 93–100 (chỉ để xem, không compile)

std::string StringPrintf(const char* format, ...) {
  va_list ap;
  va_start(ap, format);
  std::string result;
  StringAppendV(&result, format, ap);
  va_end(ap);
  return result;
}
