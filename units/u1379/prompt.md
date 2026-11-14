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

- Hàm: `ComputeOffsetsAndCreateResultMatrix(const CompressedRowSparseMatrix::StorageType product_storage_type, const std::vector<InnerProductComputer::ProductTerm> & product_terms)`, trả về `void`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::InnerProductComputer`
- Vị trí: `internal/ceres/inner_product_computer.cc`, dòng 179–280

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
179 | void InnerProductComputer::ComputeOffsetsAndCreateResultMatrix(
180 |     const CompressedRowSparseMatrix::StorageType product_storage_type,
181 |     const std::vector<InnerProductComputer::ProductTerm>& product_terms) {
182 |   const std::vector<Block>& col_blocks = m_.block_structure()->cols;
183 | 
184 |   std::vector<int> row_block_nnz;
185 |   const int num_nonzeros = ComputeNonzeros(product_terms, &row_block_nnz);
186 | 
187 |   result_ = CreateResultMatrix(product_storage_type, num_nonzeros);
188 | 
189 |   // Populate the row non-zero counts in the result matrix.
190 |   int* crsm_rows = result_->mutable_rows();
191 |   crsm_rows[0] = 0;
192 |   for (int i = 0; i < col_blocks.size(); ++i) {
193 |     for (int j = 0; j < col_blocks[i].size; ++j, ++crsm_rows) {
194 |       *(crsm_rows + 1) = *crsm_rows + row_block_nnz[i];
195 |     }
196 |   }
197 |   result_offsets_.resize(product_terms.size());
198 |   if (num_nonzeros == 0) {
199 |     return;
200 |   }
201 | 
202 |   // The following macro FILL_CRSM_COL_BLOCK is key to understanding
203 |   // how this class works.
204 |   //
205 |   // It does two things.
206 |   //
207 |   // Sets the value for the current term in the result_offsets_ array
208 |   // and populates the cols array of the result matrix.
209 |   //
210 |   // row_block and col_block as the names imply, refer to the row and
211 |   // column blocks of the current term.
212 |   //
213 |   // row_nnz is the number of nonzeros in the result_matrix at the
214 |   // beginning of the first row of row_block.
215 |   //
216 |   // col_nnz is the number of nonzeros in the first row of the row
217 |   // block that occur before the current column block, i.e. this is
218 |   // sum of the sizes of all the column blocks in this row block that
219 |   // came before this column block.
220 |   //
221 |   // Given these two numbers and the total number of nonzeros in this
222 |   // row (nnz_in_row), we can now populate the cols array as follows:
223 |   //
224 |   // nnz + j * nnz_in_row is the beginning of the j^th row.
225 |   //
226 |   // nnz + j * nnz_in_row + col_nnz is the beginning of the column
227 |   // block in the j^th row.
228 |   //
229 |   // nnz + j * nnz_in_row + col_nnz + k is then the j^th row and the
230 |   // k^th column of the product block, whose value is
231 |   //
232 |   // col_blocks[col_block].position + k, which is the column number of
233 |   // the k^th column of the current column block.
234 | #define FILL_CRSM_COL_BLOCK                                \
235 |   const int row_block = current->row;                      \
236 |   const int col_block = current->col;                      \
237 |   const int nnz_in_row = row_block_nnz[row_block];         \
238 |   int* crsm_cols = result_->mutable_cols();                \
239 |   result_offsets_[current->index] = nnz + col_nnz;         \
240 |   for (int j = 0; j < col_blocks[row_block].size; ++j) {   \
241 |     for (int k = 0; k < col_blocks[col_block].size; ++k) { \
242 |       crsm_cols[nnz + j * nnz_in_row + col_nnz + k] =      \
243 |           col_blocks[col_block].position + k;              \
244 |     }                                                      \
245 |   }
246 | 
247 |   int col_nnz = 0;
248 |   int nnz = 0;
249 | 
250 |   // Process the first term.
251 |   const InnerProductComputer::ProductTerm* current = product_terms.data();
252 |   FILL_CRSM_COL_BLOCK;
253 | 
254 |   // Process the rest of the terms.
255 |   for (int i = 1; i < product_terms.size(); ++i) {
256 |     current = &product_terms[i];
257 |     const InnerProductComputer::ProductTerm* previous = &product_terms[i - 1];
258 | 
259 |     // If the current term is the same as the previous term, then it
260 |     // stores its product at the same location as the previous term.
261 |     if (previous->row == current->row && previous->col == current->col) {
262 |       result_offsets_[current->index] = result_offsets_[previous->index];
263 |       continue;
264 |     }
265 | 
266 |     if (previous->row == current->row) {
267 |       // if the current and previous terms are in the same row block,
268 |       // then they differ in the column block, in which case advance
269 |       // col_nnz by the column size of the previous term.
270 |       col_nnz += col_blocks[previous->col].size;
271 |     } else {
272 |       // If we have moved to a new row-block , then col_nnz is zero,
273 |       // and nnz is set to the beginning of the row block.
274 |       col_nnz = 0;
275 |       nnz += row_block_nnz[previous->row] * col_blocks[previous->row].size;
276 |     }
277 | 
278 |     FILL_CRSM_COL_BLOCK;
279 |   }
280 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 10

START → 1
1   const std::vector<Block> &col_blocks = m_.block_structure()->cols
    const int num_nonzeros = ComputeNonzeros(product_terms, &row_block_nnz)
    result_ = CreateResultMatrix(product_storage_type, num_nonzeros)
    int *crsm_rows = result_->mutable_rows()
    crsm_rows[0] = 0
    int i = 0                                                      → 2
2   vòng for, điều kiện: i < col_blocks.size()                     đúng → 3   sai → 8
3   int j = 0                                                      → 4
4   vòng for, điều kiện: j < col_blocks[i].size                    đúng → 5   sai → 7
5   *(crsm_rows + 1) = *crsm_rows + row_block_nnz[i]               → 6
6   ++j                                                            → 4
7   ++i                                                            → 2
8   result_offsets_.resize(product_terms.size())                   → 9
9   if (num_nonzeros == 0)                                         đúng → 10   sai → 11
10  return                                                         → END
11  int col_nnz = 0
    int nnz = 0
    const InnerProductComputer::ProductTerm *current = product_terms.data()
    const int row_block = current->row
    const int col_block = current->col
    const int nnz_in_row = row_block_nnz[row_block]
    int *crsm_cols = result_->mutable_cols()
    result_offsets_[current->index] = nnz + col_nnz
    int j = 0                                                      → 12
12  vòng for, điều kiện: j < col_blocks[row_block].size            đúng → 13   sai → 18
13  int k = 0                                                      → 14
14  vòng for, điều kiện: k < col_blocks[col_block].size            đúng → 15   sai → 17
15  crsm_cols[nnz + j * nnz_in_row + col_nnz + k] = col_blocks[col_block].position + k   → 16
16  ++k                                                            → 14
17  ++j                                                            → 12
18  int i = 1                                                      → 19
19  vòng for, điều kiện: i < product_terms.size()                  đúng → 20   sai → END
20  current = &product_terms[i]
    const InnerProductComputer::ProductTerm *previous = &product_terms[i - 1]   → 21
21  if (previous->row == current->row && previous->col == current->col)   đúng → 22   sai → 24
22  result_offsets_[current->index] = result_offsets_[previous->index]
    continue                                                       → 23
23  ++i                                                            → 19
24  if (previous->row == current->row)                             đúng → 25   sai → 33
25  col_nnz += col_blocks[previous->col].size                      → 26
26  const int row_block = current->row
    const int col_block = current->col
    const int nnz_in_row = row_block_nnz[row_block]
    int *crsm_cols = result_->mutable_cols()
    result_offsets_[current->index] = nnz + col_nnz
    int j = 0                                                      → 27
27  vòng for, điều kiện: j < col_blocks[row_block].size            đúng → 28   sai → 23
28  int k = 0                                                      → 29
29  vòng for, điều kiện: k < col_blocks[col_block].size            đúng → 30   sai → 32
30  crsm_cols[nnz + j * nnz_in_row + col_nnz + k] = col_blocks[col_block].position + k   → 31
31  ++k                                                            → 29
32  ++j                                                            → 27
33  col_nnz = 0
    nnz += row_block_nnz[previous->row] * col_blocks[previous->row].size   → 26
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
#include "ceres/block_structure.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/inner_product_computer.h"
```

- Method này là `private` (bên ngoài class không gọi được). Thêm 2 dòng `#define private public` và `#define protected public` **sau** `#include "gtest/gtest.h"` và **trước** các `#include` của Ceres.
- Đây là method của class `ceres::internal::InnerProductComputer`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `InnerProductComputer`:
Các constructor:
```cpp
  InnerProductComputer(const BlockSparseMatrix & m, const int start_row_block, const int end_row_block)   // private
  InnerProductComputer(const BlockSparseMatrix & m, int start_row_block, int end_row_block)   // private
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1379_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
