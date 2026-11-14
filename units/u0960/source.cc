// u0960 – ceres::internal::InnerProductComputer::InnerProductComputer
// Trích từ internal/ceres/inner_product_computer.cc, dòng 98–101 (chỉ để xem, không compile)

InnerProductComputer::InnerProductComputer(const BlockSparseMatrix& m,
                                           const int start_row_block,
                                           const int end_row_block)
    : m_(m), start_row_block_(start_row_block), end_row_block_(end_row_block) {}
