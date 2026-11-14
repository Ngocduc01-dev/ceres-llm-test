// u0741 – ceres::internal::Make1stOrderPerturbation::Apply
// Trích từ include/ceres/internal/autodiff.h, dòng 186–193 (chỉ để xem, không compile)

  inline static void Apply(const T* src, JetT* dst) {
    if (j == 0) {
      DCHECK(src);
      DCHECK(dst);
    }
    dst[j] = JetT(src[j], j + Offset);
    Make1stOrderPerturbation<j + 1, N, Offset, T, JetT>::Apply(src, dst);
  }
