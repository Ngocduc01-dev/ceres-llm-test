// u0529 – ceres::internal::LinearIndexToUpperTriangularIndex
// Trích từ internal/ceres/parallel_utils.cc, dòng 35–86 (chỉ để xem, không compile)

void LinearIndexToUpperTriangularIndex(int k, int n, int* i, int* j) {
  // This works by unfolding a rectangle into a triangle.
  // Say n is even. 4 is a nice even number. The 10 i,j pairs that we
  // want to produce are:
  // 0,0 0,1 0,2 0,3
  //     1,1 1,2 1,3
  //         2,2 2,3
  //             3,3
  // This triangle can be folded into a 5x2 rectangle:
  // 3,3 0,0 0,1 0,2 0,3
  // 2,2 2,3 1,1 1,2 1,3

  // If N is odd, say 5, then the 15 i,j pairs are:
  // 0,0 0,1 0,2 0,3 0,4
  //     1,1 1,2 1,3 1,4
  //         2,2 2,3 2,3
  //             3,3 3,4
  //                 4,4
  // which folds to a 5x3 rectangle:
  // 0,0 0,1 0,2 0,3 0,4
  // 4,4 1,1 1,2 1,3 1,4
  // 3,3 3,4 2,2 2,3 2,4

  // All this function does is map the linear iteration position to a
  // location in the rectangle and work out the appropriate (i, j) for that
  // location.
  if (n & 1) {
    // Odd n. The tip of the triangle is on row 1.
    int w = n;  // Width of the rectangle to unfold
    int i0 = k / w;
    int j0 = k % w;
    if (j0 >= i0) {
      *i = i0;
      *j = j0;
    } else {
      *i = n - i0;
      *j = *i + j0;
    }
  } else {
    // Even n. The tip of the triangle is on row 0, making it one wider.
    int w = n + 1;
    int i0 = k / w;
    int j0 = k % w;
    if (j0 > i0) {
      *i = i0;
      *j = j0 - 1;
    } else {
      *i = n - 1 - i0;
      *j = *i + j0;
    }
  }
}
