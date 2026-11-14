// u1062 – ceres::internal::MatrixTransposeMatrixMultiplyNaive
// Trích từ internal/ceres/small_blas.h, dòng 280–351 (chỉ để xem, không compile)

CERES_GEMM_BEGIN(MatrixTransposeMatrixMultiplyNaive) {
  CERES_GEMM_NAIVE_HEADER
  DCHECK_EQ(NUM_ROW_A, NUM_ROW_B);

  const int NUM_ROW_C = NUM_COL_A;
  const int NUM_COL_C = NUM_COL_B;
  DCHECK_LE(start_row_c + NUM_ROW_C, row_stride_c);
  DCHECK_LE(start_col_c + NUM_COL_C, col_stride_c);
  const int span = 4;

  // Process the remainder part first.

  // Process the last odd column if present.
  if (NUM_COL_C & 1) {
    int col = NUM_COL_C - 1;
    for (int row = 0; row < NUM_ROW_C; ++row) {
      const double* pa = &A[row];
      const double* pb = &B[col];
      double tmp = 0.0;
      for (int k = 0; k < NUM_ROW_A; ++k) {
        tmp += pa[0] * pb[0];
        pa += NUM_COL_A;
        pb += NUM_COL_B;
      }

      const int index = (row + start_row_c) * col_stride_c + start_col_c + col;
      CERES_GEMM_STORE_SINGLE(C, index, tmp);
    }

    // Return directly for efficiency of extremely small matrix multiply.
    if (NUM_COL_C == 1) {
      return;
    }
  }

  // Process the couple columns in remainder if present.
  if (NUM_COL_C & 2) {
    int col = NUM_COL_C & (~(span - 1));
    for (int row = 0; row < NUM_ROW_C; ++row) {
      const double* pa = &A[row];
      const double* pb = &B[col];
      double tmp1 = 0.0, tmp2 = 0.0;
      for (int k = 0; k < NUM_ROW_A; ++k) {
        double av = *pa;
        tmp1 += av * pb[0];
        tmp2 += av * pb[1];
        pa += NUM_COL_A;
        pb += NUM_COL_B;
      }

      const int index = (row + start_row_c) * col_stride_c + start_col_c + col;
      CERES_GEMM_STORE_PAIR(C, index, tmp1, tmp2);
    }

    // Return directly for efficiency of extremely small matrix multiply.
    if (NUM_COL_C < span) {
      return;
    }
  }

  // Process the main part with multiples of 4.
  int col_m = NUM_COL_C & (~(span - 1));
  for (int col = 0; col < col_m; col += span) {
    for (int row = 0; row < NUM_ROW_C; ++row) {
      const int index = (row + start_row_c) * col_stride_c + start_col_c + col;
      // clang-format off
      MTM_mat1x4(NUM_ROW_A, &A[row], NUM_COL_A,
                 &B[col], NUM_COL_B, &C[index], kOperation);
      // clang-format on
    }
  }
}
