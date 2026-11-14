// u1293 – ceres::internal::AppendArrayToString
// Trích từ internal/ceres/array_utils.cc, dòng 77–91 (chỉ để xem, không compile)

void AppendArrayToString(const int64_t size,
                         const double* x,
                         std::string* result) {
  for (int64_t i = 0; i < size; ++i) {
    if (x == nullptr) {
      StringAppendF(result, "Not Computed  ");
    } else {
      if (x[i] == kImpossibleValue) {
        StringAppendF(result, "Uninitialized ");
      } else {
        StringAppendF(result, "%12g ", x[i]);
      }
    }
  }
}
