# 1. NHIỆM VỤ

Bạn là kỹ sư kiểm thử phần mềm. Hãy thiết kế bộ test cho **một hàm C++** (gọi là **unit**) ở mục 3 theo phương pháp **kiểm thử luồng điều khiển (CFT)**, sao cho đạt **độ phủ nhánh C2**, rồi viết bộ test đó thành **một file GoogleTest** (thư viện viết unit test cho C++) chạy được.

- Dự án: thư viện **Ceres Solver 2.2.0**, viết bằng C++17.
- Dự án **không có tài liệu mô tả kết quả đúng**, nên **không cần kiểm tra kết quả trả về**. Mục tiêu chỉ là gọi hàm sao cho chương trình **đi qua đủ các nhánh**.

---

# 2. KHÁI NIỆM

- **CFG (đồ thị luồng điều khiển):** sơ đồ các bước của hàm. Mỗi **node** là một đoạn lệnh chạy liền nhau hoặc một chỗ rẽ nhánh; mũi tên nối các node theo thứ tự chạy.
- **Điểm rẽ nhánh:** chỗ chương trình chọn đường đi theo một điều kiện: `if`, `else if`, vòng `for` / `while`, `switch`, `?:`. Mỗi điểm rẽ nhánh có **2 nhánh**: điều kiện **đúng** và điều kiện **sai** (`switch` có 1 nhánh cho mỗi `case`).
- **Độ phủ C2 (phủ nhánh):** mọi nhánh của mọi điểm rẽ nhánh đều được chạy qua ít nhất 1 lần.
  **C2 = số nhánh đã chạy qua / tổng số nhánh × 100%.**
  (C2 chặt hơn C1 – chỉ yêu cầu mỗi câu lệnh chạy ít nhất 1 lần. Ví dụ `if (x > 0) y = 1;`: chỉ cần x > 0 là đạt C1, nhưng C2 cần thêm 1 test với x ≤ 0.)
  Điều kiện ghép như `a && b`, `a || b` được tính là **một** điểm rẽ nhánh.
- **Test path (đường kiểm thử):** một đường đi trên CFG, từ `START` tới `END`, ghi rõ ở mỗi điểm rẽ nhánh đi theo nhánh nào.
- **Điều kiện của đường đi:** các điều kiện phải đúng/sai dọc theo một test path. Dữ liệu đầu vào của test phải thoả các điều kiện này.
- **Nhánh không thể đi tới:** nhánh mà không có dữ liệu nào làm chương trình đi vào (ví dụ điều kiện mâu thuẫn). Ghi rõ lý do, vẫn tính vào tổng số nhánh.
- **Tổng số nhánh** (mẫu số của C2) = 2 × số điểm rẽ nhánh ghi ở dòng đầu CFG (`switch`: mỗi `case` là 1 nhánh). **Không** tính nhánh của `CHECK`.
- **Vòng lặp:**
  - Có giới hạn số lần lặp n (ví dụ `for (i = 0; i < size; ...)`): test với **0, 1, 2, một số ở giữa, n−1, n** lần lặp; thêm **n+1** nếu làm được.
  - Không có giới hạn (lặp đến khi thoả một điều kiện, ví dụ `while (!done)`): test với **0, 1, 2** lần lặp và **mỗi cách thoát khỏi vòng lặp** (`break`, `return`, điều kiện sai) ít nhất 1 lần.
  - Số lần lặp nào không làm được thì ghi lý do.
- **`CHECK(...)`:** lệnh kiểm tra của thư viện glog mà Ceres dùng. Nếu điều kiện sai, chương trình **dừng ngay**. **Không** cố tình làm `CHECK` sai; ghi nhánh đó là "không test (làm chương trình dừng)".

---

# 3. ĐẦU VÀO

## 3.1. Unit cần test

