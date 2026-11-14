// u0810 – ceres::internal::(anonymous)::WriteArrayToFileOrDie
// Trích từ internal/ceres/linear_least_squares_problems.cc, dòng 953–964 (chỉ để xem, không compile)

void WriteArrayToFileOrDie(const std::string& filename,
                           const double* x,
                           const int size) {
  CHECK(x != nullptr);
  VLOG(2) << "Writing array to: " << filename;
  FILE* fptr = fopen(filename.c_str(), "w");
  CHECK(fptr != nullptr);
  for (int i = 0; i < size; ++i) {
    fprintf(fptr, "%17f\n", x[i]);
  }
  fclose(fptr);
}
