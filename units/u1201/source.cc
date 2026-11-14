// u1201 – ceres::internal::CreateFakeBundleAdjustmentJacobian
// Trích từ internal/ceres/fake_bundle_adjustment_jacobian.cc, dòng 44–97 (chỉ để xem, không compile)

std::unique_ptr<BlockSparseMatrix> CreateFakeBundleAdjustmentJacobian(
    int num_cameras,
    int num_points,
    int camera_size,
    int point_size,
    double visibility,
    std::mt19937& prng) {
  constexpr int kResidualSize = 2;

  CompressedRowBlockStructure* bs = new CompressedRowBlockStructure;
  int c = 0;
  // Add column blocks for each point
  for (int i = 0; i < num_points; ++i) {
    bs->cols.push_back(Block(point_size, c));
    c += point_size;
  }

  // Add column blocks for each camera.
  for (int i = 0; i < num_cameras; ++i) {
    bs->cols.push_back(Block(camera_size, c));
    c += camera_size;
  }

  std::bernoulli_distribution visibility_distribution(visibility);
  int row_pos = 0;
  int cell_pos = 0;
  for (int i = 0; i < num_points; ++i) {
    for (int j = 0; j < num_cameras; ++j) {
      if (!visibility_distribution(prng)) {
        continue;
      }
      bs->rows.emplace_back();
      auto& row = bs->rows.back();
      row.block.position = row_pos;
      row.block.size = kResidualSize;
      auto& cells = row.cells;
      cells.resize(2);

      cells[0].block_id = i;
      cells[0].position = cell_pos;
      cell_pos += kResidualSize * point_size;

      cells[1].block_id = num_points + j;
      cells[1].position = cell_pos;
      cell_pos += kResidualSize * camera_size;

      row_pos += kResidualSize;
    }
  }

  auto jacobian = std::make_unique<BlockSparseMatrix>(bs);
  VectorRef(jacobian->mutable_values(), jacobian->num_nonzeros()).setRandom();
  return jacobian;
}
