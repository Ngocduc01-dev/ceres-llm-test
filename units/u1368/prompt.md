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

- Hàm: `CreateJacobian() const`, trả về `std::unique_ptr<SparseMatrix>`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::BlockJacobianWriter`
- Vị trí: `internal/ceres/block_jacobian_writer.cc`, dòng 196–261

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
196 | std::unique_ptr<SparseMatrix> BlockJacobianWriter::CreateJacobian() const {
197 |   if (!jacobian_layout_is_valid_) {
198 |     LOG(ERROR) << "Unable to create Jacobian matrix. Too many entries in the "
199 |                   "Jacobian matrix.";
200 |     return nullptr;
201 |   }
202 | 
203 |   auto* bs = new CompressedRowBlockStructure;
204 | 
205 |   const std::vector<ParameterBlock*>& parameter_blocks =
206 |       program_->parameter_blocks();
207 | 
208 |   // Construct the column blocks.
209 |   bs->cols.resize(parameter_blocks.size());
210 |   for (int i = 0, cursor = 0; i < parameter_blocks.size(); ++i) {
211 |     CHECK_NE(parameter_blocks[i]->index(), -1);
212 |     CHECK(!parameter_blocks[i]->IsConstant());
213 |     bs->cols[i].size = parameter_blocks[i]->TangentSize();
214 |     bs->cols[i].position = cursor;
215 |     cursor += bs->cols[i].size;
216 |   }
217 | 
218 |   // Construct the cells in each row.
219 |   const std::vector<ResidualBlock*>& residual_blocks =
220 |       program_->residual_blocks();
221 |   int row_block_position = 0;
222 |   bs->rows.resize(residual_blocks.size());
223 |   for (int i = 0; i < residual_blocks.size(); ++i) {
224 |     const ResidualBlock* residual_block = residual_blocks[i];
225 |     CompressedRow* row = &bs->rows[i];
226 | 
227 |     row->block.size = residual_block->NumResiduals();
228 |     row->block.position = row_block_position;
229 |     row_block_position += row->block.size;
230 | 
231 |     // Size the row by the number of active parameters in this residual.
232 |     const int num_parameter_blocks = residual_block->NumParameterBlocks();
233 |     int num_active_parameter_blocks = 0;
234 |     for (int j = 0; j < num_parameter_blocks; ++j) {
235 |       if (residual_block->parameter_blocks()[j]->index() != -1) {
236 |         num_active_parameter_blocks++;
237 |       }
238 |     }
239 |     row->cells.resize(num_active_parameter_blocks);
240 | 
241 |     // Add layout information for the active parameters in this row.
242 |     for (int j = 0, k = 0; j < num_parameter_blocks; ++j) {
243 |       const ParameterBlock* parameter_block =
244 |           residual_block->parameter_blocks()[j];
245 |       if (!parameter_block->IsConstant()) {
246 |         Cell& cell = row->cells[k];
247 |         cell.block_id = parameter_block->index();
248 |         cell.position = jacobian_layout_[i][k];
249 | 
250 |         // Only increment k for active parameters, since there is only layout
251 |         // information for active parameters.
252 |         k++;
253 |       }
254 |     }
255 | 
256 |     std::sort(row->cells.begin(), row->cells.end(), CellLessThan);
257 |   }
258 | 
259 |   return std::make_unique<BlockSparseMatrix>(
260 |       bs, options_.sparse_linear_algebra_library_type == CUDA_SPARSE);
261 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 7 (và 2 lệnh CHECK)

START → 1
1   if (!jacobian_layout_is_valid_)                                đúng → END   sai → 2
2   CFGNewAllocator(CompressedRowBlockStructure *)
    auto *bs = new CompressedRowBlockStructure
    const std::vector<ParameterBlock *> &parameter_blocks = program_->parameter_blocks()
    bs->cols.resize(parameter_blocks.size())
    int i = 0
    int cursor = 0                                                 → 3
3   vòng for, điều kiện: i < parameter_blocks.size()               đúng → 4   sai → 7
4   CHECK_NE(parameter_blocks[i]->index(), -1)                     đúng → 5   sai → DỪNG
5   CHECK(!parameter_blocks[i]->IsConstant())                      đúng → 6   sai → DỪNG
6   ++i                                                            → 3
7   const std::vector<ResidualBlock *> &residual_blocks = program_->residual_blocks()
    int row_block_position = 0
    bs->rows.resize(residual_blocks.size())
    int i = 0                                                      → 8
8   vòng for, điều kiện: i < residual_blocks.size()                đúng → 9   sai → END
9   const ResidualBlock *residual_block = residual_blocks[i]
    CompressedRow *row = &bs->rows[i]
    row->block.size = residual_block->NumResiduals()
    row->block.position = row_block_position
    row_block_position += row->block.size
    const int num_parameter_blocks = residual_block->NumParameterBlocks()
    int num_active_parameter_blocks = 0
    int j = 0                                                      → 10
10  vòng for, điều kiện: j < num_parameter_blocks                  đúng → 11   sai → 14
11  if (residual_block->parameter_blocks()[j]->index() != -1)      đúng → 12   sai → 13
12  num_active_parameter_blocks++                                  → 13
13  ++j                                                            → 10
14  row->cells.resize(num_active_parameter_blocks)
    int j = 0
    int k = 0                                                      → 15
15  vòng for, điều kiện: j < num_parameter_blocks                  đúng → 16   sai → 20
16  const ParameterBlock *parameter_block = residual_block->parameter_blocks()[j]   → 17
17  if (!parameter_block->IsConstant())                            đúng → 18   sai → 19
18  Cell &cell = row->cells[k]
    cell.block_id = parameter_block->index()
    cell.position = jacobian_layout_[i][k]
    k++                                                            → 19
19  ++j                                                            → 15
20  ++i                                                            → 8
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
#include "ceres/block_jacobian_writer.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/parameter_block.h"
#include "ceres/residual_block.h"
#include "ceres/sparse_matrix.h"
```

- Đây là method của class `ceres::internal::BlockJacobianWriter`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `BlockJacobianWriter`:
Các constructor:
```cpp
  BlockJacobianWriter(const Evaluator::Options & options, Program * program)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1368_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
