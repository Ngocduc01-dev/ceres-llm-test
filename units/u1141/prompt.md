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

- Hàm: `InitStorage(const CompressedRowBlockStructure * bs)`, trả về `void`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::SparseSchurComplementSolver`
- Vị trí: `internal/ceres/schur_complement_solver.cc`, dòng 223–288

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
223 | void SparseSchurComplementSolver::InitStorage(
224 |     const CompressedRowBlockStructure* bs) {
225 |   const int num_eliminate_blocks = options().elimination_groups[0];
226 |   const int num_col_blocks = bs->cols.size();
227 |   const int num_row_blocks = bs->rows.size();
228 | 
229 |   blocks_ = Tail(bs->cols, num_col_blocks - num_eliminate_blocks);
230 | 
231 |   std::set<std::pair<int, int>> block_pairs;
232 |   for (int i = 0; i < blocks_.size(); ++i) {
233 |     block_pairs.emplace(i, i);
234 |   }
235 | 
236 |   int r = 0;
237 |   while (r < num_row_blocks) {
238 |     int e_block_id = bs->rows[r].cells.front().block_id;
239 |     if (e_block_id >= num_eliminate_blocks) {
240 |       break;
241 |     }
242 |     std::vector<int> f_blocks;
243 | 
244 |     // Add to the chunk until the first block in the row is
245 |     // different than the one in the first row for the chunk.
246 |     for (; r < num_row_blocks; ++r) {
247 |       const CompressedRow& row = bs->rows[r];
248 |       if (row.cells.front().block_id != e_block_id) {
249 |         break;
250 |       }
251 | 
252 |       // Iterate over the blocks in the row, ignoring the first
253 |       // block since it is the one to be eliminated.
254 |       for (int c = 1; c < row.cells.size(); ++c) {
255 |         const Cell& cell = row.cells[c];
256 |         f_blocks.push_back(cell.block_id - num_eliminate_blocks);
257 |       }
258 |     }
259 | 
260 |     sort(f_blocks.begin(), f_blocks.end());
261 |     f_blocks.erase(unique(f_blocks.begin(), f_blocks.end()), f_blocks.end());
262 |     for (int i = 0; i < f_blocks.size(); ++i) {
263 |       for (int j = i + 1; j < f_blocks.size(); ++j) {
264 |         block_pairs.emplace(f_blocks[i], f_blocks[j]);
265 |       }
266 |     }
267 |   }
268 | 
269 |   // Remaining rows do not contribute to the chunks and directly go
270 |   // into the schur complement via an outer product.
271 |   for (; r < num_row_blocks; ++r) {
272 |     const CompressedRow& row = bs->rows[r];
273 |     CHECK_GE(row.cells.front().block_id, num_eliminate_blocks);
274 |     for (int i = 0; i < row.cells.size(); ++i) {
275 |       int r_block1_id = row.cells[i].block_id - num_eliminate_blocks;
276 |       for (const auto& cell : row.cells) {
277 |         int r_block2_id = cell.block_id - num_eliminate_blocks;
278 |         if (r_block1_id <= r_block2_id) {
279 |           block_pairs.emplace(r_block1_id, r_block2_id);
280 |         }
281 |       }
282 |     }
283 |   }
284 | 
285 |   set_lhs(std::make_unique<BlockRandomAccessSparseMatrix>(
286 |       blocks_, block_pairs, options().context, options().num_threads));
287 |   ResizeRhs(lhs()->num_rows());
288 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 12 (và 1 lệnh CHECK)

START → 1
1   const int num_eliminate_blocks = options().elimination_groups[0]
    const int num_col_blocks = bs->cols.size()
    const int num_row_blocks = bs->rows.size()
    operator= (ImplicitCastExpr, FunctionToPointerDecay, vector<Block> &(*)(vector<Block> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    blocks_ = Tail(bs->cols, num_col_blocks - num_eliminate_blocks)
    int i = 0                                                      → 2
2   vòng for, điều kiện: i < blocks_.size()                        đúng → 3   sai → 5
3   block_pairs.emplace(i, i)                                      → 4
4   ++i                                                            → 2
5   int r = 0                                                      → 6
6   while (r < num_row_blocks)                                     đúng → 7   sai → 10
7   int e_block_id = bs->rows[r].cells.front().block_id            → 8
8   if (e_block_id >= num_eliminate_blocks)                        đúng → 9   sai → 24
9   break                                                          → 10
10  for (; r < num_row_blocks; ...)                                đúng → 11   sai → 23
11  const CompressedRow &row = bs->rows[r]                         → 12
12  CHECK_GE(row.cells.front().block_id, num_eliminate_blocks)     đúng → 13   sai → DỪNG
13  int i = 0                                                      → 14
14  vòng for, điều kiện: i < row.cells.size()                      đúng → 15   sai → 22
15  int r_block1_id = row.cells[i].block_id - num_eliminate_blocks   → 16
16  for (const auto &cell : row.cells)                             đúng → 17   sai → 21
17  const auto &cell
    int r_block2_id = cell.block_id - num_eliminate_blocks         → 18
18  if (r_block1_id <= r_block2_id)                                đúng → 19   sai → 20
19  block_pairs.emplace(r_block1_id, r_block2_id)                  → 20
20  ++ (bước tiếp của vòng for)                                    → 16
21  ++i                                                            → 14
22  ++r                                                            → 10
23  ResizeRhs(lhs()->num_rows())                                   → END
24  for (; r < num_row_blocks; ...)                                đúng → 25   sai → 28
25  const CompressedRow &row = bs->rows[r]                         → 26
26  if (row.cells.front().block_id != e_block_id)                  đúng → 27   sai → 35
27  break                                                          → 28
28  int i = 0                                                      → 29
29  vòng for, điều kiện: i < f_blocks.size()                       đúng → 30   sai → 6
30  int j = i + 1                                                  → 31
31  vòng for, điều kiện: j < f_blocks.size()                       đúng → 32   sai → 34
32  block_pairs.emplace(f_blocks[i], f_blocks[j])                  → 33
33  ++j                                                            → 31
34  ++i                                                            → 29
35  int c = 1                                                      → 36
36  vòng for, điều kiện: c < row.cells.size()                      đúng → 37   sai → 39
37  const Cell &cell = row.cells[c]
    f_blocks.push_back(cell.block_id - num_eliminate_blocks)       → 38
38  ++c                                                            → 36
39  ++r                                                            → 24
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
#include "ceres/block_random_access_matrix.h"
#include "ceres/block_random_access_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/schur_complement_solver.h"
```

- Method này là `private` (bên ngoài class không gọi được). Thêm 2 dòng `#define private public` và `#define protected public` **sau** `#include "gtest/gtest.h"` và **trước** các `#include` của Ceres.
- Đây là method của class `ceres::internal::SparseSchurComplementSolver`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `SparseSchurComplementSolver`:
Các constructor:
```cpp
  SparseSchurComplementSolver(const LinearSolver::Options & options)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1141_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
