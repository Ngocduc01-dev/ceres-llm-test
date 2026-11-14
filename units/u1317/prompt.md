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

- Hàm: `BuildJacobianLayout(const Program & program, int num_eliminate_blocks, std::vector<int *> * jacobian_layout, std::vector<int> * jacobian_layout_storage)`, trả về `bool`
- Loại: hàm tự do (không thuộc class)
- Namespace: `ceres::internal::(namespace không tên)`
- Vị trí: `internal/ceres/block_jacobian_writer.cc`, dòng 66–165

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
 66 | bool BuildJacobianLayout(const Program& program,
 67 |                          int num_eliminate_blocks,
 68 |                          std::vector<int*>* jacobian_layout,
 69 |                          std::vector<int>* jacobian_layout_storage) {
 70 |   const std::vector<ResidualBlock*>& residual_blocks =
 71 |       program.residual_blocks();
 72 | 
 73 |   // Iterate over all the active residual blocks and determine how many E blocks
 74 |   // are there. This will determine where the F blocks start in the jacobian
 75 |   // matrix. Also compute the number of jacobian blocks.
 76 |   unsigned int f_block_pos = 0;
 77 |   unsigned int num_jacobian_blocks = 0;
 78 |   for (auto* residual_block : residual_blocks) {
 79 |     const int num_residuals = residual_block->NumResiduals();
 80 |     const int num_parameter_blocks = residual_block->NumParameterBlocks();
 81 | 
 82 |     // Advance f_block_pos over each E block for this residual.
 83 |     for (int j = 0; j < num_parameter_blocks; ++j) {
 84 |       ParameterBlock* parameter_block = residual_block->parameter_blocks()[j];
 85 |       if (!parameter_block->IsConstant()) {
 86 |         // Only count blocks for active parameters.
 87 |         num_jacobian_blocks++;
 88 |         if (parameter_block->index() < num_eliminate_blocks) {
 89 |           f_block_pos += num_residuals * parameter_block->TangentSize();
 90 |         }
 91 |       }
 92 |     }
 93 |     if (num_jacobian_blocks > std::numeric_limits<int>::max()) {
 94 |       LOG(ERROR) << "Overlow error. Too many blocks in the jacobian matrix : "
 95 |                  << num_jacobian_blocks;
 96 |       return false;
 97 |     }
 98 |   }
 99 | 
100 |   // We now know that the E blocks are laid out starting at zero, and the F
101 |   // blocks are laid out starting at f_block_pos. Iterate over the residual
102 |   // blocks again, and this time fill the jacobian_layout array with the
103 |   // position information.
104 | 
105 |   jacobian_layout->resize(program.NumResidualBlocks());
106 |   jacobian_layout_storage->resize(num_jacobian_blocks);
107 | 
108 |   int e_block_pos = 0;
109 |   int* jacobian_pos = jacobian_layout_storage->data();
110 |   std::vector<std::pair<int, int>> active_parameter_blocks;
111 |   for (int i = 0; i < residual_blocks.size(); ++i) {
112 |     const ResidualBlock* residual_block = residual_blocks[i];
113 |     const int num_residuals = residual_block->NumResiduals();
114 |     const int num_parameter_blocks = residual_block->NumParameterBlocks();
115 | 
116 |     (*jacobian_layout)[i] = jacobian_pos;
117 |     // Cells from F sub-matrix are to be stored sequentially with increasing
118 |     // column block id. For each non-constant parameter block, a pair of indices
119 |     // (index in the list of active parameter blocks and index in the list of
120 |     // all parameter blocks) is computed, and index pairs are sorted by the
121 |     // index of corresponding column block id.
122 |     active_parameter_blocks.clear();
123 |     active_parameter_blocks.reserve(num_parameter_blocks);
124 |     for (int j = 0; j < num_parameter_blocks; ++j) {
125 |       ParameterBlock* parameter_block = residual_block->parameter_blocks()[j];
126 |       if (parameter_block->IsConstant()) {
127 |         continue;
128 |       }
129 |       const int k = active_parameter_blocks.size();
130 |       active_parameter_blocks.emplace_back(k, j);
131 |     }
132 |     std::sort(active_parameter_blocks.begin(),
133 |               active_parameter_blocks.end(),
134 |               [&residual_block](const std::pair<int, int>& a,
135 |                                 const std::pair<int, int>& b) {
136 |                 return residual_block->parameter_blocks()[a.second]->index() <
137 |                        residual_block->parameter_blocks()[b.second]->index();
138 |               });
139 |     // Cell positions for each active parameter block are filled in the order of
140 |     // active parameter block indices sorted by columnd block index. This
141 |     // guarantees that cells are laid out sequentially with increasing column
142 |     // block indices.
143 |     for (const auto& indices : active_parameter_blocks) {
144 |       const auto [k, j] = indices;
145 |       ParameterBlock* parameter_block = residual_block->parameter_blocks()[j];
146 |       const int parameter_block_index = parameter_block->index();
147 |       const int jacobian_block_size =
148 |           num_residuals * parameter_block->TangentSize();
149 |       if (parameter_block_index < num_eliminate_blocks) {
150 |         jacobian_pos[k] = e_block_pos;
151 |         e_block_pos += jacobian_block_size;
152 |       } else {
153 |         jacobian_pos[k] = static_cast<int>(f_block_pos);
154 |         f_block_pos += jacobian_block_size;
155 |         if (f_block_pos > std::numeric_limits<int>::max()) {
156 |           LOG(ERROR)
157 |               << "Overlow error. Too many entries in the Jacobian matrix.";
158 |           return false;
159 |         }
160 |       }
161 |     }
162 |     jacobian_pos += active_parameter_blocks.size();
163 |   }
164 |   return true;
165 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 11

START → 1
1   const std::vector<ResidualBlock *> &residual_blocks = program.residual_blocks()
    unsigned int f_block_pos = 0
    unsigned int num_jacobian_blocks = 0                           → 2
2   for (auto *residual_block : residual_blocks)                   đúng → 3   sai → 13
3   auto *residual_block
    const int num_residuals = residual_block->NumResiduals()
    const int num_parameter_blocks = residual_block->NumParameterBlocks()
    int j = 0                                                      → 4
4   vòng for, điều kiện: j < num_parameter_blocks                  đúng → 5   sai → 11
5   ParameterBlock *parameter_block = residual_block->parameter_blocks()[j]   → 6
6   if (!parameter_block->IsConstant())                            đúng → 7   sai → 10
7   num_jacobian_blocks++                                          → 8
8   if (parameter_block->index() < num_eliminate_blocks)           đúng → 9   sai → 10
9   f_block_pos += num_residuals * parameter_block->TangentSize()   → 10
10  ++j                                                            → 4
11  if (num_jacobian_blocks > std::numeric_limits<int>::max())     đúng → END   sai → 12
12  ++ (bước tiếp của vòng for)                                    → 2
13  jacobian_layout->resize(program.NumResidualBlocks())
    jacobian_layout_storage->resize(num_jacobian_blocks)
    int e_block_pos = 0
    int *jacobian_pos = jacobian_layout_storage->data()
    int i = 0                                                      → 14
14  vòng for, điều kiện: i < residual_blocks.size()                đúng → 15   sai → 32
15  const ResidualBlock *residual_block = residual_blocks[i]
    const int num_residuals = residual_block->NumResiduals()
    const int num_parameter_blocks = residual_block->NumParameterBlocks()
    (*jacobian_layout)[i] = jacobian_pos
    active_parameter_blocks.clear()
    active_parameter_blocks.reserve(num_parameter_blocks)
    int j = 0                                                      → 16
16  vòng for, điều kiện: j < num_parameter_blocks                  đúng → 17   sai → 22
17  ParameterBlock *parameter_block = residual_block->parameter_blocks()[j]   → 18
18  if (parameter_block->IsConstant())                             đúng → 19   sai → 21
19  continue                                                       → 20
20  ++j                                                            → 16
21  const int k = active_parameter_blocks.size()
    active_parameter_blocks.emplace_back(k, j)                     → 20
22  residual_block                                                 → 23
23  for (const auto &indices : active_parameter_blocks)            đúng → 24   sai → 30
24  const auto &indices
    get<0UL>(?)
    std::tuple_element<0, const std::pair<int, int>>::type k = get<0UL>()
    get<1UL>(?)
    std::tuple_element<1, const std::pair<int, int>>::type j = get<1UL>()
    ParameterBlock *parameter_block = residual_block->parameter_blocks()[j]
    const int parameter_block_index = parameter_block->index()
    const int jacobian_block_size = num_residuals * parameter_block->TangentSize()   → 25
25  if (parameter_block_index < num_eliminate_blocks)              đúng → 26   sai → 28
26  jacobian_pos[k] = e_block_pos
    e_block_pos += jacobian_block_size                             → 27
27  ++ (bước tiếp của vòng for)                                    → 23
28  jacobian_pos[k] = static_cast<int>(f_block_pos)
    f_block_pos += jacobian_block_size                             → 29
29  if (f_block_pos > std::numeric_limits<int>::max())             đúng → END   sai → 27
30  jacobian_pos += active_parameter_blocks.size()                 → 31
31  ++i                                                            → 14
32  return true                                                    → END
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
#include "ceres/parameter_block.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"
#include "ceres/block_jacobian_writer.cc"
```

- Hàm này chỉ dùng được bên trong file `internal/ceres/block_jacobian_writer.cc` (khai báo `static` hoặc trong namespace không tên). Để gọi được, thêm `#include "ceres/block_jacobian_writer.cc"` vào file test.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1317_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
