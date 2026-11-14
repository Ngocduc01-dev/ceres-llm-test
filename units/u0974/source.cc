// u0974 – ceres::internal::(anonymous)::DumpLinearLeastSquaresProblemToConsole
// Trích từ internal/ceres/linear_least_squares_problems.cc, dòng 929–951 (chỉ để xem, không compile)

bool DumpLinearLeastSquaresProblemToConsole(const SparseMatrix* A,
                                            const double* D,
                                            const double* b,
                                            const double* x,
                                            int /*num_eliminate_blocks*/) {
  CHECK(A != nullptr);
  Matrix AA;
  A->ToDenseMatrix(&AA);
  LOG(INFO) << "A^T: \n" << AA.transpose();

  if (D != nullptr) {
    LOG(INFO) << "A's appended diagonal:\n" << ConstVectorRef(D, A->num_cols());
  }

  if (b != nullptr) {
    LOG(INFO) << "b: \n" << ConstVectorRef(b, A->num_rows());
  }

  if (x != nullptr) {
    LOG(INFO) << "x: \n" << ConstVectorRef(x, A->num_cols());
  }
  return true;
}
