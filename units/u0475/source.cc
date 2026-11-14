// u0475 – ceres::FindOrNull
// Trích từ internal/ceres/map_util.h, dòng 99–108 (chỉ để xem, không compile)

template <class Collection>
typename Collection::value_type::second_type* FindOrNull(
    Collection& collection,  // NOLINT
    const typename Collection::value_type::first_type& key) {
  typename Collection::iterator it = collection.find(key);
  if (it == collection.end()) {
    return 0;
  }
  return &it->second;
}
