// u0950 – ceres::internal::TripletSparseMatrix::Resize
// Trích từ internal/ceres/triplet_sparse_matrix.cc, dòng 237–264 (chỉ để xem, không compile)

void TripletSparseMatrix::Resize(int new_num_rows, int new_num_cols) {
  if ((new_num_rows >= num_rows_) && (new_num_cols >= num_cols_)) {
    num_rows_ = new_num_rows;
    num_cols_ = new_num_cols;
    return;
  }

  num_rows_ = new_num_rows;
  num_cols_ = new_num_cols;

  int* r_ptr = rows_.get();
  int* c_ptr = cols_.get();
  double* v_ptr = values_.get();

  int dropped_terms = 0;
  for (int i = 0; i < num_nonzeros_; ++i) {
    if ((r_ptr[i] < num_rows_) && (c_ptr[i] < num_cols_)) {
      if (dropped_terms) {
        r_ptr[i - dropped_terms] = r_ptr[i];
        c_ptr[i - dropped_terms] = c_ptr[i];
        v_ptr[i - dropped_terms] = v_ptr[i];
      }
    } else {
      ++dropped_terms;
    }
  }
  num_nonzeros_ -= dropped_terms;
}
