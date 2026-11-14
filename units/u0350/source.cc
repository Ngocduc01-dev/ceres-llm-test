// u0350 – ceres::InsertIfNotPresent
// Trích từ internal/ceres/map_util.h, dòng 86–94 (chỉ để xem, không compile)

template <class Collection>
bool InsertIfNotPresent(
    Collection* const collection,
    const typename Collection::value_type::first_type& key,
    const typename Collection::value_type::second_type& value) {
  std::pair<typename Collection::iterator, bool> ret =
      collection->insert(typename Collection::value_type(key, value));
  return ret.second;
}
