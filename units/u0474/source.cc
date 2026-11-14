// u0474 – ceres::FindWithDefault
// Trích từ internal/ceres/map_util.h, dòng 70–80 (chỉ để xem, không compile)

template <class Collection>
const typename Collection::value_type::second_type FindWithDefault(
    const Collection& collection,
    const typename Collection::value_type::first_type& key,
    const typename Collection::value_type::second_type& value) {
  typename Collection::const_iterator it = collection.find(key);
  if (it == collection.end()) {
    return value;
  }
  return it->second;
}
