# 1. NHIỆM VỤ

Bạn là kỹ sư kiểm thử phần mềm. Hãy thiết kế bộ test cho **một hàm C++** (gọi là **unit**) ở mục 3 theo phương pháp **kiểm thử luồng điều khiển (CFT)**, sao cho đạt **độ phủ nhánh C2**, rồi viết bộ test đó thành **một file GoogleTest** (thư viện viết unit test cho C++) chạy được.

- Dự án: thư viện **Ceres Solver 2.2.0**, viết bằng C++17.
- Dự án **không có tài liệu mô tả kết quả đúng**, nên **không cần kiểm tra kết quả trả về**. Mục tiêu chỉ là gọi hàm sao cho chương trình **đi qua đủ các nhánh**.

---

# 2. KHÁI NIỆM CẦN DÙNG

- **CFG (đồ thị luồng điều khiển):** sơ đồ các bước của hàm. Mỗi **node** là một đoạn lệnh chạy liền nhau hoặc một chỗ rẽ nhánh; mũi tên nối các node theo thứ tự chạy.
- **Điểm rẽ nhánh:** chỗ chương trình chọn đường đi theo một điều kiện: `if`, `else if`, vòng `for` / `while`, `switch`, `?:`. Mỗi điểm rẽ nhánh có **2 nhánh**: điều kiện **đúng** và điều kiện **sai** (`switch` có 1 nhánh cho mỗi `case`).
- **Độ phủ C2 (phủ nhánh):** mọi nhánh của mọi điểm rẽ nhánh đều được chạy qua ít nhất 1 lần.
  **C2 = số nhánh đã chạy qua / tổng số nhánh × 100%.**
  (C2 chặt hơn C1 – chỉ yêu cầu mỗi câu lệnh chạy ít nhất 1 lần. Ví dụ `if (x > 0) y = 1;`: chỉ cần x > 0 là đạt C1, nhưng C2 cần thêm 1 test với x ≤ 0.)
  Điều kiện ghép như `a && b`, `a || b` được tính là **một** điểm rẽ nhánh.
- **Test path (đường kiểm thử):** một đường đi trên CFG, từ `START` tới `END`, ghi rõ ở mỗi điểm rẽ nhánh đi theo nhánh nào.
- **Điều kiện của đường đi:** các điều kiện phải đúng/sai dọc theo một test path. Dữ liệu đầu vào của test phải thoả các điều kiện này.
- **Nhánh không thể đi tới:** nhánh mà không có dữ liệu nào làm chương trình đi vào (ví dụ điều kiện mâu thuẫn). Ghi rõ lý do, vẫn tính vào tổng số nhánh.
- **Vòng lặp:**
  - Có giới hạn số lần lặp n (ví dụ `for (i = 0; i < size; ...)`): test với **0, 1, 2, một số ở giữa, n−1, n** lần lặp; thêm **n+1** nếu làm được.
  - Không có giới hạn (lặp đến khi thoả một điều kiện, ví dụ `while (!done)`): test với **0, 1, 2** lần lặp và **mỗi cách thoát khỏi vòng lặp** (`break`, `return`, điều kiện sai) ít nhất 1 lần.
  - Số lần lặp nào không làm được thì ghi lý do.
- **`CHECK(...)`:** lệnh kiểm tra của thư viện glog mà Ceres dùng. Nếu điều kiện sai, chương trình **dừng ngay**. **Không** cố tình làm `CHECK` sai; ghi nhánh đó là "không test (làm chương trình dừng)".

---

# 3. ĐẦU VÀO

## 3.1. Unit cần test

