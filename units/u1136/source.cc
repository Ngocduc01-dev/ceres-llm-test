// u1136 – ceres::internal::SchurEliminator::ChunkOuterProduct
// Trích từ internal/ceres/schur_eliminator_impl.h, dòng 511–561 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
void SchurEliminator<kRowBlockSize, kEBlockSize, kFBlockSize>::
    ChunkOuterProduct(int thread_id,
                      const CompressedRowBlockStructure* bs,
                      const Matrix& inverse_ete,
                      const double* buffer,
                      const BufferLayoutType& buffer_layout,
                      BlockRandomAccessMatrix* lhs) {
  // This is the most computationally expensive part of this
  // code. Profiling experiments reveal that the bottleneck is not the
  // computation of the right-hand matrix product, but memory
  // references to the left hand side.
  const int e_block_size = inverse_ete.rows();
  auto it1 = buffer_layout.begin();

  double* b1_transpose_inverse_ete =
      chunk_outer_product_buffer_.get() + thread_id * buffer_size_;

  // S(i,j) -= bi' * ete^{-1} b_j
  for (; it1 != buffer_layout.end(); ++it1) {
    const int block1 = it1->first - num_eliminate_blocks_;
    const int block1_size = bs->cols[it1->first].size;
    // clang-format off
    MatrixTransposeMatrixMultiply
        <kEBlockSize, kFBlockSize, kEBlockSize, kEBlockSize, 0>(
        buffer + it1->second, e_block_size, block1_size,
        inverse_ete.data(), e_block_size, e_block_size,
        b1_transpose_inverse_ete, 0, 0, block1_size, e_block_size);
    // clang-format on

    auto it2 = it1;
    for (; it2 != buffer_layout.end(); ++it2) {
      const int block2 = it2->first - num_eliminate_blocks_;

      int r, c, row_stride, col_stride;
      CellInfo* cell_info =
          lhs->GetCell(block1, block2, &r, &c, &row_stride, &col_stride);
      if (cell_info != nullptr) {
        const int block2_size = bs->cols[it2->first].size;
        auto lock = MakeConditionalLock(num_threads_, cell_info->m);
        // clang-format off
        MatrixMatrixMultiply
            <kFBlockSize, kEBlockSize, kEBlockSize, kFBlockSize, -1>(
                b1_transpose_inverse_ete, block1_size, e_block_size,
                buffer  + it2->second, e_block_size, block2_size,
                cell_info->values, r, c, row_stride, col_stride);
        // clang-format on
      }
    }
  }
}
