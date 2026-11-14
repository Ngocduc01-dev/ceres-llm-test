// u0353 – ceres::internal::hash_mix
// Trích từ internal/ceres/pair_hash.h, dòng 74–84 (chỉ để xem, không compile)

inline void hash_mix(uint64_t& a, uint64_t& b, uint64_t& c) {
  a -= b; a -= c; a ^= (c>>43);
  b -= c; b -= a; b ^= (a<<9);
  c -= a; c -= b; c ^= (b>>8);
  a -= b; a -= c; a ^= (c>>38);
  b -= c; b -= a; b ^= (a<<23);
  c -= a; c -= b; c ^= (b>>5);
  a -= b; a -= c; a ^= (c>>35);
  b -= c; b -= a; b ^= (a<<49);
  c -= a; c -= b; c ^= (b>>11);
}