- Hàm: `ComputeCovarianceValuesUsingDenseSVD()`, trả về `bool`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::CovarianceImpl`
- Vị trí: `internal/ceres/covariance_impl.cc`, dòng 704–793

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
704 | bool CovarianceImpl::ComputeCovarianceValuesUsingDenseSVD() {
705 |   EventLogger event_logger(
706 |       "CovarianceImpl::ComputeCovarianceValuesUsingDenseSVD");
707 |   if (covariance_matrix_ == nullptr) {
708 |     // Nothing to do, all zeros covariance matrix.
709 |     return true;
710 |   }
711 | 
712 |   CRSMatrix jacobian;
713 |   problem_->Evaluate(evaluate_options_, nullptr, nullptr, nullptr, &jacobian);
714 |   event_logger.AddEvent("Evaluate");
715 | 
716 |   Matrix dense_jacobian(jacobian.num_rows, jacobian.num_cols);
717 |   dense_jacobian.setZero();
718 |   for (int r = 0; r < jacobian.num_rows; ++r) {
719 |     for (int idx = jacobian.rows[r]; idx < jacobian.rows[r + 1]; ++idx) {
720 |       const int c = jacobian.cols[idx];
721 |       dense_jacobian(r, c) = jacobian.values[idx];
722 |     }
723 |   }
724 |   event_logger.AddEvent("ConvertToDenseMatrix");
725 | 
726 |   Eigen::BDCSVD<Matrix> svd(dense_jacobian,
727 |                             Eigen::ComputeThinU | Eigen::ComputeThinV);
728 | 
729 |   event_logger.AddEvent("SingularValueDecomposition");
730 | 
731 |   const Vector singular_values = svd.singularValues();
732 |   const int num_singular_values = singular_values.rows();
733 |   Vector inverse_squared_singular_values(num_singular_values);
734 |   inverse_squared_singular_values.setZero();
735 | 
736 |   const double max_singular_value = singular_values[0];
737 |   const double min_singular_value_ratio =
738 |       sqrt(options_.min_reciprocal_condition_number);
739 | 
740 |   const bool automatic_truncation = (options_.null_space_rank < 0);
741 |   const int max_rank = std::min(num_singular_values,
742 |                                 num_singular_values - options_.null_space_rank);
743 | 
744 |   // Compute the squared inverse of the singular values. Truncate the
745 |   // computation based on min_singular_value_ratio and
746 |   // null_space_rank. When either of these two quantities are active,
747 |   // the resulting covariance matrix is a Moore-Penrose inverse
748 |   // instead of a regular inverse.
749 |   for (int i = 0; i < max_rank; ++i) {
750 |     const double singular_value_ratio = singular_values[i] / max_singular_value;
751 |     if (singular_value_ratio < min_singular_value_ratio) {
752 |       // Since the singular values are in decreasing order, if
753 |       // automatic truncation is enabled, then from this point on
754 |       // all values will fail the ratio test and there is nothing to
755 |       // do in this loop.
756 |       if (automatic_truncation) {
757 |         break;
758 |       } else {
759 |         LOG(ERROR) << "Error: Covariance matrix is near rank deficient "
760 |                    << "and the user did not specify a non-zero"
761 |                    << "Covariance::Options::null_space_rank "
762 |                    << "to enable the computation of a Pseudo-Inverse. "
763 |                    << "Reciprocal condition number: "
764 |                    << singular_value_ratio * singular_value_ratio << " "
765 |                    << "min_reciprocal_condition_number: "
766 |                    << options_.min_reciprocal_condition_number;
767 |         return false;
768 |       }
769 |     }
770 | 
771 |     inverse_squared_singular_values[i] =
772 |         1.0 / (singular_values[i] * singular_values[i]);
773 |   }
774 | 
775 |   Matrix dense_covariance = svd.matrixV() *
776 |                             inverse_squared_singular_values.asDiagonal() *
777 |                             svd.matrixV().transpose();
778 |   event_logger.AddEvent("PseudoInverse");
779 | 
780 |   const int num_rows = covariance_matrix_->num_rows();
781 |   const int* rows = covariance_matrix_->rows();
782 |   const int* cols = covariance_matrix_->cols();
783 |   double* values = covariance_matrix_->mutable_values();
784 | 
785 |   for (int r = 0; r < num_rows; ++r) {
786 |     for (int idx = rows[r]; idx < rows[r + 1]; ++idx) {
787 |       const int c = cols[idx];
788 |       values[idx] = dense_covariance(r, c);
789 |     }
790 |   }
791 |   event_logger.AddEvent("CopyToCovarianceMatrix");
792 |   return true;
793 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 8

START → 1
1   "CovarianceImpl::ComputeCovarianceValuesUsingDenseSVD"         → 2
2   if (covariance_matrix_ == nullptr)                             đúng → 3   sai → 4
3   return true                                                    → END
4   problem_->Evaluate(evaluate_options_, nullptr, nullptr, nullptr, &jacobian)
    event_logger.AddEvent("Evaluate")
    jacobian.num_rows, jacobian.num_cols
    dense_jacobian.setZero()
    int r = 0                                                      → 5
5   vòng for, điều kiện: r < jacobian.num_rows                     đúng → 6   sai → 11
6   int idx = jacobian.rows[r]                                     → 7
7   vòng for, điều kiện: idx < jacobian.rows[r + 1]                đúng → 8   sai → 10
8   const int c = jacobian.cols[idx]
    dense_jacobian(r, c) = jacobian.values[idx]                    → 9
9   ++idx                                                          → 7
10  ++r                                                            → 5
11  event_logger.AddEvent("ConvertToDenseMatrix")
    dense_jacobian, Eigen::ComputeThinU | Eigen::ComputeThinV
    event_logger.AddEvent("SingularValueDecomposition")
    svd.singularValues()
    const int num_singular_values = singular_values.rows()
    inverse_squared_singular_values.setZero()
    const double max_singular_value = singular_values[0]
    const double min_singular_value_ratio = sqrt(options_.min_reciprocal_condition_number)
    const bool automatic_truncation = (options_.null_space_rank < 0)
    const int max_rank = std::min(num_singular_values, num_singular_values - options_.null_space_rank)
    int i = 0                                                      → 12
12  vòng for, điều kiện: i < max_rank                              đúng → 13   sai → 17
13  const double singular_value_ratio = singular_values[i] / max_singular_value   → 14
14  if (singular_value_ratio < min_singular_value_ratio)           đúng → 15   sai → 25
15  if (automatic_truncation)                                      đúng → 16   sai → END
16  break                                                          → 17
17  svd.matrixV() * inverse_squared_singular_values.asDiagonal() * svd.matrixV().transpose()
    event_logger.AddEvent("PseudoInverse")
    const int num_rows = covariance_matrix_->num_rows()
    const int *rows = covariance_matrix_->rows()
    const int *cols = covariance_matrix_->cols()
    double *values = covariance_matrix_->mutable_values()
    int r = 0                                                      → 18
18  vòng for, điều kiện: r < num_rows                              đúng → 19   sai → 24
19  int idx = rows[r]                                              → 20
20  vòng for, điều kiện: idx < rows[r + 1]                         đúng → 21   sai → 23
21  const int c = cols[idx]
    values[idx] = dense_covariance(r, c)                           → 22
22  ++idx                                                          → 20
23  ++r                                                            → 18
24  event_logger.AddEvent("CopyToCovarianceMatrix")
    return true                                                    → END
25  inverse_squared_singular_values[i] = 1. / (singular_values[i] * singular_values[i])   → 26
26  ++i                                                            → 12
```

