// u1060 – ceres::internal::MatrixTransposeVectorMultiply
// Trích từ internal/ceres/small_blas.h, dòng 470–554 (chỉ để xem, không compile)

template <int kRowA, int kColA, int kOperation>
inline void MatrixTransposeVectorMultiply(const double* A,
                                          const int num_row_a,
                                          const int num_col_a,
                                          const double* b,
                                          double* c) {
#ifdef CERES_NO_CUSTOM_BLAS
  const typename EigenTypes<kRowA, kColA>::ConstMatrixRef Aref(
      A, num_row_a, num_col_a);
  const typename EigenTypes<kRowA>::ConstVectorRef bref(b, num_row_a);
  typename EigenTypes<kColA>::VectorRef cref(c, num_col_a);

  // lazyProduct works better than .noalias() for matrix-vector
  // products.
  if (kOperation > 0) {
    cref += Aref.transpose().lazyProduct(bref);
  } else if (kOperation < 0) {
    cref -= Aref.transpose().lazyProduct(bref);
  } else {
    cref = Aref.transpose().lazyProduct(bref);
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

  // Process the last odd column if present.
  if (NUM_COL_A & 1) {
    int row = NUM_COL_A - 1;
    const double* pa = &A[row];
    const double* pb = &b[0];
    double tmp = 0.0;
    for (int col = 0; col < NUM_ROW_A; ++col) {
      tmp += *pa * (*pb++);
      pa += NUM_COL_A;
    }
    CERES_GEMM_STORE_SINGLE(c, row, tmp);

    // Return directly for efficiency of extremely small matrix multiply.
    if (NUM_COL_A == 1) {
      return;
    }
  }

  // Process the couple columns in remainder if present.
  if (NUM_COL_A & 2) {
    int row = NUM_COL_A & (~(span - 1));
    const double* pa = &A[row];
    const double* pb = &b[0];
    double tmp1 = 0.0, tmp2 = 0.0;
    for (int col = 0; col < NUM_ROW_A; ++col) {
      // clang-format off
      double bv = *pb++;
      tmp1 += *(pa    ) * bv;
      tmp2 += *(pa + 1) * bv;
      pa += NUM_COL_A;
      // clang-format on
    }
    CERES_GEMM_STORE_PAIR(c, row, tmp1, tmp2);

    // Return directly for efficiency of extremely small matrix multiply.
    if (NUM_COL_A < span) {
      return;
    }
  }

  // Calculate the main part with multiples of 4.
  int row_m = NUM_COL_A & (~(span - 1));
  for (int row = 0; row < row_m; row += span) {
    // clang-format off
    MTV_mat4x1(NUM_ROW_A, &A[row], NUM_COL_A,
               &b[0], &c[row], kOperation);
    // clang-format on
  }

#endif  // CERES_NO_CUSTOM_BLAS
}
