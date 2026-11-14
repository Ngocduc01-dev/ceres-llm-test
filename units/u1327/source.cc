// u1327 – ceres::internal::CreateFakeBundleAdjustmentPartitionedJacobian
// Trích từ internal/ceres/fake_bundle_adjustment_jacobian.cc, dòng 99–118 (chỉ để xem, không compile)

std::pair<
    std::unique_ptr<PartitionedMatrixView<2, Eigen::Dynamic, Eigen::Dynamic>>,
    std::unique_ptr<BlockSparseMatrix>>
CreateFakeBundleAdjustmentPartitionedJacobian(int num_cameras,
                                              int num_points,
                                              int camera_size,
                                              int landmark_size,
                                              double visibility,
                                              std::mt19937& rng) {
  using PartitionedView =
      PartitionedMatrixView<2, Eigen::Dynamic, Eigen::Dynamic>;
  auto block_sparse_matrix = CreateFakeBundleAdjustmentJacobian(
      num_cameras, num_points, camera_size, landmark_size, visibility, rng);
  LinearSolver::Options options;
  options.elimination_groups.push_back(num_points);
  auto partitioned_view =
      std::make_unique<PartitionedView>(options, *block_sparse_matrix);
  return std::make_pair(std::move(partitioned_view),
                        std::move(block_sparse_matrix));
}