**Cách đọc:** dòng đầu cho biết hàm có bao nhiêu điểm rẽ nhánh. Mỗi dòng sau đó là **một node**: số node, nội dung (câu lệnh hoặc điều kiện), rồi mũi tên tới node tiếp theo. Dòng "Ghi chú" (nếu có) cho biết unit là template và CFG được dựng với kiểu dữ liệu cụ thể nào.
- Node có điều kiện ghi `đúng → x   sai → y`: điều kiện đúng thì đi tới node x, sai thì đi tới node y.
- `START`: bắt đầu hàm · `END`: kết thúc hàm · `DỪNG`: chương trình dừng do `CHECK` sai.
- Nếu thấy CFG không khớp với mã nguồn, **tin mã nguồn** và ghi chú lại.
- Khi trả lời, gọi các node bằng **đúng số node này**.

## 3.3. Cách gọi unit trong file test

Các dòng `#include` được dùng:
```cpp
#include "gtest/gtest.h"
#include "ceres/crs_matrix.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/covariance_impl.h"
#include "ceres/wall_time.h"
```

- Đây là method của class `ceres::internal::CovarianceImpl`: tạo một object của class rồi gọi method trên object đó.

---

# 4. YÊU CẦU ĐỐI VỚI BỘ TEST

1. Mỗi nhánh (đúng và sai) của mỗi điểm rẽ nhánh có **ít nhất 1 test** đi qua.
2. Mỗi vòng lặp được test với số lần lặp như mục 2.
3. Mỗi test ứng với **một test path**, ghi rõ các nhánh nó đi qua (ví dụ `node 2: đúng, node 4: sai`).
4. Dùng **ít test nhất** có thể: một test nên đi qua nhiều nhánh chưa được phủ.
5. **Dữ liệu đầu vào:** từ điều kiện của đường đi, xác định **khoảng giá trị** hợp lệ cho từng đầu vào (ví dụ `n` từ 1 đến 5), rồi **chọn ngẫu nhiên một giá trị** trong khoảng đó. Nếu dùng hàm sinh số ngẫu nhiên trong code thì **cố định giá trị khởi tạo (seed)** để mỗi lần chạy ra cùng một giá trị. Mảng, ma trận nhỏ (tối đa 5 phần tử). Không dùng file, mạng, đa luồng.
6. **Không** kiểm tra kết quả trả về (không có kết quả đúng để so).

---

# 5. CÁC BƯỚC THỰC HIỆN

1. Đọc mã nguồn và CFG của unit.
2. Liệt kê các điểm rẽ nhánh và các nhánh cần phủ.
3. Chọn các test path sao cho phủ hết các nhánh (trừ nhánh không thể đi tới và nhánh `CHECK` sai).
4. Với mỗi test path: viết điều kiện của đường đi → khoảng giá trị đầu vào → chọn giá trị ngẫu nhiên trong khoảng.
5. Viết code GoogleTest: mỗi test chuẩn bị dữ liệu rồi gọi unit **một lần**.
6. Kiểm tra lại: mọi nhánh đã có test chưa, code có dùng đúng tên hàm và `#include` ở mục 3.3 không.

---

# 6. KẾT QUẢ CẦN TRẢ VỀ

**A. Test paths**

| Path | Đường đi (theo số node) | Các nhánh đi qua |
|---|---|---|
| P1 | START → 1 → 2 → … → END | node 1: đúng, node 2: sai |

**B. Bộ test case**

| Test | Path | Khoảng giá trị đầu vào | Giá trị đã chọn |
|---|---|---|---|
| TC1 | P1 | … | … |

**C. Nhánh không test** (nếu có): nhánh nào, vì sao. Kèm 1 dòng: `C2 dự kiến = <số nhánh có test> / <tổng số nhánh>` (dự kiến, chưa chạy thật).

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1503_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