- Hàm: `ComputeCovarianceValuesUsingSuiteSparseQR()`, trả về `bool`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::CovarianceImpl`
- Vị trí: `internal/ceres/covariance_impl.cc`, dòng 535–702

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
535 | bool CovarianceImpl::ComputeCovarianceValuesUsingSuiteSparseQR() {
536 |   EventLogger event_logger(
537 |       "CovarianceImpl::ComputeCovarianceValuesUsingSparseQR");
538 | 
539 | #ifndef CERES_NO_SUITESPARSE
540 |   if (covariance_matrix_ == nullptr) {
541 |     // Nothing to do, all zeros covariance matrix.
542 |     return true;
543 |   }
544 | 
545 |   CRSMatrix jacobian;
546 |   problem_->Evaluate(evaluate_options_, nullptr, nullptr, nullptr, &jacobian);
547 |   event_logger.AddEvent("Evaluate");
548 | 
549 |   // Construct a compressed column form of the Jacobian.
550 |   const int num_rows = jacobian.num_rows;
551 |   const int num_cols = jacobian.num_cols;
552 |   const int num_nonzeros = jacobian.values.size();
553 | 
554 |   std::vector<SuiteSparse_long> transpose_rows(num_cols + 1, 0);
555 |   std::vector<SuiteSparse_long> transpose_cols(num_nonzeros, 0);
556 |   std::vector<double> transpose_values(num_nonzeros, 0);
557 | 
558 |   for (int idx = 0; idx < num_nonzeros; ++idx) {
559 |     transpose_rows[jacobian.cols[idx] + 1] += 1;
560 |   }
561 | 
562 |   for (int i = 1; i < transpose_rows.size(); ++i) {
563 |     transpose_rows[i] += transpose_rows[i - 1];
564 |   }
565 | 
566 |   for (int r = 0; r < num_rows; ++r) {
567 |     for (int idx = jacobian.rows[r]; idx < jacobian.rows[r + 1]; ++idx) {
568 |       const int c = jacobian.cols[idx];
569 |       const int transpose_idx = transpose_rows[c];
570 |       transpose_cols[transpose_idx] = r;
571 |       transpose_values[transpose_idx] = jacobian.values[idx];
572 |       ++transpose_rows[c];
573 |     }
574 |   }
575 | 
576 |   for (int i = transpose_rows.size() - 1; i > 0; --i) {
577 |     transpose_rows[i] = transpose_rows[i - 1];
578 |   }
579 |   transpose_rows[0] = 0;
580 | 
581 |   cholmod_sparse cholmod_jacobian;
582 |   cholmod_jacobian.nrow = num_rows;
583 |   cholmod_jacobian.ncol = num_cols;
584 |   cholmod_jacobian.nzmax = num_nonzeros;
585 |   cholmod_jacobian.nz = nullptr;
586 |   cholmod_jacobian.p = reinterpret_cast<void*>(transpose_rows.data());
587 |   cholmod_jacobian.i = reinterpret_cast<void*>(transpose_cols.data());
588 |   cholmod_jacobian.x = reinterpret_cast<void*>(transpose_values.data());
589 |   cholmod_jacobian.z = nullptr;
590 |   cholmod_jacobian.stype = 0;  // Matrix is not symmetric.
591 |   cholmod_jacobian.itype = CHOLMOD_LONG;
592 |   cholmod_jacobian.xtype = CHOLMOD_REAL;
593 |   cholmod_jacobian.dtype = CHOLMOD_DOUBLE;
594 |   cholmod_jacobian.sorted = 1;
595 |   cholmod_jacobian.packed = 1;
596 | 
597 |   cholmod_common cc;
598 |   cholmod_l_start(&cc);
599 | 
600 |   cholmod_sparse* R = nullptr;
601 |   SuiteSparse_long* permutation = nullptr;
602 | 
603 |   // Compute a Q-less QR factorization of the Jacobian. Since we are
604 |   // only interested in inverting J'J = R'R, we do not need Q. This
605 |   // saves memory and gives us R as a permuted compressed column
606 |   // sparse matrix.
607 |   //
608 |   // TODO(sameeragarwal): Currently the symbolic factorization and the
609 |   // numeric factorization is done at the same time, and this does not
610 |   // explicitly account for the block column and row structure in the
611 |   // matrix. When using AMD, we have observed in the past that
612 |   // computing the ordering with the block matrix is significantly
613 |   // more efficient, both in runtime as well as the quality of
614 |   // ordering computed. So, it maybe worth doing that analysis
615 |   // separately.
616 |   const SuiteSparse_long rank = SuiteSparseQR<double>(
617 |       SPQR_ORDERING_BESTAMD,
618 |       options_.column_pivot_threshold < 0 ? SPQR_DEFAULT_TOL
619 |                                           : options_.column_pivot_threshold,
620 |       static_cast<int64_t>(cholmod_jacobian.ncol),
621 |       &cholmod_jacobian,
622 |       &R,
623 |       &permutation,
624 |       &cc);
625 |   event_logger.AddEvent("Numeric Factorization");
626 |   if (R == nullptr) {
627 |     LOG(ERROR) << "Something is wrong. SuiteSparseQR returned R = nullptr.";
628 |     free(permutation);
629 |     cholmod_l_finish(&cc);
630 |     return false;
631 |   }
632 | 
633 |   if (rank < cholmod_jacobian.ncol) {
634 |     LOG(WARNING) << "Jacobian matrix is rank deficient. "
635 |                  << "Number of columns: " << cholmod_jacobian.ncol
636 |                  << " rank: " << rank;
637 |     free(permutation);
638 |     cholmod_l_free_sparse(&R, &cc);
639 |     cholmod_l_finish(&cc);
640 |     return false;
641 |   }
642 | 
643 |   std::vector<int> inverse_permutation(num_cols);
644 |   if (permutation) {
645 |     for (SuiteSparse_long i = 0; i < num_cols; ++i) {
646 |       inverse_permutation[permutation[i]] = i;
647 |     }
648 |   } else {
649 |     for (SuiteSparse_long i = 0; i < num_cols; ++i) {
650 |       inverse_permutation[i] = i;
651 |     }
652 |   }
653 | 
654 |   const int* rows = covariance_matrix_->rows();
655 |   const int* cols = covariance_matrix_->cols();
656 |   double* values = covariance_matrix_->mutable_values();
657 | 
658 |   // The following loop exploits the fact that the i^th column of A^{-1}
659 |   // is given by the solution to the linear system
660 |   //
661 |   //  A x = e_i
662 |   //
663 |   // where e_i is a vector with e(i) = 1 and all other entries zero.
664 |   //
665 |   // Since the covariance matrix is symmetric, the i^th row and column
666 |   // are equal.
667 |   const int num_threads = options_.num_threads;
668 |   auto workspace = std::make_unique<double[]>(num_threads * num_cols);
669 | 
670 |   problem_->context()->EnsureMinimumThreads(num_threads);
671 |   ParallelFor(
672 |       problem_->context(), 0, num_cols, num_threads, [&](int thread_id, int r) {
673 |         const int row_begin = rows[r];
674 |         const int row_end = rows[r + 1];
675 |         if (row_end != row_begin) {
676 |           double* solution = workspace.get() + thread_id * num_cols;
677 |           SolveRTRWithSparseRHS<SuiteSparse_long>(
678 |               num_cols,
679 |               static_cast<SuiteSparse_long*>(R->i),
680 |               static_cast<SuiteSparse_long*>(R->p),
681 |               static_cast<double*>(R->x),
682 |               inverse_permutation[r],
683 |               solution);
684 |           for (int idx = row_begin; idx < row_end; ++idx) {
685 |             const int c = cols[idx];
686 |             values[idx] = solution[inverse_permutation[c]];
687 |           }
688 |         }
689 |       });
690 | 
691 |   free(permutation);
692 |   cholmod_l_free_sparse(&R, &cc);
693 |   cholmod_l_finish(&cc);
694 |   event_logger.AddEvent("Inversion");
695 |   return true;
696 | 
697 | #else  // CERES_NO_SUITESPARSE
698 | 
699 |   return false;
700 | 
701 | #endif  // CERES_NO_SUITESPARSE
702 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 0

START → 1
1   "CovarianceImpl::ComputeCovarianceValuesUsingSparseQR"
    return false                                                   → END
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
#include "ceres/covariance_impl.h"
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1380_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
