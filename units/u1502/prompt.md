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

- Hàm: `ComputeCovarianceValuesUsingEigenSparseQR()`, trả về `bool`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::CovarianceImpl`
- Vị trí: `internal/ceres/covariance_impl.cc`, dòng 795–887

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
795 | bool CovarianceImpl::ComputeCovarianceValuesUsingEigenSparseQR() {
796 |   EventLogger event_logger(
797 |       "CovarianceImpl::ComputeCovarianceValuesUsingEigenSparseQR");
798 |   if (covariance_matrix_ == nullptr) {
799 |     // Nothing to do, all zeros covariance matrix.
800 |     return true;
801 |   }
802 | 
803 |   CRSMatrix jacobian;
804 |   problem_->Evaluate(evaluate_options_, nullptr, nullptr, nullptr, &jacobian);
805 |   event_logger.AddEvent("Evaluate");
806 | 
807 |   using EigenSparseMatrix = Eigen::SparseMatrix<double, Eigen::ColMajor>;
808 | 
809 |   // Convert the matrix to column major order as required by SparseQR.
810 |   EigenSparseMatrix sparse_jacobian =
811 |       Eigen::Map<Eigen::SparseMatrix<double, Eigen::RowMajor>>(
812 |           jacobian.num_rows,
813 |           jacobian.num_cols,
814 |           static_cast<int>(jacobian.values.size()),
815 |           jacobian.rows.data(),
816 |           jacobian.cols.data(),
817 |           jacobian.values.data());
818 |   event_logger.AddEvent("ConvertToSparseMatrix");
819 | 
820 |   Eigen::SparseQR<EigenSparseMatrix, Eigen::COLAMDOrdering<int>> qr;
821 |   if (options_.column_pivot_threshold > 0) {
822 |     qr.setPivotThreshold(options_.column_pivot_threshold);
823 |   }
824 | 
825 |   qr.compute(sparse_jacobian);
826 |   event_logger.AddEvent("QRDecomposition");
827 | 
828 |   if (qr.info() != Eigen::Success) {
829 |     LOG(ERROR) << "Eigen::SparseQR decomposition failed.";
830 |     return false;
831 |   }
832 | 
833 |   if (qr.rank() < jacobian.num_cols) {
834 |     LOG(ERROR) << "Jacobian matrix is rank deficient. "
835 |                << "Number of columns: " << jacobian.num_cols
836 |                << " rank: " << qr.rank();
837 |     return false;
838 |   }
839 | 
840 |   const int* rows = covariance_matrix_->rows();
841 |   const int* cols = covariance_matrix_->cols();
842 |   double* values = covariance_matrix_->mutable_values();
843 | 
844 |   // Compute the inverse column permutation used by QR factorization.
845 |   Eigen::PermutationMatrix<Eigen::Dynamic, Eigen::Dynamic> inverse_permutation =
846 |       qr.colsPermutation().inverse();
847 | 
848 |   // The following loop exploits the fact that the i^th column of A^{-1}
849 |   // is given by the solution to the linear system
850 |   //
851 |   //  A x = e_i
852 |   //
853 |   // where e_i is a vector with e(i) = 1 and all other entries zero.
854 |   //
855 |   // Since the covariance matrix is symmetric, the i^th row and column
856 |   // are equal.
857 |   const int num_cols = jacobian.num_cols;
858 |   const int num_threads = options_.num_threads;
859 |   auto workspace = std::make_unique<double[]>(num_threads * num_cols);
860 | 
861 |   problem_->context()->EnsureMinimumThreads(num_threads);
862 |   ParallelFor(
863 |       problem_->context(), 0, num_cols, num_threads, [&](int thread_id, int r) {
864 |         const int row_begin = rows[r];
865 |         const int row_end = rows[r + 1];
866 |         if (row_end != row_begin) {
867 |           double* solution = workspace.get() + thread_id * num_cols;
868 |           SolveRTRWithSparseRHS<int>(num_cols,
869 |                                      qr.matrixR().innerIndexPtr(),
870 |                                      qr.matrixR().outerIndexPtr(),
871 |                                      &qr.matrixR().data().value(0),
872 |                                      inverse_permutation.indices().coeff(r),
873 |                                      solution);
874 | 
875 |           // Assign the values of the computed covariance using the
876 |           // inverse permutation used in the QR factorization.
877 |           for (int idx = row_begin; idx < row_end; ++idx) {
878 |             const int c = cols[idx];
879 |             values[idx] = solution[inverse_permutation.indices().coeff(c)];
880 |           }
881 |         }
882 |       });
883 | 
884 |   event_logger.AddEvent("Inverse");
885 | 
886 |   return true;
887 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 4

START → 1
1   "CovarianceImpl::ComputeCovarianceValuesUsingEigenSparseQR"    → 2
2   if (covariance_matrix_ == nullptr)                             đúng → 3   sai → 4
3   return true                                                    → END
4   problem_->Evaluate(evaluate_options_, nullptr, nullptr, nullptr, &jacobian)
    event_logger.AddEvent("Evaluate")
    Eigen::Map<Eigen::SparseMatrix<double, Eigen::RowMajor>>(jacobian.num_rows, jacobian.num_cols, static_cast<int>(jacobian.values.size()), jacobian.rows.data(), jacobian.cols.data(), jacobian.values.data())
    event_logger.AddEvent("ConvertToSparseMatrix")                 → 5
5   if (options_.column_pivot_threshold > 0)                       đúng → 6   sai → 7
6   qr.setPivotThreshold(options_.column_pivot_threshold)          → 7
7   qr.compute(sparse_jacobian)
    event_logger.AddEvent("QRDecomposition")                       → 8
8   if (qr.info() != Eigen::Success)                               đúng → END   sai → 9
9   if (qr.rank() < jacobian.num_cols)                             đúng → END   sai → 10
10  const int *rows = covariance_matrix_->rows()
    const int *cols = covariance_matrix_->cols()
    double *values = covariance_matrix_->mutable_values()
    qr.colsPermutation().inverse()
    const int num_cols = jacobian.num_cols
    const int num_threads = options_.num_threads
    problem_->context()->EnsureMinimumThreads(num_threads)
    ParallelFor (ImplicitCastExpr, FunctionToPointerDecay, void (*)(ContextImpl *, int, int, int, class (lambda at /work/ceres-solver/internal/ceres/covariance_impl.cc:863:54) &&, int))(problem_->context(), 0, num_cols, num_threads, [&](int thread_id, int r) {)
    event_logger.AddEvent("Inverse")
    return true                                                    → END
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
#include "ceres/compressed_col_sparse_matrix_utils.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/covariance_impl.h"
#include "ceres/parallel_for.h"
#include "ceres/problem_impl.h"
#include "ceres/wall_time.h"
```

- Đây là method của class `ceres::internal::CovarianceImpl`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `CovarianceImpl`:
Các constructor:
```cpp
  CovarianceImpl(const Covariance::Options & options)
```

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1502_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
