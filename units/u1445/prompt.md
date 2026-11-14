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

- Hàm: `CreateJacobian() const`, trả về `std::unique_ptr<SparseMatrix>`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::CompressedRowJacobianWriter`
- Vị trí: `internal/ceres/compressed_row_jacobian_writer.cc`, dòng 89–199

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
 89 | std::unique_ptr<SparseMatrix> CompressedRowJacobianWriter::CreateJacobian()
 90 |     const {
 91 |   const auto& residual_blocks = program_->residual_blocks();
 92 | 
 93 |   const int total_num_residuals = program_->NumResiduals();
 94 |   const int total_num_effective_parameters = program_->NumEffectiveParameters();
 95 | 
 96 |   // Count the number of jacobian nonzeros.
 97 |   //
 98 |   // We used an unsigned int here, so that we can compare it INT_MAX without
 99 |   // triggering overflow behaviour.
100 |   unsigned int num_jacobian_nonzeros = total_num_effective_parameters;
101 |   for (auto* residual_block : residual_blocks) {
102 |     const int num_residuals = residual_block->NumResiduals();
103 |     const int num_parameter_blocks = residual_block->NumParameterBlocks();
104 |     for (int j = 0; j < num_parameter_blocks; ++j) {
105 |       auto parameter_block = residual_block->parameter_blocks()[j];
106 |       if (!parameter_block->IsConstant()) {
107 |         num_jacobian_nonzeros += num_residuals * parameter_block->TangentSize();
108 |         if (num_jacobian_nonzeros > std::numeric_limits<int>::max()) {
109 |           LOG(ERROR) << "Unable to create Jacobian matrix: Too many entries in "
110 |                         "the Jacobian matrix. num_jacobian_nonzeros = "
111 |                      << num_jacobian_nonzeros;
112 |           return nullptr;
113 |         }
114 |       }
115 |     }
116 |   }
117 | 
118 |   // Allocate storage for the jacobian with some extra space at the end.
119 |   // Allocate more space than needed to store the jacobian so that when the LM
120 |   // algorithm adds the diagonal, no reallocation is necessary. This reduces
121 |   // peak memory usage significantly.
122 |   auto jacobian = std::make_unique<CompressedRowSparseMatrix>(
123 |       total_num_residuals,
124 |       total_num_effective_parameters,
125 |       static_cast<int>(num_jacobian_nonzeros));
126 | 
127 |   // At this stage, the CompressedRowSparseMatrix is an invalid state. But
128 |   // this seems to be the only way to construct it without doing a memory
129 |   // copy.
130 |   int* rows = jacobian->mutable_rows();
131 |   int* cols = jacobian->mutable_cols();
132 | 
133 |   int row_pos = 0;
134 |   rows[0] = 0;
135 |   for (auto* residual_block : residual_blocks) {
136 |     const int num_parameter_blocks = residual_block->NumParameterBlocks();
137 | 
138 |     // Count the number of derivatives for a row of this residual block and
139 |     // build a list of active parameter block indices.
140 |     int num_derivatives = 0;
141 |     std::vector<int> parameter_indices;
142 |     for (int j = 0; j < num_parameter_blocks; ++j) {
143 |       auto parameter_block = residual_block->parameter_blocks()[j];
144 |       if (!parameter_block->IsConstant()) {
145 |         parameter_indices.push_back(parameter_block->index());
146 |         num_derivatives += parameter_block->TangentSize();
147 |       }
148 |     }
149 | 
150 |     // Sort the parameters by their position in the state vector.
151 |     std::sort(parameter_indices.begin(), parameter_indices.end());
152 |     if (adjacent_find(parameter_indices.begin(), parameter_indices.end()) !=
153 |         parameter_indices.end()) {
154 |       std::string parameter_block_description;
155 |       for (int j = 0; j < num_parameter_blocks; ++j) {
156 |         auto parameter_block = residual_block->parameter_blocks()[j];
157 |         parameter_block_description += parameter_block->ToString() + "\n";
158 |       }
159 |       LOG(FATAL) << "Ceres internal error: "
160 |                  << "Duplicate parameter blocks detected in a cost function. "
161 |                  << "This should never happen. Please report this to "
162 |                  << "the Ceres developers.\n"
163 |                  << "Residual Block: " << residual_block->ToString() << "\n"
164 |                  << "Parameter Blocks: " << parameter_block_description;
165 |     }
166 | 
167 |     // Update the row indices.
168 |     const int num_residuals = residual_block->NumResiduals();
169 |     for (int j = 0; j < num_residuals; ++j) {
170 |       rows[row_pos + j + 1] = rows[row_pos + j] + num_derivatives;
171 |     }
172 | 
173 |     // Iterate over parameter blocks in the order which they occur in the
174 |     // parameter vector. This code mirrors that in Write(), where jacobian
175 |     // values are updated.
176 |     int col_pos = 0;
177 |     for (int parameter_index : parameter_indices) {
178 |       auto parameter_block = program_->parameter_blocks()[parameter_index];
179 |       const int parameter_block_size = parameter_block->TangentSize();
180 | 
181 |       for (int r = 0; r < num_residuals; ++r) {
182 |         // This is the position in the values array of the jacobian where this
183 |         // row of the jacobian block should go.
184 |         const int column_block_begin = rows[row_pos + r] + col_pos;
185 |         for (int c = 0; c < parameter_block_size; ++c) {
186 |           cols[column_block_begin + c] = parameter_block->delta_offset() + c;
187 |         }
188 |       }
189 |       col_pos += parameter_block_size;
190 |     }
191 |     row_pos += num_residuals;
192 |   }
193 |   CHECK_EQ(num_jacobian_nonzeros - total_num_effective_parameters,
194 |            rows[total_num_residuals]);
195 | 
196 |   PopulateJacobianRowAndColumnBlockVectors(program_, jacobian.get());
197 | 
198 |   return jacobian;
199 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 12 (và 2 lệnh CHECK)

START → 1
1   const auto &residual_blocks = program_->residual_blocks()
    const int total_num_residuals = program_->NumResiduals()
    const int total_num_effective_parameters = program_->NumEffectiveParameters()
    unsigned int num_jacobian_nonzeros = total_num_effective_parameters   → 2
2   for (auto *residual_block : residual_blocks)                   đúng → 3   sai → 11
3   auto *residual_block
    const int num_residuals = residual_block->NumResiduals()
    const int num_parameter_blocks = residual_block->NumParameterBlocks()
    int j = 0                                                      → 4
4   vòng for, điều kiện: j < num_parameter_blocks                  đúng → 5   sai → 10
5   auto parameter_block = residual_block->parameter_blocks()[j]   → 6
6   if (!parameter_block->IsConstant())                            đúng → 7   sai → 9
7   num_jacobian_nonzeros += num_residuals * parameter_block->TangentSize()   → 8
8   if (num_jacobian_nonzeros > std::numeric_limits<int>::max())   đúng → END   sai → 9
9   ++j                                                            → 4
10  ++ (bước tiếp của vòng for)                                    → 2
11  int *rows = jacobian->mutable_rows()
    int *cols = jacobian->mutable_cols()
    int row_pos = 0
    rows[0] = 0                                                    → 12
12  for (auto *residual_block : residual_blocks)                   đúng → 13   sai → 41
13  auto *residual_block
    const int num_parameter_blocks = residual_block->NumParameterBlocks()
    int num_derivatives = 0
    int j = 0                                                      → 14
14  vòng for, điều kiện: j < num_parameter_blocks                  đúng → 15   sai → 19
15  auto parameter_block = residual_block->parameter_blocks()[j]   → 16
16  if (!parameter_block->IsConstant())                            đúng → 17   sai → 18
17  parameter_indices.push_back(parameter_block->index())
    num_derivatives += parameter_block->TangentSize()              → 18
18  ++j                                                            → 14
19  if (adjacent_find(parameter_indices.begin(), parameter_indices.end()) != parameter_indices.end())   đúng → 20   sai → 24
20  int j = 0                                                      → 21
21  LOG(FATAL)                                                     đúng → 22   sai → DỪNG
22  auto parameter_block = residual_block->parameter_blocks()[j]
    parameter_block_description += parameter_block->ToString() + "\n"   → 23
23  ++j                                                            → 21
24  const int num_residuals = residual_block->NumResiduals()
    int j = 0                                                      → 25
25  vòng for, điều kiện: j < num_residuals                         đúng → 26   sai → 28
26  rows[row_pos + j + 1] = rows[row_pos + j] + num_derivatives    → 27
27  ++j                                                            → 25
28  int col_pos = 0                                                → 29
29  for (int parameter_index : parameter_indices)                  đúng → 30   sai → 39
30  int parameter_index
    auto parameter_block = program_->parameter_blocks()[parameter_index]
    const int parameter_block_size = parameter_block->TangentSize()
    int r = 0                                                      → 31
31  vòng for, điều kiện: r < num_residuals                         đúng → 32   sai → 37
32  const int column_block_begin = rows[row_pos + r] + col_pos
    int c = 0                                                      → 33
33  vòng for, điều kiện: c < parameter_block_size                  đúng → 34   sai → 36
34  cols[column_block_begin + c] = parameter_block->delta_offset() + c   → 35
35  ++c                                                            → 33
36  ++r                                                            → 31
37  col_pos += parameter_block_size                                → 38
38  ++ (bước tiếp của vòng for)                                    → 29
39  row_pos += num_residuals                                       → 40
40  ++ (bước tiếp của vòng for)                                    → 12
41  rows[total_num_residuals])                                     đúng → 42   sai → DỪNG
42  PopulateJacobianRowAndColumnBlockVectors(program_, jacobian.get())   → END
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
#include "ceres/compressed_row_jacobian_writer.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/parameter_block.h"
#include "ceres/residual_block.h"
#include "ceres/sparse_matrix.h"
```

- Đây là method của class `ceres::internal::CompressedRowJacobianWriter`: tạo một object của class rồi gọi method trên object đó.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1445_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
