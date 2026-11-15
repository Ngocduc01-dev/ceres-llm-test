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

- Hàm: `ComputeSubspaceModel(SparseMatrix * jacobian)`, trả về `bool`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::DoglegStrategy`
- Vị trí: `internal/ceres/dogleg_strategy.cc`, dòng 647–716

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
647 | bool DoglegStrategy::ComputeSubspaceModel(SparseMatrix* jacobian) {
648 |   // Compute an orthogonal basis for the subspace using QR decomposition.
649 |   Matrix basis_vectors(jacobian->num_cols(), 2);
650 |   basis_vectors.col(0) = gradient_;
651 |   basis_vectors.col(1) = gauss_newton_step_;
652 |   Eigen::ColPivHouseholderQR<Matrix> basis_qr(basis_vectors);
653 | 
654 |   switch (basis_qr.rank()) {
655 |     case 0:
656 |       // This should never happen, as it implies that both the gradient
657 |       // and the Gauss-Newton step are zero. In this case, the minimizer should
658 |       // have stopped due to the gradient being too small.
659 |       LOG(ERROR) << "Rank of subspace basis is 0. "
660 |                  << "This means that the gradient at the current iterate is "
661 |                  << "zero but the optimization has not been terminated. "
662 |                  << "You may have found a bug in Ceres.";
663 |       return false;
664 | 
665 |     case 1:
666 |       // Gradient and Gauss-Newton step coincide, so we lie on one of the
667 |       // major axes of the quadratic problem. In this case, we simply move
668 |       // along the gradient until we reach the trust region boundary.
669 |       subspace_is_one_dimensional_ = true;
670 |       return true;
671 | 
672 |     case 2:
673 |       subspace_is_one_dimensional_ = false;
674 |       break;
675 | 
676 |     default:
677 |       LOG(ERROR) << "Rank of the subspace basis matrix is reported to be "
678 |                  << "greater than 2. As the matrix contains only two "
679 |                  << "columns this cannot be true and is indicative of "
680 |                  << "a bug.";
681 |       return false;
682 |   }
683 | 
684 |   // The subspace is two-dimensional, so compute the subspace model.
685 |   // Given the basis U, this is
686 |   //
687 |   //   subspace_g_ = g_scaled^T U
688 |   //
689 |   // and
690 |   //
691 |   //   subspace_B_ = U^T (J_scaled^T J_scaled) U
692 |   //
693 |   // As J_scaled = J * D^-1, the latter becomes
694 |   //
695 |   //   subspace_B_ = ((U^T D^-1) J^T) (J (D^-1 U))
696 |   //               = (J (D^-1 U))^T (J (D^-1 U))
697 | 
698 |   subspace_basis_ =
699 |       basis_qr.householderQ() * Matrix::Identity(jacobian->num_cols(), 2);
700 | 
701 |   subspace_g_ = subspace_basis_.transpose() * gradient_;
702 | 
703 |   Eigen::Matrix<double, 2, Eigen::Dynamic, Eigen::RowMajor> Jb(
704 |       2, jacobian->num_rows());
705 |   Jb.setZero();
706 | 
707 |   Vector tmp;
708 |   tmp = (subspace_basis_.col(0).array() / diagonal_.array()).matrix();
709 |   jacobian->RightMultiplyAndAccumulate(tmp.data(), Jb.row(0).data());
710 |   tmp = (subspace_basis_.col(1).array() / diagonal_.array()).matrix();
711 |   jacobian->RightMultiplyAndAccumulate(tmp.data(), Jb.row(1).data());
712 | 
713 |   subspace_B_ = Jb * Jb.transpose();
714 | 
715 |   return true;
716 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 1

START → 1
1   jacobian->num_cols(), 2
    basis_vectors.col(0) = gradient_
    basis_vectors.col(1) = gauss_newton_step_                      → 2
2   switch (basis_qr.rank())                                       nhánh → 3   nhánh → 5   nhánh → END   nhánh → END
3   subspace_is_one_dimensional_ = false
    break                                                          → 4
4   subspace_basis_ = basis_qr.householderQ() * Matrix::Identity(jacobian->num_cols(), 2)
    subspace_g_ = subspace_basis_.transpose() * gradient_
    2, jacobian->num_rows()
    Jb.setZero()
    tmp = (subspace_basis_.col(0).array() / diagonal_.array()).matrix()
    jacobian->RightMultiplyAndAccumulate(tmp.data(), Jb.row(0).data())
    tmp = (subspace_basis_.col(1).array() / diagonal_.array()).matrix()
    jacobian->RightMultiplyAndAccumulate(tmp.data(), Jb.row(1).data())
    subspace_B_ = Jb * Jb.transpose()
    return true                                                    → END
5   subspace_is_one_dimensional_ = true
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
#include "ceres/dogleg_strategy.h"
#include "ceres/sparse_matrix.h"
```

- Method này là `private` (bên ngoài class không gọi được). Thêm 2 dòng `#define private public` và `#define protected public` **sau** `#include "gtest/gtest.h"` và **trước** các `#include` của Ceres.
- Đây là method của class `ceres::internal::DoglegStrategy`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `DoglegStrategy`:
Các constructor:
```cpp
  DoglegStrategy(const TrustRegionStrategy::Options & options)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u0972_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
