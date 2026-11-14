// u1258 – ceres::internal::pair_hash::operator()
// Trích từ internal/ceres/pair_hash.h, dòng 104–111 (chỉ để xem, không compile)

  template <typename T>
  std::size_t operator()(const std::pair<T, T>& p) const {
    const std::size_t h1 = std::hash<T>()(p.first);
    const std::size_t h2 = std::hash<T>()(p.second);
    // The decision below is at compile time
    return (sizeof(h1) <= sizeof(uint32_t)) ? Hash32NumWithSeed(h1, h2)
                                            : Hash64NumWithSeed(h1, h2);
  }
