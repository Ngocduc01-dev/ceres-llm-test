// u1011 – ceres::internal::Hash32NumWithSeed
// Trích từ internal/ceres/pair_hash.h, dòng 87–92 (chỉ để xem, không compile)

inline uint32_t Hash32NumWithSeed(uint32_t num, uint32_t c) {
  // The golden ratio; an arbitrary value.
  uint32_t b = 0x9e3779b9UL;
  hash_mix(num, b, c);
  return c;
}
