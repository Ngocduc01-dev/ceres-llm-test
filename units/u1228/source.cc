// u1228 – ceres::internal::(anonymous)::CreateBlockJacobian
// Trích từ internal/ceres/reorder_program.cc, dòng 92–110 (chỉ để xem, không compile)

Eigen::SparseMatrix<int> CreateBlockJacobian(
    const TripletSparseMatrix& block_jacobian_transpose) {
  using SparseMatrix = Eigen::SparseMatrix<int>;
  using Triplet = Eigen::Triplet<int>;

  const int* rows = block_jacobian_transpose.rows();
  const int* cols = block_jacobian_transpose.cols();
  int num_nonzeros = block_jacobian_transpose.num_nonzeros();
  std::vector<Triplet> triplets;
  triplets.reserve(num_nonzeros);
  for (int i = 0; i < num_nonzeros; ++i) {
    triplets.emplace_back(cols[i], rows[i], 1);
  }

  SparseMatrix block_jacobian(block_jacobian_transpose.num_cols(),
                              block_jacobian_transpose.num_rows());
  block_jacobian.setFromTriplets(triplets.begin(), triplets.end());
  return block_jacobian;
}
