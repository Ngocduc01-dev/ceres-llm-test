// u1059 – ceres::internal::MatrixVectorMultiply
// Trích từ internal/ceres/small_blas.h, dòng 384–465 (chỉ để xem, không compile)

template <int kRowA, int kColA, int kOperation>
inline void MatrixVectorMultiply(const double* A,
                                 const int num_row_a,
                                 const int num_col_a,
                                 const double* b,
                                 double* c) {
#ifdef CERES_NO_CUSTOM_BLAS
  const typename EigenTypes<kRowA, kColA>::ConstMatrixRef Aref(
      A, num_row_a, num_col_a);
  const typename EigenTypes<kColA>::ConstVectorRef bref(b, num_col_a);
  typename EigenTypes<kRowA>::VectorRef cref(c, num_row_a);

  // lazyProduct works better than .noalias() for matrix-vector
  // products.
  if (kOperation > 0) {
    cref += Aref.lazyProduct(bref);
  } else if (kOperation < 0) {
    cref -= Aref.lazyProduct(bref);
  } else {
    cref = Aref.lazyProduct(bref);
  }
#else

  DCHECK_GT(num_row_a, 0);
  DCHECK_GT(num_col_a, 0);
  DCHECK((kRowA == Eigen::Dynamic) || (kRowA == num_row_a));
  DCHECK((kColA == Eigen::Dynamic) || (kColA == num_col_a));

  const int NUM_ROW_A = (kRowA != Eigen::Dynamic ? kRowA : num_row_a);
  const int NUM_COL_A = (kColA != Eigen::Dynamic ? kColA : num_col_a);
  const int span = 4;

  // Calculate the remainder part first.

  // Process the last odd row if present.
  if (NUM_ROW_A & 1) {
    int row = NUM_ROW_A - 1;
    const double* pa = &A[row * NUM_COL_A];
    const double* pb = &b[0];
    double tmp = 0.0;
    for (int col = 0; col < NUM_COL_A; ++col) {
      tmp += (*pa++) * (*pb++);
    }
    CERES_GEMM_STORE_SINGLE(c, row, tmp);

    // Return directly for efficiency of extremely small matrix multiply.
    if (NUM_ROW_A == 1) {
      return;
    }
  }

  // Process the couple rows in remainder if present.
  if (NUM_ROW_A & 2) {
    int row = NUM_ROW_A & (~(span - 1));
    const double* pa1 = &A[row * NUM_COL_A];
    const double* pa2 = pa1 + NUM_COL_A;
    const double* pb = &b[0];
    double tmp1 = 0.0, tmp2 = 0.0;
    for (int col = 0; col < NUM_COL_A; ++col) {
      double bv = *pb++;
      tmp1 += *(pa1++) * bv;
      tmp2 += *(pa2++) * bv;
    }
    CERES_GEMM_STORE_PAIR(c, row, tmp1, tmp2);

    // Return directly for efficiency of extremely small matrix multiply.
    if (NUM_ROW_A < span) {
      return;
    }
  }

  // Calculate the main part with multiples of 4.
  int row_m = NUM_ROW_A & (~(span - 1));
  for (int row = 0; row < row_m; row += span) {
    // clang-format off
    MVM_mat4x1(NUM_COL_A, &A[row * NUM_COL_A], NUM_COL_A,
               &b[0], &c[row], kOperation);
    // clang-format on
  }

#endif  // CERES_NO_CUSTOM_BLAS
}
