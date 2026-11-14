// u1194 – ceres::internal::CompressedRowSparseMatrix::Transpose
// Trích từ internal/ceres/compressed_row_sparse_matrix.cc, dòng 600–638 (chỉ để xem, không compile)

std::unique_ptr<CompressedRowSparseMatrix>
CompressedRowSparseMatrix::Transpose() const {
  auto transpose = std::make_unique<CompressedRowSparseMatrix>(
      num_cols_, num_rows_, num_nonzeros());

  switch (storage_type_) {
    case StorageType::UNSYMMETRIC:
      transpose->set_storage_type(StorageType::UNSYMMETRIC);
      break;
    case StorageType::LOWER_TRIANGULAR:
      transpose->set_storage_type(StorageType::UPPER_TRIANGULAR);
      break;
    case StorageType::UPPER_TRIANGULAR:
      transpose->set_storage_type(StorageType::LOWER_TRIANGULAR);
      break;
    default:
      LOG(FATAL) << "Unknown storage type: " << storage_type_;
  };

  TransposeForCompressedRowSparseStructure(num_rows(),
                                           num_cols(),
                                           num_nonzeros(),
                                           rows(),
                                           cols(),
                                           values(),
                                           transpose->mutable_rows(),
                                           transpose->mutable_cols(),
                                           transpose->mutable_values());

  // The rest of the code updates the block information. Immediately
  // return in case of no block information.
  if (row_blocks_.empty()) {
    return transpose;
  }

  *(transpose->mutable_row_blocks()) = col_blocks_;
  *(transpose->mutable_col_blocks()) = row_blocks_;
  return transpose;
}
