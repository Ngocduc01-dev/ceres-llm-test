// u1012 – ceres::internal::Hash64NumWithSeed
// Trích từ internal/ceres/pair_hash.h, dòng 94–99 (chỉ để xem, không compile)

inline uint64_t Hash64NumWithSeed(uint64_t num, uint64_t c) {
  // More of the golden ratio.
  uint64_t b = GG_ULONGLONG(0xe08c1d668b756f82);
  hash_mix(num, b, c);
  return c;
}
