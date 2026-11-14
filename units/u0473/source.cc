// u0473 – ceres::FindOrDie
// Trích từ internal/ceres/map_util.h, dòng 58–65 (chỉ để xem, không compile)

template <class Collection>
const typename Collection::value_type::second_type& FindOrDie(
    const Collection& collection,
    const typename Collection::value_type::first_type& key) {
  typename Collection::const_iterator it = collection.find(key);
  CHECK(it != collection.end()) << "Map key not found: " << key;
  return it->second;
}
