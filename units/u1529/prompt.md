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

- Hàm: `CreateGradientCheckingProblemImpl(ProblemImpl * problem_impl, double relative_step_size, double relative_precision, GradientCheckingIterationCallback * callback)`, trả về `std::unique_ptr<ProblemImpl>`
- Loại: hàm tự do (không thuộc class)
- Namespace: `ceres::internal`
- Vị trí: `internal/ceres/gradient_checking_cost_function.cc`, dòng 168–278

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
168 | std::unique_ptr<ProblemImpl> CreateGradientCheckingProblemImpl(
169 |     ProblemImpl* problem_impl,
170 |     double relative_step_size,
171 |     double relative_precision,
172 |     GradientCheckingIterationCallback* callback) {
173 |   CHECK(callback != nullptr);
174 |   // We create new CostFunctions by wrapping the original CostFunction in a
175 |   // gradient checking CostFunction. So its okay for the ProblemImpl to take
176 |   // ownership of it and destroy it. The LossFunctions and Manifolds are reused
177 |   // and since they are owned by problem_impl, gradient_checking_problem_impl
178 |   // should not take ownership of it.
179 |   Problem::Options gradient_checking_problem_options;
180 |   gradient_checking_problem_options.cost_function_ownership = TAKE_OWNERSHIP;
181 |   gradient_checking_problem_options.loss_function_ownership =
182 |       DO_NOT_TAKE_OWNERSHIP;
183 |   gradient_checking_problem_options.manifold_ownership = DO_NOT_TAKE_OWNERSHIP;
184 |   gradient_checking_problem_options.context = problem_impl->context();
185 | 
186 |   NumericDiffOptions numeric_diff_options;
187 |   numeric_diff_options.relative_step_size = relative_step_size;
188 | 
189 |   auto gradient_checking_problem_impl =
190 |       std::make_unique<ProblemImpl>(gradient_checking_problem_options);
191 | 
192 |   Program* program = problem_impl->mutable_program();
193 | 
194 |   // For every ParameterBlock in problem_impl, create a new parameter block with
195 |   // the same manifold and constancy.
196 |   const std::vector<ParameterBlock*>& parameter_blocks =
197 |       program->parameter_blocks();
198 |   for (auto* parameter_block : parameter_blocks) {
199 |     gradient_checking_problem_impl->AddParameterBlock(
200 |         parameter_block->mutable_user_state(),
201 |         parameter_block->Size(),
202 |         parameter_block->mutable_manifold());
203 | 
204 |     if (parameter_block->IsConstant()) {
205 |       gradient_checking_problem_impl->SetParameterBlockConstant(
206 |           parameter_block->mutable_user_state());
207 |     }
208 | 
209 |     for (int i = 0; i < parameter_block->Size(); ++i) {
210 |       gradient_checking_problem_impl->SetParameterUpperBound(
211 |           parameter_block->mutable_user_state(),
212 |           i,
213 |           parameter_block->UpperBound(i));
214 |       gradient_checking_problem_impl->SetParameterLowerBound(
215 |           parameter_block->mutable_user_state(),
216 |           i,
217 |           parameter_block->LowerBound(i));
218 |     }
219 |   }
220 | 
221 |   // For every ResidualBlock in problem_impl, create a new
222 |   // ResidualBlock by wrapping its CostFunction inside a
223 |   // GradientCheckingCostFunction.
224 |   const std::vector<ResidualBlock*>& residual_blocks =
225 |       program->residual_blocks();
226 |   for (int i = 0; i < residual_blocks.size(); ++i) {
227 |     ResidualBlock* residual_block = residual_blocks[i];
228 | 
229 |     // Build a human readable string which identifies the
230 |     // ResidualBlock. This is used by the GradientCheckingCostFunction
231 |     // when logging debugging information.
232 |     std::string extra_info =
233 |         StringPrintf("Residual block id %d; depends on parameters [", i);
234 |     std::vector<double*> parameter_blocks;
235 |     std::vector<const Manifold*> manifolds;
236 |     parameter_blocks.reserve(residual_block->NumParameterBlocks());
237 |     manifolds.reserve(residual_block->NumParameterBlocks());
238 |     for (int j = 0; j < residual_block->NumParameterBlocks(); ++j) {
239 |       ParameterBlock* parameter_block = residual_block->parameter_blocks()[j];
240 |       parameter_blocks.push_back(parameter_block->mutable_user_state());
241 |       StringAppendF(&extra_info, "%p", parameter_block->mutable_user_state());
242 |       extra_info += (j < residual_block->NumParameterBlocks() - 1) ? ", " : "]";
243 |       manifolds.push_back(
244 |           problem_impl->GetManifold(parameter_block->mutable_user_state()));
245 |     }
246 | 
247 |     // Wrap the original CostFunction in a GradientCheckingCostFunction.
248 |     CostFunction* gradient_checking_cost_function =
249 |         new GradientCheckingCostFunction(residual_block->cost_function(),
250 |                                          &manifolds,
251 |                                          numeric_diff_options,
252 |                                          relative_precision,
253 |                                          extra_info,
254 |                                          callback);
255 | 
256 |     // The const_cast is necessary because
257 |     // ProblemImpl::AddResidualBlock can potentially take ownership of
258 |     // the LossFunction, but in this case we are guaranteed that this
259 |     // will not be the case, so this const_cast is harmless.
260 |     gradient_checking_problem_impl->AddResidualBlock(
261 |         gradient_checking_cost_function,
262 |         const_cast<LossFunction*>(residual_block->loss_function()),
263 |         parameter_blocks.data(),
264 |         static_cast<int>(parameter_blocks.size()));
265 |   }
266 | 
267 |   // Normally, when a problem is given to the solver, we guarantee
268 |   // that the state pointers for each parameter block point to the
269 |   // user provided data. Since we are creating this new problem from a
270 |   // problem given to us at an arbitrary stage of the solve, we cannot
271 |   // depend on this being the case, so we explicitly call
272 |   // SetParameterBlockStatePtrsToUserStatePtrs to ensure that this is
273 |   // the case.
274 |   gradient_checking_problem_impl->mutable_program()
275 |       ->SetParameterBlockStatePtrsToUserStatePtrs();
276 | 
277 |   return gradient_checking_problem_impl;
278 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 6 (và 1 lệnh CHECK)

START → 1
1   CHECK(callback != nullptr)                                     đúng → 2   sai → DỪNG
2   for (auto *parameter_block : parameter_blocks)                 đúng → 3   sai → 11
3   auto *parameter_block
    gradient_checking_problem_impl->AddParameterBlock(parameter_block->mutable_user_state(), parameter_block->Size(), parameter_block->mutable_manifold())   → 4
4   if (parameter_block->IsConstant())                             đúng → 5   sai → 6
5   gradient_checking_problem_impl->SetParameterBlockConstant(parameter_block->mutable_user_state())   → 6
6   int i = 0                                                      → 7
7   vòng for, điều kiện: i < parameter_block->Size()               đúng → 8   sai → 10
8   gradient_checking_problem_impl->SetParameterUpperBound(parameter_block->mutable_user_state(), i, parameter_block->UpperBound(i))
    gradient_checking_problem_impl->SetParameterLowerBound(parameter_block->mutable_user_state(), i, parameter_block->LowerBound(i))   → 9
9   ++i                                                            → 7
10  ++ (bước tiếp của vòng for)                                    → 2
11  const std::vector<ResidualBlock *> &residual_blocks = program->residual_blocks()
    int i = 0                                                      → 12
12  vòng for, điều kiện: i < residual_blocks.size()                đúng → 13   sai → 21
13  ResidualBlock *residual_block = residual_blocks[i]
    parameter_blocks.reserve(residual_block->NumParameterBlocks())
    manifolds.reserve(residual_block->NumParameterBlocks())
    int j = 0                                                      → 14
14  vòng for, điều kiện: j < residual_block->NumParameterBlocks()   đúng → 15   sai → 19
15  ParameterBlock *parameter_block = residual_block->parameter_blocks()[j]
    parameter_blocks.push_back(parameter_block->mutable_user_state())
    StringAppendF(&extra_info, "%p", parameter_block->mutable_user_state())   → 16
16  (j < residual_block->NumParameterBlocks() - 1) ? ... : ...     đúng → 17   sai → 17
17  extra_info += (j < residual_block->NumParameterBlocks() - 1) ? ", " : "]"
    manifolds.push_back(problem_impl->GetManifold(parameter_block->mutable_user_state()))   → 18
18  ++j                                                            → 14
19  CFGNewAllocator(GradientCheckingCostFunction *)
    CostFunction *gradient_checking_cost_function = new GradientCheckingCostFunction(residual_block->cost_function(), &manifolds, numeric_diff_options, relative_precision, extra_info, callback)
    gradient_checking_problem_impl->AddResidualBlock(gradient_checking_cost_function, const_cast<LossFunction *>(residual_block->loss_function()) (CXXConstCastExpr, NoOp, LossFunction *), parameter_blocks.data(), static_cast<int>(parameter_blocks.size()))   → 20
20  ++i                                                            → 12
21  gradient_checking_problem_impl->mutable_program()->SetParameterBlockStatePtrsToUserStatePtrs()   → END
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
#include "ceres/cost_function.h"
#include "ceres/loss_function.h"
#include "ceres/manifold.h"
#include "ceres/numeric_diff_options.h"
#include "ceres/problem.h"
#include "ceres/gradient_checking_cost_function.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"
```

- Hàm gọi trực tiếp được.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1529_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
