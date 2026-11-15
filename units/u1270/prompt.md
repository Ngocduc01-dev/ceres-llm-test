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
- **Tổng số nhánh** (mẫu số của C2) = 2 × số điểm rẽ nhánh ghi ở dòng đầu CFG (`switch`: mỗi `case` là 1 nhánh). **Không** tính nhánh của `CHECK`.
- **Vòng lặp:**
  - Có giới hạn số lần lặp n (ví dụ `for (i = 0; i < size; ...)`): test với **0, 1, 2, một số ở giữa, n−1, n** lần lặp; thêm **n+1** nếu làm được.
  - Không có giới hạn (lặp đến khi thoả một điều kiện, ví dụ `while (!done)`): test với **0, 1, 2** lần lặp và **mỗi cách thoát khỏi vòng lặp** (`break`, `return`, điều kiện sai) ít nhất 1 lần.
  - Số lần lặp nào không làm được thì ghi lý do.
- **`CHECK(...)`:** lệnh kiểm tra của thư viện glog mà Ceres dùng. Nếu điều kiện sai, chương trình **dừng ngay**. **Không** cố tình làm `CHECK` sai; ghi nhánh đó là "không test (làm chương trình dừng)".

---

# 3. ĐẦU VÀO

## 3.1. Unit cần test

- Hàm: `FullReport() const`, trả về `std::string`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::GradientProblemSolver::Summary`
- Vị trí: `internal/ceres/gradient_problem_solver.cc`, dòng 220–288

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
220 | std::string GradientProblemSolver::Summary::FullReport() const {
221 |   using internal::VersionString;
222 | 
223 |   // NOTE operator+ is not usable for concatenating a string and a string_view.
224 |   std::string report =
225 |       std::string{"\nSolver Summary (v "}.append(VersionString()) + ")\n\n";
226 | 
227 |   StringAppendF(&report, "Parameters          % 25d\n", num_parameters);
228 |   if (num_tangent_parameters != num_parameters) {
229 |     StringAppendF(
230 |         &report, "Tangent parameters   % 25d\n", num_tangent_parameters);
231 |   }
232 | 
233 |   std::string line_search_direction_string;
234 |   if (line_search_direction_type == LBFGS) {
235 |     line_search_direction_string = StringPrintf("LBFGS (%d)", max_lbfgs_rank);
236 |   } else if (line_search_direction_type == NONLINEAR_CONJUGATE_GRADIENT) {
237 |     line_search_direction_string = NonlinearConjugateGradientTypeToString(
238 |         nonlinear_conjugate_gradient_type);
239 |   } else {
240 |     line_search_direction_string =
241 |         LineSearchDirectionTypeToString(line_search_direction_type);
242 |   }
243 | 
244 |   StringAppendF(&report,
245 |                 "Line search direction     %19s\n",
246 |                 line_search_direction_string.c_str());
247 | 
248 |   const std::string line_search_type_string = StringPrintf(
249 |       "%s %s",
250 |       LineSearchInterpolationTypeToString(line_search_interpolation_type),
251 |       LineSearchTypeToString(line_search_type));
252 |   StringAppendF(&report,
253 |                 "Line search type          %19s\n",
254 |                 line_search_type_string.c_str());
255 |   StringAppendF(&report, "\n");
256 | 
257 |   StringAppendF(&report, "\nCost:\n");
258 |   StringAppendF(&report, "Initial        % 30e\n", initial_cost);
259 |   if (termination_type != FAILURE && termination_type != USER_FAILURE) {
260 |     StringAppendF(&report, "Final          % 30e\n", final_cost);
261 |     StringAppendF(&report, "Change         % 30e\n", initial_cost - final_cost);
262 |   }
263 | 
264 |   StringAppendF(&report,
265 |                 "\nMinimizer iterations         % 16d\n",
266 |                 static_cast<int>(iterations.size()));
267 | 
268 |   StringAppendF(&report, "\nTime (in seconds):\n");
269 |   StringAppendF(&report,
270 |                 "\n  Cost evaluation     %23.6f (%d)\n",
271 |                 cost_evaluation_time_in_seconds,
272 |                 num_cost_evaluations);
273 |   StringAppendF(&report,
274 |                 "  Gradient & cost evaluation %16.6f (%d)\n",
275 |                 gradient_evaluation_time_in_seconds,
276 |                 num_gradient_evaluations);
277 |   StringAppendF(&report,
278 |                 "  Polynomial minimization   %17.6f\n",
279 |                 line_search_polynomial_minimization_time_in_seconds);
280 |   StringAppendF(
281 |       &report, "Total               %25.6f\n\n", total_time_in_seconds);
282 | 
283 |   StringAppendF(&report,
284 |                 "Termination:        %25s (%s)\n",
285 |                 TerminationTypeToString(termination_type),
286 |                 message.c_str());
287 |   return report;
288 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 4

START → 1
1   StringAppendF(&report, "Parameters          % 25d\n", num_parameters)   → 2
2   if (num_tangent_parameters != num_parameters)                  đúng → 3   sai → 4
3   StringAppendF(&report, "Tangent parameters   % 25d\n", num_tangent_parameters)   → 4
4   if (line_search_direction_type == LBFGS)                       đúng → 5   sai → 10
5   operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    line_search_direction_string = StringPrintf("LBFGS (%d)", max_lbfgs_rank)   → 6
6   StringAppendF(&report, "Line search direction     %19s\n", line_search_direction_string.c_str())
    StringPrintf("%s %s", LineSearchInterpolationTypeToString(line_search_interpolation_type), LineSearchTypeToString(line_search_type))
    StringAppendF(&report, "Line search type          %19s\n", line_search_type_string.c_str())
    StringAppendF(&report, "\n")
    StringAppendF(&report, "\nCost:\n")
    StringAppendF(&report, "Initial        % 30e\n", initial_cost)   → 7
7   if (termination_type != FAILURE && termination_type != USER_FAILURE)   đúng → 8   sai → 9
8   StringAppendF(&report, "Final          % 30e\n", final_cost)
    StringAppendF(&report, "Change         % 30e\n", initial_cost - final_cost)   → 9
9   StringAppendF(&report, "\nMinimizer iterations         % 16d\n", static_cast<int>(iterations.size()))
    StringAppendF(&report, "\nTime (in seconds):\n")
    StringAppendF(&report, "\n  Cost evaluation     %23.6f (%d)\n", cost_evaluation_time_in_seconds, num_cost_evaluations)
    StringAppendF(&report, "  Gradient & cost evaluation %16.6f (%d)\n", gradient_evaluation_time_in_seconds, num_gradient_evaluations)
    StringAppendF(&report, "  Polynomial minimization   %17.6f\n", line_search_polynomial_minimization_time_in_seconds)
    StringAppendF(&report, "Total               %25.6f\n\n", total_time_in_seconds)
    StringAppendF(&report, "Termination:        %25s (%s)\n", TerminationTypeToString(termination_type), message.c_str())   → END
10  if (line_search_direction_type == NONLINEAR_CONJUGATE_GRADIENT)   đúng → 11   sai → 12
11  line_search_direction_string = NonlinearConjugateGradientTypeToString(nonlinear_conjugate_gradient_type)   → 6
12  line_search_direction_string = LineSearchDirectionTypeToString(line_search_direction_type)   → 6
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
#include "ceres/gradient_problem_solver.h"
```

- Đây là method của class `ceres::GradientProblemSolver::Summary`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `Summary`:
Các constructor:
```cpp
  Summary()
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1270_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
