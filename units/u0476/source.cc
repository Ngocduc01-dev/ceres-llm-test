// u0476 – ceres::InsertOrDie
// Trích từ internal/ceres/map_util.h, dòng 120–127 (chỉ để xem, không compile)

template <class Collection>
void InsertOrDie(Collection* const collection,
                 const typename Collection::value_type::first_type& key,
                 const typename Collection::value_type::second_type& data) {
  using value_type = typename Collection::value_type;
  CHECK(collection->insert(value_type(key, data)).second)
      << "duplicate key: " << key;
}
