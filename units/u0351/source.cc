// u0351 – ceres::ContainsKey
// Trích từ internal/ceres/map_util.h, dòng 112–116 (chỉ để xem, không compile)

template <class Collection, class Key>
bool ContainsKey(const Collection& collection, const Key& key) {
  typename Collection::const_iterator it = collection.find(key);
  return it != collection.end();
}
