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
- **Vòng lặp:**
  - Có giới hạn số lần lặp n (ví dụ `for (i = 0; i < size; ...)`): test với **0, 1, 2, một số ở giữa, n−1, n** lần lặp; thêm **n+1** nếu làm được.
  - Không có giới hạn (lặp đến khi thoả một điều kiện, ví dụ `while (!done)`): test với **0, 1, 2** lần lặp và **mỗi cách thoát khỏi vòng lặp** (`break`, `return`, điều kiện sai) ít nhất 1 lần.
  - Số lần lặp nào không làm được thì ghi lý do.
- **`CHECK(...)`:** lệnh kiểm tra của thư viện glog mà Ceres dùng. Nếu điều kiện sai, chương trình **dừng ngay**. **Không** cố tình làm `CHECK` sai; ghi nhánh đó là "không test (làm chương trình dừng)".

---

# 3. ĐẦU VÀO

## 3.1. Unit cần test

- Hàm: `UpdateImpl(const BlockSparseMatrix & A, const double * D)`, trả về `bool`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::SubsetPreconditioner`
- Vị trí: `internal/ceres/subset_preconditioner.cc`, dòng 68–115

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
 68 | bool SubsetPreconditioner::UpdateImpl(const BlockSparseMatrix& A,
 69 |                                       const double* D) {
 70 |   auto* m = const_cast<BlockSparseMatrix*>(&A);
 71 |   const CompressedRowBlockStructure* bs = m->block_structure();
 72 | 
 73 |   // A = [P]
 74 |   //     [Q]
 75 | 
 76 |   // Now add D to A if needed.
 77 |   if (D != nullptr) {
 78 |     // A = [P]
 79 |     //     [Q]
 80 |     //     [D]
 81 |     std::unique_ptr<BlockSparseMatrix> regularizer(
 82 |         BlockSparseMatrix::CreateDiagonalMatrix(D, bs->cols));
 83 |     m->AppendRows(*regularizer);
 84 |   }
 85 | 
 86 |   if (inner_product_computer_ == nullptr) {
 87 |     inner_product_computer_ = InnerProductComputer::Create(
 88 |         *m,
 89 |         options_.subset_preconditioner_start_row_block,
 90 |         bs->rows.size(),
 91 |         sparse_cholesky_->StorageType());
 92 |   }
 93 | 
 94 |   // Compute inner_product = [Q'*Q + D'*D]
 95 |   inner_product_computer_->Compute();
 96 | 
 97 |   // Unappend D if needed.
 98 |   if (D != nullptr) {
 99 |     // A = [P]
100 |     //     [Q]
101 |     m->DeleteRowBlocks(bs->cols.size());
102 |   }
103 | 
104 |   std::string message;
105 |   // Compute L. s.t., LL' = Q'*Q + D'*D
106 |   const LinearSolverTerminationType termination_type =
107 |       sparse_cholesky_->Factorize(inner_product_computer_->mutable_result(),
108 |                                   &message);
109 |   if (termination_type != LinearSolverTerminationType::SUCCESS) {
110 |     LOG(ERROR) << "Preconditioner factorization failed: " << message;
111 |     return false;
112 |   }
113 | 
114 |   return true;
115 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 4

START → 1
1   const_cast<BlockSparseMatrix *>(&A) (CXXConstCastExpr, NoOp, BlockSparseMatrix *)
    auto *m = const_cast<BlockSparseMatrix *>(&A)
    const CompressedRowBlockStructure *bs = m->block_structure()   → 2
2   if (D != nullptr)                                              đúng → 3   sai → 4
3   operator* (ImplicitCastExpr, FunctionToPointerDecay, typename add_lvalue_reference<element_type>::type (*)(void) const noexcept(noexcept(*std::declval<pointer>())))
    m->AppendRows(* regularizer)                                   → 4
4   if (inner_product_computer_ == nullptr)                        đúng → 5   sai → 6
5   inner_product_computer_ = InnerProductComputer::Create(*m, options_.subset_preconditioner_start_row_block, bs->rows.size(), sparse_cholesky_->StorageType())   → 6
6   inner_product_computer_->Compute()                             → 7
7   if (D != nullptr)                                              đúng → 8   sai → 9
8   m->DeleteRowBlocks(bs->cols.size())                            → 9
9   const LinearSolverTerminationType termination_type = sparse_cholesky_->Factorize(inner_product_computer_->mutable_result(), &message)   → 10
10  if (termination_type != LinearSolverTerminationType::SUCCESS)   đúng → END   sai → 11
11  return true                                                    → END
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
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/inner_product_computer.h"
#include "ceres/sparse_cholesky.h"
#include "ceres/subset_preconditioner.h"
```

- Method này là `private` (bên ngoài class không gọi được). Thêm 2 dòng `#define private public` và `#define protected public` **sau** `#include "gtest/gtest.h"` và **trước** các `#include` của Ceres.
- Đây là method của class `ceres::internal::SubsetPreconditioner`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `SubsetPreconditioner`:
Các constructor:
```cpp
  SubsetPreconditioner(Preconditioner::Options options, const BlockSparseMatrix & A)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1374_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
