// u1138 – ceres::(anonymous)::IsNestedDissectionAvailable
// Trích từ internal/ceres/solver.cc, dòng 111–117 (chỉ để xem, không compile)

bool IsNestedDissectionAvailable(SparseLinearAlgebraLibraryType type) {
  return (((type == SUITE_SPARSE) &&
           internal::SuiteSparse::IsNestedDissectionAvailable()) ||
          (type == ACCELERATE_SPARSE) ||
          ((type == EIGEN_SPARSE) &&
           internal::EigenSparse::IsNestedDissectionAvailable()));
}
