// u0608 – ceres::internal::MTM_mat1x4
// Trích từ internal/ceres/small_blas_generic.h, dòng 153–190 (chỉ để xem, không compile)

static inline void MTM_mat1x4(const int col_a,
                              const double* a,
                              const int col_stride_a,
                              const double* b,
                              const int col_stride_b,
                              double* c,
                              const int kOperation) {
  CERES_GEMM_OPT_NAIVE_HEADER
  double av = 0.0;
  int ai = 0;
  int bi = 0;

#define CERES_GEMM_OPT_MTM_MAT1X4_MUL \
  av = pa[ai];                        \
  pb = b + bi;                        \
  cvec4[0] += av * pb[0];             \
  cvec4[1] += av * pb[1];             \
  cvec4[2] += av * pb[2];             \
  cvec4[3] += av * pb[3];             \
  pb += 4;                            \
  ai += col_stride_a;                 \
  bi += col_stride_b;

  for (int k = 0; k < col_m; k += span) {
    CERES_GEMM_OPT_MTM_MAT1X4_MUL
    CERES_GEMM_OPT_MTM_MAT1X4_MUL
    CERES_GEMM_OPT_MTM_MAT1X4_MUL
    CERES_GEMM_OPT_MTM_MAT1X4_MUL
  }

  for (int k = col_m; k < col_a; k++) {
    CERES_GEMM_OPT_MTM_MAT1X4_MUL
  }

  CERES_GEMM_OPT_STORE_MAT1X4

#undef CERES_GEMM_OPT_MTM_MAT1X4_MUL
}
