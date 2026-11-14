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

- Hàm: `UpdateImpl(const CompressedRowSparseMatrix & A, const double * D)`, trả về `bool`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::BlockCRSJacobiPreconditioner`
- Vị trí: `internal/ceres/block_jacobi_preconditioner.cc`, dòng 158–224

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
158 | bool BlockCRSJacobiPreconditioner::UpdateImpl(
159 |     const CompressedRowSparseMatrix& A, const double* D) {
160 |   const auto& col_blocks = A.col_blocks();
161 |   const auto& row_blocks = A.row_blocks();
162 |   const int num_col_blocks = col_blocks.size();
163 |   const int num_row_blocks = row_blocks.size();
164 | 
165 |   const int* a_rows = A.rows();
166 |   const int* a_cols = A.cols();
167 |   const double* a_values = A.values();
168 |   double* m_values = m_->mutable_values();
169 |   const int* m_rows = m_->rows();
170 | 
171 |   m_->SetZero();
172 | 
173 |   ParallelFor(
174 |       options_.context,
175 |       0,
176 |       num_row_blocks,
177 |       options_.num_threads,
178 |       [this, row_blocks, a_rows, a_cols, a_values, m_values, m_rows](int i) {
179 |         const int row = row_blocks[i].position;
180 |         const int row_block_size = row_blocks[i].size;
181 |         const int row_nnz = a_rows[row + 1] - a_rows[row];
182 |         ConstMatrixRef row_block(
183 |             a_values + a_rows[row], row_block_size, row_nnz);
184 |         int c = 0;
185 |         while (c < row_nnz) {
186 |           const int idx = a_rows[row] + c;
187 |           const int col = a_cols[idx];
188 |           const int col_block_size = m_rows[col + 1] - m_rows[col];
189 | 
190 |           // We make use of the fact that the entire diagonal block is
191 |           // stored contiguously in memory as a row-major matrix.
192 |           MatrixRef m(m_values + m_rows[col], col_block_size, col_block_size);
193 |           // We do not have a row_stride version of
194 |           // MatrixTransposeMatrixMultiply, otherwise we could use it
195 |           // here to further speed up the following expression.
196 |           auto b = row_block.middleCols(c, col_block_size);
197 |           auto lock = MakeConditionalLock(options_.num_threads, locks_[col]);
198 |           m.noalias() += b.transpose() * b;
199 |           c += col_block_size;
200 |         }
201 |       });
202 | 
203 |   ParallelFor(
204 |       options_.context,
205 |       0,
206 |       num_col_blocks,
207 |       options_.num_threads,
208 |       [col_blocks, m_rows, m_values, D](int i) {
209 |         const int col = col_blocks[i].position;
210 |         const int col_block_size = col_blocks[i].size;
211 |         MatrixRef m(m_values + m_rows[col], col_block_size, col_block_size);
212 | 
213 |         if (D != nullptr) {
214 |           m.diagonal() +=
215 |               ConstVectorRef(D + col, col_block_size).array().square().matrix();
216 |         }
217 | 
218 |         // TODO(sameeragarwal): Deal with Cholesky inversion failure here and
219 |         // elsewhere.
220 |         m = m.llt().solve(Matrix::Identity(col_block_size, col_block_size));
221 |       });
222 | 
223 |   return true;
224 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 0

START → 1
1   const auto &col_blocks = A.col_blocks()
    const auto &row_blocks = A.row_blocks()
    const int num_col_blocks = col_blocks.size()
    const int num_row_blocks = row_blocks.size()
    const int *a_rows = A.rows()
    const int *a_cols = A.cols()
    const double *a_values = A.values()
    double *m_values = m_->mutable_values()
    const int *m_rows = m_->rows()
    m_->SetZero()
    ParallelFor (ImplicitCastExpr, FunctionToPointerDecay, void (*)(ContextImpl *, int, int, int, class (lambda at /work/ceres-solver/internal/ceres/block_jacobi_preconditioner.cc:178:7) &&, int))(options_.context, 0, num_row_blocks, options_.num_threads, [this, row_blocks, a_rows, a_cols, a_values, m_values, m_rows](int i) {)
    ParallelFor (ImplicitCastExpr, FunctionToPointerDecay, void (*)(ContextImpl *, int, int, int, class (lambda at /work/ceres-solver/internal/ceres/block_jacobi_preconditioner.cc:208:7) &&, int))(options_.context, 0, num_col_blocks, options_.num_threads, [col_blocks, m_rows, m_values, D](int i) {)
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
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/parallel_for.h"
```

- Method này là `private` (bên ngoài class không gọi được). Thêm 2 dòng `#define private public` và `#define protected public` **sau** `#include "gtest/gtest.h"` và **trước** các `#include` của Ceres.
- Đây là method của class `ceres::internal::BlockCRSJacobiPreconditioner`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `BlockCRSJacobiPreconditioner`:
Các constructor:
```cpp
  BlockCRSJacobiPreconditioner(Preconditioner::Options options, const CompressedRowSparseMatrix & A)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1231_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
