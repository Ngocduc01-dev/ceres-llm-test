// u1098 – ceres::StringToCovarianceAlgorithmType
// Trích từ internal/ceres/types.cc, dòng 299–305 (chỉ để xem, không compile)

bool StringToCovarianceAlgorithmType(std::string value,
                                     CovarianceAlgorithmType* type) {
  UpperCase(&value);
  STRENUM(DENSE_SVD);
  STRENUM(SPARSE_QR);
  return false;
}
