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

- Hàm: `UpdateImpl(const BlockSparseMatrix & A, const double * D)`, trả về `bool`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::BlockSparseJacobiPreconditioner`
- Vị trí: `internal/ceres/block_jacobi_preconditioner.cc`, dòng 58–114

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
 58 | bool BlockSparseJacobiPreconditioner::UpdateImpl(const BlockSparseMatrix& A,
 59 |                                                  const double* D) {
 60 |   const CompressedRowBlockStructure* bs = A.block_structure();
 61 |   const double* values = A.values();
 62 |   m_->SetZero();
 63 | 
 64 |   ParallelFor(options_.context,
 65 |               0,
 66 |               bs->rows.size(),
 67 |               options_.num_threads,
 68 |               [this, bs, values](int i) {
 69 |                 const int row_block_size = bs->rows[i].block.size;
 70 |                 const std::vector<Cell>& cells = bs->rows[i].cells;
 71 |                 for (const auto& cell : cells) {
 72 |                   const int block_id = cell.block_id;
 73 |                   const int col_block_size = bs->cols[block_id].size;
 74 |                   int r, c, row_stride, col_stride;
 75 |                   CellInfo* cell_info = m_->GetCell(
 76 |                       block_id, block_id, &r, &c, &row_stride, &col_stride);
 77 |                   MatrixRef m(cell_info->values, row_stride, col_stride);
 78 |                   ConstMatrixRef b(
 79 |                       values + cell.position, row_block_size, col_block_size);
 80 |                   auto lock =
 81 |                       MakeConditionalLock(options_.num_threads, cell_info->m);
 82 |                   // clang-format off
 83 |                   MatrixTransposeMatrixMultiply<Eigen::Dynamic, Eigen::Dynamic,
 84 |                       Eigen::Dynamic,Eigen::Dynamic, 1>(
 85 |                           values + cell.position, row_block_size,col_block_size,
 86 |                           values + cell.position, row_block_size,col_block_size,
 87 |                           cell_info->values,r, c,row_stride,col_stride);
 88 |                   // clang-format on
 89 |                 }
 90 |               });
 91 | 
 92 |   if (D != nullptr) {
 93 |     // Add the diagonal.
 94 |     ParallelFor(options_.context,
 95 |                 0,
 96 |                 bs->cols.size(),
 97 |                 options_.num_threads,
 98 |                 [this, bs, D](int i) {
 99 |                   const int block_size = bs->cols[i].size;
100 |                   int r, c, row_stride, col_stride;
101 |                   CellInfo* cell_info =
102 |                       m_->GetCell(i, i, &r, &c, &row_stride, &col_stride);
103 |                   MatrixRef m(cell_info->values, row_stride, col_stride);
104 |                   m.block(r, c, block_size, block_size).diagonal() +=
105 |                       ConstVectorRef(D + bs->cols[i].position, block_size)
106 |                           .array()
107 |                           .square()
108 |                           .matrix();
109 |                 });
110 |   }
111 | 
112 |   m_->Invert();
113 |   return true;
114 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 1

START → 1
1   const CompressedRowBlockStructure *bs = A.block_structure()
    const double *values = A.values()
    m_->SetZero()
    ParallelFor (ImplicitCastExpr, FunctionToPointerDecay, void (*)(ContextImpl *, int, int, int, class (lambda at /work/ceres-solver/internal/ceres/block_jacobi_preconditioner.cc:68:15) &&, int))(options_.context, 0, bs->rows.size(), options_.num_threads, [this, bs, values](int i) {)   → 2
2   if (D != nullptr)                                              đúng → 3   sai → 4
3   ParallelFor (ImplicitCastExpr, FunctionToPointerDecay, void (*)(ContextImpl *, int, int, int, class (lambda at /work/ceres-solver/internal/ceres/block_jacobi_preconditioner.cc:98:17) &&, int))(options_.context, 0, bs->cols.size(), options_.num_threads, [this, bs, D](int i) {)   → 4
4   m_->Invert()
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
#include "ceres/block_jacobi_preconditioner.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/parallel_for.h"
#include "ceres/small_blas.h"
```

- Method này là `private` (bên ngoài class không gọi được). Thêm 2 dòng `#define private public` và `#define protected public` **sau** `#include "gtest/gtest.h"` và **trước** các `#include` của Ceres.
- Đây là method của class `ceres::internal::BlockSparseJacobiPreconditioner`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `BlockSparseJacobiPreconditioner`:
Các constructor:
```cpp
  BlockSparseJacobiPreconditioner(Preconditioner::Options options, const BlockSparseMatrix & A)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1372_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
