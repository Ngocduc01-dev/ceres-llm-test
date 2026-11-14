// u1184 – ceres::internal::InnerProductComputer::Create
// Trích từ internal/ceres/inner_product_computer.cc, dòng 124–139 (chỉ để xem, không compile)

std::unique_ptr<InnerProductComputer> InnerProductComputer::Create(
    const BlockSparseMatrix& m,
    const int start_row_block,
    const int end_row_block,
    CompressedRowSparseMatrix::StorageType product_storage_type) {
  CHECK(product_storage_type ==
            CompressedRowSparseMatrix::StorageType::LOWER_TRIANGULAR ||
        product_storage_type ==
            CompressedRowSparseMatrix::StorageType::UPPER_TRIANGULAR);
  CHECK_GT(m.num_nonzeros(), 0)
      << "Congratulations, you found a bug in Ceres. Please report it.";
  std::unique_ptr<InnerProductComputer> inner_product_computer(
      new InnerProductComputer(m, start_row_block, end_row_block));
  inner_product_computer->Init(product_storage_type);
  return inner_product_computer;
}
