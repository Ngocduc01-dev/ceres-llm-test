// u1083 – ceres::internal::SStringPrintf
// Trích từ internal/ceres/stringprintf.cc, dòng 102–109 (chỉ để xem, không compile)

const std::string& SStringPrintf(std::string* dst, const char* format, ...) {
  va_list ap;
  va_start(ap, format);
  dst->clear();
  StringAppendV(dst, format, ap);
  va_end(ap);
  return *dst;
}
