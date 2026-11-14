// u0609 – ceres::internal::MVM_mat4x1
// Trích từ internal/ceres/small_blas_generic.h, dòng 211–245 (chỉ để xem, không compile)

static inline void MVM_mat4x1(const int col_a,
                              const double* a,
                              const int col_stride_a,
                              const double* b,
                              double* c,
                              const int kOperation) {
  CERES_GEMM_OPT_NAIVE_HEADER
  double bv = 0.0;

  // clang-format off
#define CERES_GEMM_OPT_MVM_MAT4X1_MUL       \
  bv = *pb;                                 \
  cvec4[0] += *(pa                   ) * bv; \
  cvec4[1] += *(pa + col_stride_a    ) * bv; \
  cvec4[2] += *(pa + col_stride_a * 2) * bv; \
  cvec4[3] += *(pa + col_stride_a * 3) * bv; \
  pa++;                                     \
  pb++;
  // clang-format on

  for (int k = 0; k < col_m; k += span) {
    CERES_GEMM_OPT_MVM_MAT4X1_MUL
    CERES_GEMM_OPT_MVM_MAT4X1_MUL
    CERES_GEMM_OPT_MVM_MAT4X1_MUL
    CERES_GEMM_OPT_MVM_MAT4X1_MUL
  }

  for (int k = col_m; k < col_a; k++) {
    CERES_GEMM_OPT_MVM_MAT4X1_MUL
  }

  CERES_GEMM_OPT_STORE_MAT1X4

#undef CERES_GEMM_OPT_MVM_MAT4X1_MUL
}
