// u0516 – ceres::internal::Take1stOrderPart
// Trích từ include/ceres/internal/autodiff.h, dòng 249–257 (chỉ để xem, không compile)

template <int N0, int N, typename JetT, typename T>
inline void Take1stOrderPart(const int M, const JetT* src, T* dst) {
  DCHECK(src);
  DCHECK(dst);
  for (int i = 0; i < M; ++i) {
    Eigen::Map<Eigen::Matrix<T, N, 1>>(dst + N * i, N) =
        src[i].v.template segment<N>(N0);
  }
}
