// u1328 – ceres::internal::CreateFakeBundleAdjustmentPartitionedJacobian
// Trích từ internal/ceres/fake_bundle_adjustment_jacobian.h, dòng 50–64 (chỉ để xem, không compile)

template <int kEBlockSize = 3, int kFBlockSize = 6>
std::pair<std::unique_ptr<PartitionedMatrixView<2, kEBlockSize, kFBlockSize>>,
          std::unique_ptr<BlockSparseMatrix>>
CreateFakeBundleAdjustmentPartitionedJacobian(int num_cameras,
                                              int num_points,
                                              double visibility,
                                              std::mt19937& rng) {
  using PartitionedView = PartitionedMatrixView<2, kEBlockSize, kFBlockSize>;
  auto block_sparse_matrix = CreateFakeBundleAdjustmentJacobian(
      num_cameras, num_points, kFBlockSize, kEBlockSize, visibility, rng);
  auto partitioned_view =
      std::make_unique<PartitionedView>(*block_sparse_matrix, num_points);
  return std::make_pair(std::move(partitioned_view),
                        std::move(block_sparse_matrix));
}
