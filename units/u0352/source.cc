// u0352 – ceres::internal::hash_mix
// Trích từ internal/ceres/pair_hash.h, dòng 61–71 (chỉ để xem, không compile)

inline void hash_mix(uint32_t& a, uint32_t& b, uint32_t& c) {
  a -= b; a -= c; a ^= (c>>13);
  b -= c; b -= a; b ^= (a<<8);
  c -= a; c -= b; c ^= (b>>13);
  a -= b; a -= c; a ^= (c>>12);
  b -= c; b -= a; b ^= (a<<16);
  c -= a; c -= b; c ^= (b>>5);
  a -= b; a -= c; a ^= (c>>3);
  b -= c; b -= a; b ^= (a<<10);
  c -= a; c -= b; c ^= (b>>15);
}
