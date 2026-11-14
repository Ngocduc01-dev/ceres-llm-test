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

- Hàm: `Evaluate(const Evaluator::EvaluateOptions & evaluate_options, const double * state, double * cost, double * residuals, double * gradient, SparseMatrix * jacobian)`, trả về `bool`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::ProgramEvaluator` (class template)
- Vị trí: `internal/ceres/program_evaluator.h`, dòng 134–301

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
134 |   bool Evaluate(const Evaluator::EvaluateOptions& evaluate_options,
135 |                 const double* state,
136 |                 double* cost,
137 |                 double* residuals,
138 |                 double* gradient,
139 |                 SparseMatrix* jacobian) final {
140 |     ScopedExecutionTimer total_timer("Evaluator::Total", &execution_summary_);
141 |     ScopedExecutionTimer call_type_timer(
142 |         gradient == nullptr && jacobian == nullptr ? "Evaluator::Residual"
143 |                                                    : "Evaluator::Jacobian",
144 |         &execution_summary_);
145 | 
146 |     // The parameters are stateful, so set the state before evaluating.
147 |     if (!program_->StateVectorToParameterBlocks(state)) {
148 |       return false;
149 |     }
150 | 
151 |     // Notify the user about a new evaluation point if they are interested.
152 |     if (options_.evaluation_callback != nullptr) {
153 |       program_->CopyParameterBlockStateToUserState();
154 |       options_.evaluation_callback->PrepareForEvaluation(
155 |           /*jacobians=*/(gradient != nullptr || jacobian != nullptr),
156 |           evaluate_options.new_evaluation_point);
157 |     }
158 | 
159 |     if (residuals != nullptr) {
160 |       ParallelSetZero(options_.context,
161 |                       options_.num_threads,
162 |                       residuals,
163 |                       program_->NumResiduals());
164 |     }
165 | 
166 |     if (jacobian != nullptr) {
167 |       jacobian->SetZero(options_.context, options_.num_threads);
168 |     }
169 | 
170 |     // Each thread gets it's own cost and evaluate scratch space.
171 |     for (int i = 0; i < options_.num_threads; ++i) {
172 |       evaluate_scratch_[i].cost = 0.0;
173 |       if (gradient != nullptr) {
174 |         ParallelSetZero(options_.context,
175 |                         options_.num_threads,
176 |                         evaluate_scratch_[i].gradient.get(),
177 |                         num_parameters_);
178 |       }
179 |     }
180 | 
181 |     const int num_residual_blocks = program_->NumResidualBlocks();
182 |     // This bool is used to disable the loop if an error is encountered without
183 |     // breaking out of it. The remaining loop iterations are still run, but with
184 |     // an empty body, and so will finish quickly.
185 |     std::atomic_bool abort(false);
186 |     ParallelFor(
187 |         options_.context,
188 |         0,
189 |         num_residual_blocks,
190 |         options_.num_threads,
191 |         [&](int thread_id, int i) {
192 |           if (abort) {
193 |             return;
194 |           }
195 | 
196 |           EvaluatePreparer* preparer = &evaluate_preparers_[thread_id];
197 |           EvaluateScratch* scratch = &evaluate_scratch_[thread_id];
198 | 
199 |           // Prepare block residuals if requested.
200 |           const ResidualBlock* residual_block = program_->residual_blocks()[i];
201 |           double* block_residuals = nullptr;
202 |           if (residuals != nullptr) {
203 |             block_residuals = residuals + residual_layout_[i];
204 |           } else if (gradient != nullptr) {
205 |             block_residuals = scratch->residual_block_residuals.get();
206 |           }
207 | 
208 |           // Prepare block jacobians if requested.
209 |           double** block_jacobians = nullptr;
210 |           if (jacobian != nullptr || gradient != nullptr) {
211 |             preparer->Prepare(residual_block,
212 |                               i,
213 |                               jacobian,
214 |                               scratch->jacobian_block_ptrs.get());
215 |             block_jacobians = scratch->jacobian_block_ptrs.get();
216 |           }
217 | 
218 |           // Evaluate the cost, residuals, and jacobians.
219 |           double block_cost;
220 |           if (!residual_block->Evaluate(
221 |                   evaluate_options.apply_loss_function,
222 |                   &block_cost,
223 |                   block_residuals,
224 |                   block_jacobians,
225 |                   scratch->residual_block_evaluate_scratch.get())) {
226 |             abort = true;
227 |             return;
228 |           }
229 | 
230 |           scratch->cost += block_cost;
231 | 
232 |           // Store the jacobians, if they were requested.
233 |           if (jacobian != nullptr) {
234 |             jacobian_writer_.Write(
235 |                 i, residual_layout_[i], block_jacobians, jacobian);
236 |           }
237 | 
238 |           // Compute and store the gradient, if it was requested.
239 |           if (gradient != nullptr) {
240 |             int num_residuals = residual_block->NumResiduals();
241 |             int num_parameter_blocks = residual_block->NumParameterBlocks();
242 |             for (int j = 0; j < num_parameter_blocks; ++j) {
243 |               const ParameterBlock* parameter_block =
244 |                   residual_block->parameter_blocks()[j];
245 |               if (parameter_block->IsConstant()) {
246 |                 continue;
247 |               }
248 | 
249 |               MatrixTransposeVectorMultiply<Eigen::Dynamic, Eigen::Dynamic, 1>(
250 |                   block_jacobians[j],
251 |                   num_residuals,
252 |                   parameter_block->TangentSize(),
253 |                   block_residuals,
254 |                   scratch->gradient.get() + parameter_block->delta_offset());
255 |             }
256 |           }
257 |         });
258 | 
259 |     if (abort) {
260 |       return false;
261 |     }
262 | 
263 |     // Sum the cost and gradient (if requested) from each thread.
264 |     (*cost) = 0.0;
265 |     if (gradient != nullptr) {
266 |       auto gradient_vector = VectorRef(gradient, num_parameters_);
267 |       ParallelSetZero(options_.context, options_.num_threads, gradient_vector);
268 |     }
269 | 
270 |     for (int i = 0; i < options_.num_threads; ++i) {
271 |       (*cost) += evaluate_scratch_[i].cost;
272 |       if (gradient != nullptr) {
273 |         auto gradient_vector = VectorRef(gradient, num_parameters_);
274 |         ParallelAssign(
275 |             options_.context,
276 |             options_.num_threads,
277 |             gradient_vector,
278 |             gradient_vector + VectorRef(evaluate_scratch_[i].gradient.get(),
279 |                                         num_parameters_));
280 |       }
281 |     }
282 | 
283 |     // It is possible that after accumulation that the cost has become infinite
284 |     // or a nan.
285 |     if (!std::isfinite(*cost)) {
286 |       LOG(ERROR) << "Accumulated cost = " << *cost
287 |                  << " is not a finite number. Evaluation failed.";
288 |       return false;
289 |     }
290 | 
291 |     // Finalize the Jacobian if it is available.
292 |     // `num_parameters` is passed to the finalizer so that additional
293 |     // storage can be reserved for additional diagonal elements if
294 |     // necessary.
295 |     if (jacobian != nullptr) {
296 |       JacobianFinalizer f;
297 |       f(jacobian, num_parameters_);
298 |     }
299 | 
300 |     return true;
301 |   }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Ghi chú: đây là template – một số kiểu dữ liệu còn để trống, chỉ được điền khi dùng. CFG dưới đây dựng cho trường hợp ProgramEvaluator<ScratchEvaluatePreparer, DenseJacobianWriter>.

Số điểm rẽ nhánh: 13

START → 1
1   gradient == nullptr && jacobian == nullptr ? ... : ...         đúng → 2   sai → 2
2   if (!program_->StateVectorToParameterBlocks(state))            đúng → 3   sai → 4
3   return false                                                   → END
4   if (options_.evaluation_callback != nullptr)                   đúng → 5   sai → 7
5   program_->CopyParameterBlockStateToUserState()                 → 6
6   options_.evaluation_callback->PrepareForEvaluation((gradient != nullptr || jacobian != nullptr), evaluate_options.new_evaluation_point)   → 7
7   if (residuals != nullptr)                                      đúng → 8   sai → 9
8   ParallelSetZero(options_.context, options_.num_threads, residuals, program_->NumResiduals())   → 9
9   if (jacobian != nullptr)                                       đúng → 10   sai → 11
10  jacobian->SetZero(options_.context, options_.num_threads)      → 11
11  int i = 0                                                      → 12
12  vòng for, điều kiện: i < options_.num_threads                  đúng → 13   sai → 17
13  evaluate_scratch_[i].cost = 0.                                 → 14
14  if (gradient != nullptr)                                       đúng → 15   sai → 16
15  ParallelSetZero(options_.context, options_.num_threads, evaluate_scratch_[i].gradient.get(), num_parameters_)   → 16
16  ++i                                                            → 12
17  const int num_residual_blocks = program_->NumResidualBlocks()
    ParallelFor (ImplicitCastExpr, FunctionToPointerDecay, void (*)(ContextImpl *, int, int, int, class (lambda at /work/ceres-solver/internal/ceres/program_evaluator.h:191:9) &&, int))(options_.context, 0, num_residual_blocks, options_.num_threads, [&](int thread_id, int i) {)   → 18
18  if (abort)                                                     đúng → 19   sai → 20
19  return false                                                   → END
20  (*cost) = 0.                                                   → 21
21  if (gradient != nullptr)                                       đúng → 22   sai → 23
22  VectorRef(gradient, num_parameters_)
    ParallelSetZero(options_.context, options_.num_threads, gradient_vector)   → 23
23  int i = 0                                                      → 24
24  vòng for, điều kiện: i < options_.num_threads                  đúng → 25   sai → 29
25  (*cost) += evaluate_scratch_[i].cost                           → 26
26  if (gradient != nullptr)                                       đúng → 27   sai → 28
27  VectorRef(gradient, num_parameters_)
    ParallelAssign(options_.context, options_.num_threads, gradient_vector, gradient_vector + VectorRef(evaluate_scratch_[i].gradient.get(), num_parameters_))   → 28
28  ++i                                                            → 24
29  if (!std::isfinite(*cost))                                     đúng → END   sai → 30
30  if (jacobian != nullptr)                                       đúng → 31   sai → 32
31  f(jacobian, num_parameters_)                                   → 32
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
#include "ceres/evaluation_callback.h"
#include "ceres/evaluator.h"
#include "ceres/execution_summary.h"
#include "ceres/parallel_vector_ops.h"
#include "ceres/parameter_block.h"
#include "ceres/program_evaluator.h"
#include "ceres/residual_block.h"
#include "ceres/sparse_matrix.h"
```

- Đây là method của class `ceres::internal::ProgramEvaluator`: tạo một object của class rồi gọi method trên object đó.
- Đây là template (khuôn mẫu): khi tạo object hoặc gọi hàm phải chọn kiểu cụ thể phù hợp.

Cách tạo object của class `ProgramEvaluator`:
Các constructor:
```cpp
  ProgramEvaluator(const Evaluator::Options & options, Program * program)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1492_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
