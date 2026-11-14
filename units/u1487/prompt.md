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

- Hàm: `Minimize(const Minimizer::Options & options, double * parameters, Solver::Summary *)`, trả về `void`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::CoordinateDescentMinimizer`
- Vị trí: `internal/ceres/coordinate_descent_minimizer.cc`, dòng 128–208

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
128 | void CoordinateDescentMinimizer::Minimize(const Minimizer::Options& options,
129 |                                           double* parameters,
130 |                                           Solver::Summary* /*summary*/) {
131 |   // Set the state and mark all parameter blocks constant.
132 |   for (auto* parameter_block : parameter_blocks_) {
133 |     parameter_block->SetState(parameters + parameter_block->state_offset());
134 |     parameter_block->SetConstant();
135 |   }
136 | 
137 |   std::vector<std::unique_ptr<LinearSolver>> linear_solvers(
138 |       options.num_threads);
139 | 
140 |   LinearSolver::Options linear_solver_options;
141 |   linear_solver_options.type = DENSE_QR;
142 |   linear_solver_options.context = context_;
143 | 
144 |   for (int i = 0; i < options.num_threads; ++i) {
145 |     linear_solvers[i] = LinearSolver::Create(linear_solver_options);
146 |   }
147 | 
148 |   for (int i = 0; i < independent_set_offsets_.size() - 1; ++i) {
149 |     const int num_problems =
150 |         independent_set_offsets_[i + 1] - independent_set_offsets_[i];
151 |     // Avoid parallelization overhead call if the set is empty.
152 |     if (num_problems == 0) {
153 |       continue;
154 |     }
155 | 
156 |     const int num_inner_iteration_threads =
157 |         std::min(options.num_threads, num_problems);
158 |     evaluator_options_.num_threads =
159 |         std::max(1, options.num_threads / num_inner_iteration_threads);
160 | 
161 |     // The parameter blocks in each independent set can be optimized
162 |     // in parallel, since they do not co-occur in any residual block.
163 |     ParallelFor(
164 |         context_,
165 |         independent_set_offsets_[i],
166 |         independent_set_offsets_[i + 1],
167 |         num_inner_iteration_threads,
168 |         [&](int thread_id, int j) {
169 |           ParameterBlock* parameter_block = parameter_blocks_[j];
170 |           const int old_index = parameter_block->index();
171 |           const int old_delta_offset = parameter_block->delta_offset();
172 |           const int old_state_offset = parameter_block->state_offset();
173 |           parameter_block->SetVarying();
174 |           parameter_block->set_index(0);
175 |           parameter_block->set_delta_offset(0);
176 |           parameter_block->set_state_offset(0);
177 | 
178 |           Program inner_program;
179 |           inner_program.mutable_parameter_blocks()->push_back(parameter_block);
180 |           *inner_program.mutable_residual_blocks() = residual_blocks_[j];
181 | 
182 |           // TODO(sameeragarwal): Better error handling. Right now we
183 |           // assume that this is not going to lead to problems of any
184 |           // sort. Basically we should be checking for numerical failure
185 |           // of some sort.
186 |           //
187 |           // On the other hand, if the optimization is a failure, that in
188 |           // some ways is fine, since it won't change the parameters and
189 |           // we are fine.
190 |           Solver::Summary inner_summary;
191 |           Solve(&inner_program,
192 |                 linear_solvers[thread_id].get(),
193 |                 parameters + old_state_offset,
194 |                 &inner_summary);
195 | 
196 |           parameter_block->set_index(old_index);
197 |           parameter_block->set_delta_offset(old_delta_offset);
198 |           parameter_block->set_state_offset(old_state_offset);
199 |           parameter_block->SetState(parameters +
200 |                                     parameter_block->state_offset());
201 |           parameter_block->SetConstant();
202 |         });
203 |   }
204 | 
205 |   for (auto* parameter_block : parameter_blocks_) {
206 |     parameter_block->SetVarying();
207 |   }
208 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 5

START → 1
1   for (auto *parameter_block : parameter_blocks_)                đúng → 2   sai → 4
2   auto *parameter_block
    parameter_block->SetState(parameters + parameter_block->state_offset())
    parameter_block->SetConstant()                                 → 3
3   ++ (bước tiếp của vòng for)                                    → 1
4   options.num_threads
    linear_solver_options.type = DENSE_QR
    linear_solver_options.context = context_
    int i = 0                                                      → 5
5   vòng for, điều kiện: i < options.num_threads                   đúng → 6   sai → 8
6   linear_solvers[i] = LinearSolver::Create(linear_solver_options)   → 7
7   ++i                                                            → 5
8   int i = 0                                                      → 9
9   vòng for, điều kiện: i < independent_set_offsets_.size() - 1   đúng → 10   sai → 15
10  const int num_problems = independent_set_offsets_[i + 1] - independent_set_offsets_[i]   → 11
11  if (num_problems == 0)                                         đúng → 12   sai → 14
12  continue                                                       → 13
13  ++i                                                            → 9
14  const int num_inner_iteration_threads = std::min(options.num_threads, num_problems)
    evaluator_options_.num_threads = std::max(1, options.num_threads / num_inner_iteration_threads)
    ParallelFor (ImplicitCastExpr, FunctionToPointerDecay, void (*)(ContextImpl *, int, int, int, class (lambda at /work/ceres-solver/internal/ceres/coordinate_descent_minimizer.cc:168:9) &&, int))(context_, independent_set_offsets_[i], independent_set_offsets_[i + 1], num_inner_iteration_threads, [&](int thread_id, int j) {)   → 13
15  for (auto *parameter_block : parameter_blocks_)                đúng → 16   sai → END
16  auto *parameter_block
    parameter_block->SetVarying()                                  → 17
17  ++ (bước tiếp của vòng for)                                    → 15
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
#include "ceres/solver.h"
#include "ceres/coordinate_descent_minimizer.h"
#include "ceres/linear_solver.h"
#include "ceres/minimizer.h"
#include "ceres/parallel_for.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1487_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
