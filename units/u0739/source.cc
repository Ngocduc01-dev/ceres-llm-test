// u0739 – ceres::IsSchurType
// Trích từ internal/ceres/types.cc, dòng 390–396 (chỉ để xem, không compile)

bool IsSchurType(LinearSolverType type) {
  // clang-format off
  return ((type == SPARSE_SCHUR) ||
          (type == DENSE_SCHUR)  ||
          (type == ITERATIVE_SCHUR));
  // clang-format on
}
