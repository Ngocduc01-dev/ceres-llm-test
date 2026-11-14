// u0607 – ceres::internal::MMM_mat1x4
// Trích từ internal/ceres/small_blas_generic.h, dòng 87–122 (chỉ để xem, không compile)

static inline void MMM_mat1x4(const int col_a,
                              const double* a,
                              const double* b,
                              const int col_stride_b,
                              double* c,
                              const int kOperation) {
  CERES_GEMM_OPT_NAIVE_HEADER
  double av = 0.0;
  int bi = 0;

#define CERES_GEMM_OPT_MMM_MAT1X4_MUL \
  av = pa[k];                         \
  pb = b + bi;                        \
  cvec4[0] += av * pb[0];             \
  cvec4[1] += av * pb[1];             \
  cvec4[2] += av * pb[2];             \
  cvec4[3] += av * pb[3];             \
  pb += 4;                            \
  bi += col_stride_b;                 \
  k++;

  for (int k = 0; k < col_m;) {
    CERES_GEMM_OPT_MMM_MAT1X4_MUL
    CERES_GEMM_OPT_MMM_MAT1X4_MUL
    CERES_GEMM_OPT_MMM_MAT1X4_MUL
    CERES_GEMM_OPT_MMM_MAT1X4_MUL
  }

  for (int k = col_m; k < col_a;) {
    CERES_GEMM_OPT_MMM_MAT1X4_MUL
  }

  CERES_GEMM_OPT_STORE_MAT1X4

#undef CERES_GEMM_OPT_MMM_MAT1X4_MUL
}
