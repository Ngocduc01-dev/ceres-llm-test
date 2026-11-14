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

- Hàm: `Init(int num_eliminate_blocks, bool assume_full_rank_ete, const CompressedRowBlockStructure * bs)`, trả về `void`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::SchurEliminator` (class template)
- Vị trí: `internal/ceres/schur_eliminator_impl.h`, dòng 79–174

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
 79 | template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
 80 | void SchurEliminator<kRowBlockSize, kEBlockSize, kFBlockSize>::Init(
 81 |     int num_eliminate_blocks,
 82 |     bool assume_full_rank_ete,
 83 |     const CompressedRowBlockStructure* bs) {
 84 |   CHECK_GT(num_eliminate_blocks, 0)
 85 |       << "SchurComplementSolver cannot be initialized with "
 86 |       << "num_eliminate_blocks = 0.";
 87 | 
 88 |   num_eliminate_blocks_ = num_eliminate_blocks;
 89 |   assume_full_rank_ete_ = assume_full_rank_ete;
 90 | 
 91 |   const int num_col_blocks = bs->cols.size();
 92 |   const int num_row_blocks = bs->rows.size();
 93 | 
 94 |   buffer_size_ = 1;
 95 |   chunks_.clear();
 96 |   lhs_row_layout_.clear();
 97 | 
 98 |   int lhs_num_rows = 0;
 99 |   // Add a map object for each block in the reduced linear system
100 |   // and build the row/column block structure of the reduced linear
101 |   // system.
102 |   lhs_row_layout_.resize(num_col_blocks - num_eliminate_blocks_);
103 |   for (int i = num_eliminate_blocks_; i < num_col_blocks; ++i) {
104 |     lhs_row_layout_[i - num_eliminate_blocks_] = lhs_num_rows;
105 |     lhs_num_rows += bs->cols[i].size;
106 |   }
107 | 
108 |   // TODO(sameeragarwal): Now that we may have subset block structure,
109 |   // we need to make sure that we account for the fact that some
110 |   // point blocks only have a "diagonal" row and nothing more.
111 |   //
112 |   // This likely requires a slightly different algorithm, which works
113 |   // off of the number of elimination blocks.
114 | 
115 |   int r = 0;
116 |   // Iterate over the row blocks of A, and detect the chunks. The
117 |   // matrix should already have been ordered so that all rows
118 |   // containing the same y block are vertically contiguous. Along
119 |   // the way also compute the amount of space each chunk will need
120 |   // to perform the elimination.
121 |   while (r < num_row_blocks) {
122 |     const int chunk_block_id = bs->rows[r].cells.front().block_id;
123 |     if (chunk_block_id >= num_eliminate_blocks_) {
124 |       break;
125 |     }
126 | 
127 |     chunks_.push_back(Chunk(r));
128 |     Chunk& chunk = chunks_.back();
129 |     int buffer_size = 0;
130 |     const int e_block_size = bs->cols[chunk_block_id].size;
131 | 
132 |     // Add to the chunk until the first block in the row is
133 |     // different than the one in the first row for the chunk.
134 |     while (r + chunk.size < num_row_blocks) {
135 |       const CompressedRow& row = bs->rows[r + chunk.size];
136 |       if (row.cells.front().block_id != chunk_block_id) {
137 |         break;
138 |       }
139 | 
140 |       // Iterate over the blocks in the row, ignoring the first
141 |       // block since it is the one to be eliminated.
142 |       for (int c = 1; c < row.cells.size(); ++c) {
143 |         const Cell& cell = row.cells[c];
144 |         if (InsertIfNotPresent(
145 |                 &(chunk.buffer_layout), cell.block_id, buffer_size)) {
146 |           buffer_size += e_block_size * bs->cols[cell.block_id].size;
147 |         }
148 |       }
149 | 
150 |       buffer_size_ = std::max(buffer_size, buffer_size_);
151 |       ++chunk.size;
152 |     }
153 | 
154 |     CHECK_GT(chunk.size, 0);  // This check will need to be resolved.
155 |     r += chunk.size;
156 |   }
157 |   const Chunk& chunk = chunks_.back();
158 | 
159 |   uneliminated_row_begins_ = chunk.start + chunk.size;
160 | 
161 |   buffer_ = std::make_unique<double[]>(buffer_size_ * num_threads_);
162 | 
163 |   // chunk_outer_product_buffer_ only needs to store e_block_size *
164 |   // f_block_size, which is always less than buffer_size_, so we just
165 |   // allocate buffer_size_ per thread.
166 |   chunk_outer_product_buffer_ =
167 |       std::make_unique<double[]>(buffer_size_ * num_threads_);
168 | 
169 |   STLDeleteElements(&rhs_locks_);
170 |   rhs_locks_.resize(num_col_blocks - num_eliminate_blocks_);
171 |   for (int i = 0; i < num_col_blocks - num_eliminate_blocks_; ++i) {
172 |     rhs_locks_[i] = new std::mutex;
173 |   }
174 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Ghi chú: đây là template – một số kiểu dữ liệu còn để trống, chỉ được điền khi dùng. CFG dưới đây dựng cho trường hợp SchurEliminator<>.

Số điểm rẽ nhánh: 8 (và 2 lệnh CHECK)

START → 1
1   CHECK_GT(num_eliminate_blocks, 0)                              đúng → 2   sai → DỪNG
2   num_eliminate_blocks_ = num_eliminate_blocks
    assume_full_rank_ete_ = assume_full_rank_ete
    const int num_col_blocks = bs->cols.size()
    const int num_row_blocks = bs->rows.size()
    buffer_size_ = 1
    chunks_.clear()
    lhs_row_layout_.clear()
    int lhs_num_rows = 0
    lhs_row_layout_.resize(num_col_blocks - num_eliminate_blocks_)
    int i = num_eliminate_blocks_                                  → 3
3   vòng for, điều kiện: i < num_col_blocks                        đúng → 4   sai → 6
4   lhs_row_layout_[i - num_eliminate_blocks_] = lhs_num_rows
    lhs_num_rows += bs->cols[i].size                               → 5
5   ++i                                                            → 3
6   int r = 0                                                      → 7
7   while (r < num_row_blocks)                                     đúng → 8   sai → 11
8   const int chunk_block_id = bs->rows[r].cells.front().block_id   → 9
9   if (chunk_block_id >= num_eliminate_blocks_)                   đúng → 10   sai → 15
10  break                                                          → 11
11  const Chunk &chunk = chunks_.back()
    uneliminated_row_begins_ = chunk.start + chunk.size
    chunk_outer_product_buffer_ = std::make_unique<double[]>(buffer_size_ * num_threads_)
    STLDeleteElements(&rhs_locks_)
    rhs_locks_.resize(num_col_blocks - num_eliminate_blocks_)
    int i = 0                                                      → 12
12  vòng for, điều kiện: i < num_col_blocks - num_eliminate_blocks_   đúng → 13   sai → END
13  CFGNewAllocator(std::mutex *)
    rhs_locks_[i] = new std::mutex                                 → 14
14  ++i                                                            → 12
15  chunks_.push_back(Chunk(r))
    Chunk &chunk = chunks_.back()
    int buffer_size = 0
    const int e_block_size = bs->cols[chunk_block_id].size         → 16
16  while (r + chunk.size < num_row_blocks)                        đúng → 17   sai → 20
17  const CompressedRow &row = bs->rows[r + chunk.size]            → 18
18  if (row.cells.front().block_id != chunk_block_id)              đúng → 19   sai → 22
19  break                                                          → 20
20  CHECK_GT(chunk.size, 0); // This check will need to be resolved.   đúng → 21   sai → DỪNG
21  r += chunk.size                                                → 7
22  int c = 1                                                      → 23
23  vòng for, điều kiện: c < row.cells.size()                      đúng → 24   sai → 28
24  const Cell &cell = row.cells[c]                                → 25
25  if (InsertIfNotPresent(&(chunk.buffer_layout), cell.block_id, buffer_size))   đúng → 26   sai → 27
26  buffer_size += e_block_size * bs->cols[cell.block_id].size     → 27
27  ++c                                                            → 23
28  buffer_size_ = std::max(buffer_size, buffer_size_)
    ++chunk.size                                                   → 16
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
#include "ceres/schur_eliminator.h"
#include "ceres/schur_eliminator_impl.h"
#include "ceres/stl_util.h"
```

- Đây là method của class `ceres::internal::SchurEliminator`: tạo một object của class rồi gọi method trên object đó.
- Đây là template (khuôn mẫu): khi tạo object hoặc gọi hàm phải chọn kiểu cụ thể phù hợp.

Cách tạo object của class `SchurEliminator`:
Các constructor:
```cpp
  SchurEliminator(const LinearSolver::Options & options)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u0780_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
