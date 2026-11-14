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

- Hàm: `Init(const Program & program, const ProblemImpl::ParameterMap & parameter_map, const ParameterBlockOrdering & ordering, std::string *)`, trả về `bool`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::CoordinateDescentMinimizer`
- Vị trí: `internal/ceres/coordinate_descent_minimizer.cc`, dòng 64–126

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
 64 | bool CoordinateDescentMinimizer::Init(
 65 |     const Program& program,
 66 |     const ProblemImpl::ParameterMap& parameter_map,
 67 |     const ParameterBlockOrdering& ordering,
 68 |     std::string* /*error*/) {
 69 |   parameter_blocks_.clear();
 70 |   independent_set_offsets_.clear();
 71 |   independent_set_offsets_.push_back(0);
 72 | 
 73 |   // Serialize the OrderedGroups into a vector of parameter block
 74 |   // offsets for parallel access.
 75 | 
 76 |   // TODO(sameeragarwal): Investigate if parameter_block_index should be an
 77 |   // ordered or an unordered container.
 78 |   std::map<ParameterBlock*, int> parameter_block_index;
 79 |   std::map<int, std::set<double*>> group_to_elements =
 80 |       ordering.group_to_elements();
 81 |   for (const auto& g_t_e : group_to_elements) {
 82 |     const auto& elements = g_t_e.second;
 83 |     for (double* parameter_block : elements) {
 84 |       parameter_blocks_.push_back(parameter_map.find(parameter_block)->second);
 85 |       parameter_block_index[parameter_blocks_.back()] =
 86 |           parameter_blocks_.size() - 1;
 87 |     }
 88 |     independent_set_offsets_.push_back(independent_set_offsets_.back() +
 89 |                                        elements.size());
 90 |   }
 91 | 
 92 |   // The ordering does not have to contain all parameter blocks, so
 93 |   // assign zero offsets/empty independent sets to these parameter
 94 |   // blocks.
 95 |   const std::vector<ParameterBlock*>& parameter_blocks =
 96 |       program.parameter_blocks();
 97 |   for (auto* parameter_block : parameter_blocks) {
 98 |     if (!ordering.IsMember(parameter_block->mutable_user_state())) {
 99 |       parameter_blocks_.push_back(parameter_block);
100 |       independent_set_offsets_.push_back(independent_set_offsets_.back());
101 |     }
102 |   }
103 | 
104 |   // Compute the set of residual blocks that depend on each parameter
105 |   // block.
106 |   residual_blocks_.resize(parameter_block_index.size());
107 |   const std::vector<ResidualBlock*>& residual_blocks =
108 |       program.residual_blocks();
109 |   for (auto* residual_block : residual_blocks) {
110 |     const int num_parameter_blocks = residual_block->NumParameterBlocks();
111 |     for (int j = 0; j < num_parameter_blocks; ++j) {
112 |       ParameterBlock* parameter_block = residual_block->parameter_blocks()[j];
113 |       const auto it = parameter_block_index.find(parameter_block);
114 |       if (it != parameter_block_index.end()) {
115 |         residual_blocks_[it->second].push_back(residual_block);
116 |       }
117 |     }
118 |   }
119 | 
120 |   evaluator_options_.linear_solver_type = DENSE_QR;
121 |   evaluator_options_.num_eliminate_blocks = 0;
122 |   evaluator_options_.num_threads = 1;
123 |   evaluator_options_.context = context_;
124 | 
125 |   return true;
126 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 7

START → 1
1   parameter_blocks_.clear()
    independent_set_offsets_.clear()
    independent_set_offsets_.push_back(0)
    ordering.group_to_elements()                                   → 2
2   for (const auto &g_t_e : group_to_elements)                    đúng → 3   sai → 9
3   const auto &g_t_e
    const auto &elements = g_t_e.second                            → 4
4   for (double *parameter_block : elements)                       đúng → 5   sai → 7
5   double *parameter_block
    parameter_blocks_.push_back(parameter_map.find(parameter_block)->second)
    parameter_block_index[parameter_blocks_.back()] = parameter_blocks_.size() - 1   → 6
6   ++ (bước tiếp của vòng for)                                    → 4
7   independent_set_offsets_.push_back(independent_set_offsets_.back() + elements.size())   → 8
8   ++ (bước tiếp của vòng for)                                    → 2
9   const std::vector<ParameterBlock *> &parameter_blocks = program.parameter_blocks()   → 10
10  for (auto *parameter_block : parameter_blocks)                 đúng → 11   sai → 15
11  auto *parameter_block                                          → 12
12  if (!ordering.IsMember(parameter_block->mutable_user_state()))   đúng → 13   sai → 14
13  parameter_blocks_.push_back(parameter_block)
    independent_set_offsets_.push_back(independent_set_offsets_.back())   → 14
14  ++ (bước tiếp của vòng for)                                    → 10
15  residual_blocks_.resize(parameter_block_index.size())
    const std::vector<ResidualBlock *> &residual_blocks = program.residual_blocks()   → 16
16  for (auto *residual_block : residual_blocks)                   đúng → 17   sai → 24
17  auto *residual_block
    const int num_parameter_blocks = residual_block->NumParameterBlocks()
    int j = 0                                                      → 18
18  vòng for, điều kiện: j < num_parameter_blocks                  đúng → 19   sai → 23
19  ParameterBlock *parameter_block = residual_block->parameter_blocks()[j]
    parameter_block_index.find(parameter_block)                    → 20
20  if (it != parameter_block_index.end())                         đúng → 21   sai → 22
21  residual_blocks_[it->second].push_back(residual_block)         → 22
22  ++j                                                            → 18
23  ++ (bước tiếp của vòng for)                                    → 16
24  evaluator_options_.linear_solver_type = DENSE_QR
    evaluator_options_.num_eliminate_blocks = 0
    evaluator_options_.num_threads = 1
    evaluator_options_.context = context_
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
#include "ceres/ordered_groups.h"
#include "ceres/coordinate_descent_minimizer.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"
```

- Đây là method của class `ceres::internal::CoordinateDescentMinimizer`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `CoordinateDescentMinimizer`:
Các constructor:
```cpp
  CoordinateDescentMinimizer(ContextImpl * context)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1301_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
