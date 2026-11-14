// u0464 – ceres::internal::MapValuesToContiguousRange
// Trích từ internal/ceres/array_utils.cc, dòng 93–104 (chỉ để xem, không compile)

void MapValuesToContiguousRange(const int64_t size, int* array) {
  std::vector<int> unique_values(array, array + size);
  std::sort(unique_values.begin(), unique_values.end());
  unique_values.erase(std::unique(unique_values.begin(), unique_values.end()),
                      unique_values.end());

  for (int64_t i = 0; i < size; ++i) {
    array[i] =
        std::lower_bound(unique_values.begin(), unique_values.end(), array[i]) -
        unique_values.begin();
  }
}
