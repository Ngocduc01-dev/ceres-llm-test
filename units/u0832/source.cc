// u0832 – ceres_free_problem
// Trích từ internal/ceres/c_api.cc, dòng 62–64 (chỉ để xem, không compile)

void ceres_free_problem(ceres_problem_t* problem) {
  delete reinterpret_cast<Problem*>(problem);
}
