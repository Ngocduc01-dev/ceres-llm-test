// u1061 – ceres::internal::MatrixMatrixMultiplyNaive
// Trích từ internal/ceres/small_blas.h, dòng 177–244 (chỉ để xem, không compile)

CERES_GEMM_BEGIN(MatrixMatrixMultiplyNaive) {
  CERES_GEMM_NAIVE_HEADER
  DCHECK_EQ(NUM_COL_A, NUM_ROW_B);

  const int NUM_ROW_C = NUM_ROW_A;
  const int NUM_COL_C = NUM_COL_B;
  DCHECK_LE(start_row_c + NUM_ROW_C, row_stride_c);
  DCHECK_LE(start_col_c + NUM_COL_C, col_stride_c);
  const int span = 4;

  // Calculate the remainder part first.

  // Process the last odd column if present.
  if (NUM_COL_C & 1) {
    int col = NUM_COL_C - 1;
    const double* pa = &A[0];
    for (int row = 0; row < NUM_ROW_C; ++row, pa += NUM_COL_A) {
      const double* pb = &B[col];
      double tmp = 0.0;
      for (int k = 0; k < NUM_COL_A; ++k, pb += NUM_COL_B) {
        tmp += pa[k] * pb[0];
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
    const double* pa = &A[0];
    for (int row = 0; row < NUM_ROW_C; ++row, pa += NUM_COL_A) {
      const double* pb = &B[col];
      double tmp1 = 0.0, tmp2 = 0.0;
      for (int k = 0; k < NUM_COL_A; ++k, pb += NUM_COL_B) {
        double av = pa[k];
        tmp1 += av * pb[0];
        tmp2 += av * pb[1];
      }

      const int index = (row + start_row_c) * col_stride_c + start_col_c + col;
      CERES_GEMM_STORE_PAIR(C, index, tmp1, tmp2);
    }

    // Return directly for efficiency of extremely small matrix multiply.
    if (NUM_COL_C < span) {
      return;
    }
  }

  // Calculate the main part with multiples of 4.
  int col_m = NUM_COL_C & (~(span - 1));
  for (int col = 0; col < col_m; col += span) {
    for (int row = 0; row < NUM_ROW_C; ++row) {
      const int index = (row + start_row_c) * col_stride_c + start_col_c + col;
      // clang-format off
      MMM_mat1x4(NUM_COL_A, &A[row * NUM_COL_A],
                 &B[col], NUM_COL_B, &C[index], kOperation);
      // clang-format on
    }
  }
}
