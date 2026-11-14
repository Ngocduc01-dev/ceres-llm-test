// u0599 – ceres::internal::(anonymous)::DecrementValueOrDeleteKey
// Trích từ internal/ceres/problem_impl.cc, dòng 87–97 (chỉ để xem, không compile)

template <typename KeyType>
void DecrementValueOrDeleteKey(const KeyType key,
                               std::map<KeyType, int>* container) {
  auto it = container->find(key);
  if (it->second == 1) {
    delete key;
    container->erase(it);
  } else {
    --it->second;
  }
}
