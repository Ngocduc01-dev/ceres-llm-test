// u1150 – ceres::internal::InnerProductComputer::Create
// Trích từ internal/ceres/inner_product_computer.cc, dòng 117–122 (chỉ để xem, không compile)

std::unique_ptr<InnerProductComputer> InnerProductComputer::Create(
    const BlockSparseMatrix& m,
    CompressedRowSparseMatrix::StorageType product_storage_type) {
  return InnerProductComputer::Create(
      m, 0, m.block_structure()->rows.size(), product_storage_type);
}
