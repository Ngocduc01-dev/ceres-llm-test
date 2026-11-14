// u1438 – ceres::internal::DumpLinearLeastSquaresProblem
// Trích từ internal/ceres/linear_least_squares_problems.cc, dòng 1023–1042 (chỉ để xem, không compile)

bool DumpLinearLeastSquaresProblem(const std::string& filename_base,
                                   DumpFormatType dump_format_type,
                                   const SparseMatrix* A,
                                   const double* D,
                                   const double* b,
                                   const double* x,
                                   int num_eliminate_blocks) {
  switch (dump_format_type) {
    case CONSOLE:
      return DumpLinearLeastSquaresProblemToConsole(
          A, D, b, x, num_eliminate_blocks);
    case TEXTFILE:
      return DumpLinearLeastSquaresProblemToTextFile(
          filename_base, A, D, b, x, num_eliminate_blocks);
    default:
      LOG(FATAL) << "Unknown DumpFormatType " << dump_format_type;
  }

  return true;
}
