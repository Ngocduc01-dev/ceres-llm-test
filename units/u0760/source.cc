// u0760 – ceres::internal::JoinPath
// Trích từ internal/ceres/file.cc, dòng 76–90 (chỉ để xem, không compile)

std::string JoinPath(const std::string& dirname, const std::string& basename) {
#ifdef _WIN32
  static const char separator = '\\';
#else
  static const char separator = '/';
#endif  // _WIN32

  if ((!basename.empty() && basename[0] == separator) || dirname.empty()) {
    return basename;
  } else if (dirname[dirname.size() - 1] == separator) {
    return dirname + basename;
  } else {
    return dirname + std::string(&separator, 1) + basename;
  }
}
