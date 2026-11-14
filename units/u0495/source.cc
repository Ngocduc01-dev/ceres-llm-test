// u0495 – ceres::internal::Take0thOrderPart
// Trích từ include/ceres/internal/autodiff.h, dòng 239–245 (chỉ để xem, không compile)

template <typename JetT, typename T>
inline void Take0thOrderPart(int M, const JetT* src, T dst) {
  DCHECK(src);
  for (int i = 0; i < M; ++i) {
    dst[i] = src[i].a;
  }
}
