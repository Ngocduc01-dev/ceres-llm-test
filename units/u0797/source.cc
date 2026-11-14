// u0797 – ceres::UpperCase
// Trích từ internal/ceres/types.cc, dòng 47–49 (chỉ để xem, không compile)

static void UpperCase(std::string* input) {
  std::transform(input->begin(), input->end(), input->begin(), ::toupper);
}
