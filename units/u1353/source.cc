// u1353 – ceres::internal::CompressedRowJacobianWriter::PopulateJacobianRowAndColumnBlockVectors
// Trích từ internal/ceres/compressed_row_jacobian_writer.cc, dòng 48–69 (chỉ để xem, không compile)

void CompressedRowJacobianWriter::PopulateJacobianRowAndColumnBlockVectors(
    const Program* program, CompressedRowSparseMatrix* jacobian) {
  const auto& parameter_blocks = program->parameter_blocks();
  auto& col_blocks = *(jacobian->mutable_col_blocks());
  col_blocks.resize(parameter_blocks.size());
  int col_pos = 0;
  for (int i = 0; i < parameter_blocks.size(); ++i) {
    col_blocks[i].size = parameter_blocks[i]->TangentSize();
    col_blocks[i].position = col_pos;
    col_pos += col_blocks[i].size;
  }

  const auto& residual_blocks = program->residual_blocks();
  auto& row_blocks = *(jacobian->mutable_row_blocks());
  row_blocks.resize(residual_blocks.size());
  int row_pos = 0;
  for (int i = 0; i < residual_blocks.size(); ++i) {
    row_blocks[i].size = residual_blocks[i]->NumResiduals();
    row_blocks[i].position = row_pos;
    row_pos += row_blocks[i].size;
  }
}
