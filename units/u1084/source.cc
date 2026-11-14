// u1084 – ceres::internal::StringAppendF
// Trích từ internal/ceres/stringprintf.cc, dòng 111–116 (chỉ để xem, không compile)

void StringAppendF(std::string* dst, const char* format, ...) {
  va_list ap;
  va_start(ap, format);
  StringAppendV(dst, format, ap);
  va_end(ap);
}
