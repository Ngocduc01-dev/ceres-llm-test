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

- Hàm: `SetupLinearSolver(PreprocessedProblem * pp)`, trả về `bool`
- Loại: hàm tự do (không thuộc class)
- Namespace: `ceres::internal::(namespace không tên)`
- Vị trí: `internal/ceres/trust_region_preprocessor.cc`, dòng 157–257

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
157 | bool SetupLinearSolver(PreprocessedProblem* pp) {
158 |   Solver::Options& options = pp->options;
159 |   pp->linear_solver_options = LinearSolver::Options();
160 | 
161 |   if (!options.linear_solver_ordering) {
162 |     // If the user has not supplied a linear solver ordering, then we
163 |     // assume that they are giving all the freedom to us in choosing
164 |     // the best possible ordering. This intent can be indicated by
165 |     // putting all the parameter blocks in the same elimination group.
166 |     options.linear_solver_ordering =
167 |         CreateDefaultLinearSolverOrdering(*pp->reduced_program);
168 |   } else {
169 |     // If the user supplied an ordering, then check if the first
170 |     // elimination group is still non-empty after the reduced problem
171 |     // has been constructed.
172 |     //
173 |     // This is important for Schur type linear solvers, where the
174 |     // first elimination group is special -- it needs to be an
175 |     // independent set.
176 |     //
177 |     // If the first elimination group is empty, then we cannot use the
178 |     // user's requested linear solver (and a preconditioner as the
179 |     // case may be) so we must use a different one.
180 |     ParameterBlockOrdering* ordering = options.linear_solver_ordering.get();
181 |     const int min_group_id = ordering->MinNonZeroGroup();
182 |     ordering->Remove(pp->removed_parameter_blocks);
183 |     if (IsSchurType(options.linear_solver_type) &&
184 |         min_group_id != ordering->MinNonZeroGroup()) {
185 |       AlternateLinearSolverAndPreconditionerForSchurTypeLinearSolver(&options);
186 |     }
187 |   }
188 | 
189 |   // Reorder the program to reduce fill in and improve cache coherency
190 |   // of the Jacobian.
191 |   if (!ReorderProgram(pp)) {
192 |     return false;
193 |   }
194 | 
195 |   // Configure the linear solver.
196 |   pp->linear_solver_options.min_num_iterations =
197 |       options.min_linear_solver_iterations;
198 |   pp->linear_solver_options.max_num_iterations =
199 |       options.max_linear_solver_iterations;
200 |   pp->linear_solver_options.type = options.linear_solver_type;
201 |   pp->linear_solver_options.preconditioner_type = options.preconditioner_type;
202 |   pp->linear_solver_options.use_spse_initialization =
203 |       options.use_spse_initialization;
204 |   pp->linear_solver_options.spse_tolerance = options.spse_tolerance;
205 |   pp->linear_solver_options.max_num_spse_iterations =
206 |       options.max_num_spse_iterations;
207 |   pp->linear_solver_options.visibility_clustering_type =
208 |       options.visibility_clustering_type;
209 |   pp->linear_solver_options.sparse_linear_algebra_library_type =
210 |       options.sparse_linear_algebra_library_type;
211 | 
212 |   pp->linear_solver_options.dense_linear_algebra_library_type =
213 |       options.dense_linear_algebra_library_type;
214 |   pp->linear_solver_options.use_explicit_schur_complement =
215 |       options.use_explicit_schur_complement;
216 |   pp->linear_solver_options.dynamic_sparsity = options.dynamic_sparsity;
217 |   pp->linear_solver_options.use_mixed_precision_solves =
218 |       options.use_mixed_precision_solves;
219 |   pp->linear_solver_options.max_num_refinement_iterations =
220 |       options.max_num_refinement_iterations;
221 |   pp->linear_solver_options.num_threads = options.num_threads;
222 |   pp->linear_solver_options.context = pp->problem->context();
223 | 
224 |   if (IsSchurType(pp->linear_solver_options.type)) {
225 |     OrderingToGroupSizes(options.linear_solver_ordering.get(),
226 |                          &pp->linear_solver_options.elimination_groups);
227 | 
228 |     // Schur type solvers expect at least two elimination groups. If
229 |     // there is only one elimination group, then it is guaranteed that
230 |     // this group only contains e_blocks. Thus we add a dummy
231 |     // elimination group with zero blocks in it.
232 |     if (pp->linear_solver_options.elimination_groups.size() == 1) {
233 |       pp->linear_solver_options.elimination_groups.push_back(0);
234 |     }
235 |   }
236 | 
237 |   if (!options.dynamic_sparsity &&
238 |       AreJacobianColumnsOrdered(options.linear_solver_type,
239 |                                 options.preconditioner_type,
240 |                                 options.sparse_linear_algebra_library_type,
241 |                                 options.linear_solver_ordering_type)) {
242 |     pp->linear_solver_options.ordering_type = OrderingType::NATURAL;
243 |   } else {
244 |     if (options.linear_solver_ordering_type == ceres::AMD) {
245 |       pp->linear_solver_options.ordering_type = OrderingType::AMD;
246 |     } else if (options.linear_solver_ordering_type == ceres::NESDIS) {
247 |       pp->linear_solver_options.ordering_type = OrderingType::NESDIS;
248 |     } else {
249 |       LOG(FATAL) << "Congratulations you have found a bug in Ceres Solver."
250 |                  << " Please report this to the maintainers. : "
251 |                  << options.linear_solver_ordering_type;
252 |     }
253 |   }
254 | 
255 |   pp->linear_solver = LinearSolver::Create(pp->linear_solver_options);
256 |   return (pp->linear_solver != nullptr);
257 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 7 (và 1 lệnh CHECK)

START → 1
1   Solver::Options &options = pp->options
    pp->linear_solver_options = LinearSolver::Options()            → 2
2   if (!options.linear_solver_ordering)                           đúng → 3   sai → 18
3   operator* (ImplicitCastExpr, FunctionToPointerDecay, typename add_lvalue_reference<element_type>::type (*)(void) const noexcept(noexcept(*std::declval<pointer>())))
    options.linear_solver_ordering = CreateDefaultLinearSolverOrdering(* pp->reduced_program)   → 4
4   if (!ReorderProgram(pp))                                       đúng → 5   sai → 6
5   return false                                                   → END
6   pp->linear_solver_options.min_num_iterations = options.min_linear_solver_iterations
    pp->linear_solver_options.max_num_iterations = options.max_linear_solver_iterations
    pp->linear_solver_options.type = options.linear_solver_type
    pp->linear_solver_options.preconditioner_type = options.preconditioner_type
    pp->linear_solver_options.use_spse_initialization = options.use_spse_initialization
    pp->linear_solver_options.spse_tolerance = options.spse_tolerance
    pp->linear_solver_options.max_num_spse_iterations = options.max_num_spse_iterations
    pp->linear_solver_options.visibility_clustering_type = options.visibility_clustering_type
    pp->linear_solver_options.sparse_linear_algebra_library_type = options.sparse_linear_algebra_library_type
    pp->linear_solver_options.dense_linear_algebra_library_type = options.dense_linear_algebra_library_type
    pp->linear_solver_options.use_explicit_schur_complement = options.use_explicit_schur_complement
    pp->linear_solver_options.dynamic_sparsity = options.dynamic_sparsity
    pp->linear_solver_options.use_mixed_precision_solves = options.use_mixed_precision_solves
    pp->linear_solver_options.max_num_refinement_iterations = options.max_num_refinement_iterations
    pp->linear_solver_options.num_threads = options.num_threads
    pp->linear_solver_options.context = pp->problem->context()     → 7
7   if (IsSchurType(pp->linear_solver_options.type))               đúng → 8   sai → 11
8   OrderingToGroupSizes(options.linear_solver_ordering.get(), &pp->linear_solver_options.elimination_groups)   → 9
9   if (pp->linear_solver_options.elimination_groups.size() == 1)   đúng → 10   sai → 11
10  pp->linear_solver_options.elimination_groups.push_back(0)      → 11
11  if (!options.dynamic_sparsity && AreJacobianColumnsOrdered(options.linear_solver_type, options.preconditioner_type, options.sparse_linear_algebra_library_type, options.linear_solver_ordering_type))   đúng → 12   sai → 14
12  pp->linear_solver_options.ordering_type = OrderingType::NATURAL   → 13
13  pp->linear_solver = LinearSolver::Create(pp->linear_solver_options)
    return (pp->linear_solver != nullptr)                          → END
14  if (options.linear_solver_ordering_type == ceres::AMD)         đúng → 15   sai → 16
15  pp->linear_solver_options.ordering_type = OrderingType::AMD    → 13
16  LOG(FATAL)                                                     đúng → 17   sai → DỪNG
17  pp->linear_solver_options.ordering_type = OrderingType::NESDIS   → 13
18  ParameterBlockOrdering *ordering = options.linear_solver_ordering.get()
    const int min_group_id = ordering->MinNonZeroGroup()
    ordering->Remove(pp->removed_parameter_blocks)                 → 19
19  if (IsSchurType(options.linear_solver_type) && min_group_id != ordering->MinNonZeroGroup())   đúng → 20   sai → 4
20  AlternateLinearSolverAndPreconditionerForSchurTypeLinearSolver(&options)   → 4
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
#include "ceres/trust_region_preprocessor.h"
#include "ceres/ordered_groups.h"
#include "ceres/solver.h"
#include "ceres/linear_solver.h"
#include "ceres/preprocessor.h"
#include "ceres/problem_impl.h"
#include "ceres/reorder_program.h"
#include "ceres/trust_region_preprocessor.cc"
```

- Hàm này chỉ dùng được bên trong file `internal/ceres/trust_region_preprocessor.cc` (khai báo `static` hoặc trong namespace không tên). Để gọi được, thêm `#include "ceres/trust_region_preprocessor.cc"` vào file test.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1460_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
