// u1391 – ceres::internal::CreateLinearLeastSquaresProblemFromId
// Trích từ internal/ceres/linear_least_squares_problems.cc, dòng 49–70 (chỉ để xem, không compile)

std::unique_ptr<LinearLeastSquaresProblem>
CreateLinearLeastSquaresProblemFromId(int id) {
  switch (id) {
    case 0:
      return LinearLeastSquaresProblem0();
    case 1:
      return LinearLeastSquaresProblem1();
    case 2:
      return LinearLeastSquaresProblem2();
    case 3:
      return LinearLeastSquaresProblem3();
    case 4:
      return LinearLeastSquaresProblem4();
    case 5:
      return LinearLeastSquaresProblem5();
    case 6:
      return LinearLeastSquaresProblem6();
    default:
      LOG(FATAL) << "Unknown problem id requested " << id;
  }
  return nullptr;
}
