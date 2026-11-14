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

- Hàm: `Evaluate(const double *const * parameters, double * residuals, double ** jacobians) const`, trả về `bool`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::DynamicAutoDiffCostFunction` (class template)
- Vị trí: `include/ceres/dynamic_autodiff_cost_function.h`, dòng 101–265

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
101 |   bool Evaluate(double const* const* parameters,
102 |                 double* residuals,
103 |                 double** jacobians) const override {
104 |     CHECK_GT(num_residuals(), 0)
105 |         << "You must call DynamicAutoDiffCostFunction::SetNumResiduals() "
106 |         << "before DynamicAutoDiffCostFunction::Evaluate().";
107 | 
108 |     if (jacobians == nullptr) {
109 |       return (*functor_)(parameters, residuals);
110 |     }
111 | 
112 |     // The difficulty with Jets, as implemented in Ceres, is that they were
113 |     // originally designed for strictly compile-sized use. At this point, there
114 |     // is a large body of code that assumes inside a cost functor it is
115 |     // acceptable to do e.g. T(1.5) and get an appropriately sized jet back.
116 |     //
117 |     // Unfortunately, it is impossible to communicate the expected size of a
118 |     // dynamically sized jet to the static instantiations that existing code
119 |     // depends on.
120 |     //
121 |     // To work around this issue, the solution here is to evaluate the
122 |     // jacobians in a series of passes, each one computing Stride *
123 |     // num_residuals() derivatives. This is done with small, fixed-size jets.
124 |     const int num_parameter_blocks =
125 |         static_cast<int>(parameter_block_sizes().size());
126 |     const int num_parameters = std::accumulate(
127 |         parameter_block_sizes().begin(), parameter_block_sizes().end(), 0);
128 | 
129 |     // Allocate scratch space for the strided evaluation.
130 |     using JetT = Jet<double, Stride>;
131 |     internal::FixedArray<JetT, (256 * 7) / sizeof(JetT)> input_jets(
132 |         num_parameters);
133 |     internal::FixedArray<JetT, (256 * 7) / sizeof(JetT)> output_jets(
134 |         num_residuals());
135 | 
136 |     // Make the parameter pack that is sent to the functor (reused).
137 |     internal::FixedArray<Jet<double, Stride>*> jet_parameters(
138 |         num_parameter_blocks, nullptr);
139 |     int num_active_parameters = 0;
140 | 
141 |     // To handle constant parameters between non-constant parameter blocks, the
142 |     // start position --- a raw parameter index --- of each contiguous block of
143 |     // non-constant parameters is recorded in start_derivative_section.
144 |     std::vector<int> start_derivative_section;
145 |     bool in_derivative_section = false;
146 |     int parameter_cursor = 0;
147 | 
148 |     // Discover the derivative sections and set the parameter values.
149 |     for (int i = 0; i < num_parameter_blocks; ++i) {
150 |       jet_parameters[i] = &input_jets[parameter_cursor];
151 | 
152 |       const int parameter_block_size = parameter_block_sizes()[i];
153 |       if (jacobians[i] != nullptr) {
154 |         if (!in_derivative_section) {
155 |           start_derivative_section.push_back(parameter_cursor);
156 |           in_derivative_section = true;
157 |         }
158 | 
159 |         num_active_parameters += parameter_block_size;
160 |       } else {
161 |         in_derivative_section = false;
162 |       }
163 | 
164 |       for (int j = 0; j < parameter_block_size; ++j, parameter_cursor++) {
165 |         input_jets[parameter_cursor].a = parameters[i][j];
166 |       }
167 |     }
168 | 
169 |     if (num_active_parameters == 0) {
170 |       return (*functor_)(parameters, residuals);
171 |     }
172 |     // When `num_active_parameters % Stride != 0` then it can be the case
173 |     // that `active_parameter_count < Stride` while parameter_cursor is less
174 |     // than the total number of parameters and with no remaining non-constant
175 |     // parameter blocks. Pushing parameter_cursor (the total number of
176 |     // parameters) as a final entry to start_derivative_section is required
177 |     // because if a constant parameter block is encountered after the
178 |     // last non-constant block then current_derivative_section is incremented
179 |     // and would otherwise index an invalid position in
180 |     // start_derivative_section. Setting the final element to the total number
181 |     // of parameters means that this can only happen at most once in the loop
182 |     // below.
183 |     start_derivative_section.push_back(parameter_cursor);
184 | 
185 |     // Evaluate all of the strides. Each stride is a chunk of the derivative to
186 |     // evaluate, typically some size proportional to the size of the SIMD
187 |     // registers of the CPU.
188 |     int num_strides = static_cast<int>(
189 |         ceil(num_active_parameters / static_cast<float>(Stride)));
190 | 
191 |     int current_derivative_section = 0;
192 |     int current_derivative_section_cursor = 0;
193 | 
194 |     for (int pass = 0; pass < num_strides; ++pass) {
195 |       // Set most of the jet components to zero, except for
196 |       // non-constant #Stride parameters.
197 |       const int initial_derivative_section = current_derivative_section;
198 |       const int initial_derivative_section_cursor =
199 |           current_derivative_section_cursor;
200 | 
201 |       int active_parameter_count = 0;
202 |       parameter_cursor = 0;
203 | 
204 |       for (int i = 0; i < num_parameter_blocks; ++i) {
205 |         for (int j = 0; j < parameter_block_sizes()[i];
206 |              ++j, parameter_cursor++) {
207 |           input_jets[parameter_cursor].v.setZero();
208 |           if (active_parameter_count < Stride &&
209 |               parameter_cursor >=
210 |                   (start_derivative_section[current_derivative_section] +
211 |                    current_derivative_section_cursor)) {
212 |             if (jacobians[i] != nullptr) {
213 |               input_jets[parameter_cursor].v[active_parameter_count] = 1.0;
214 |               ++active_parameter_count;
215 |               ++current_derivative_section_cursor;
216 |             } else {
217 |               ++current_derivative_section;
218 |               current_derivative_section_cursor = 0;
219 |             }
220 |           }
221 |         }
222 |       }
223 | 
224 |       if (!(*functor_)(&jet_parameters[0], &output_jets[0])) {
225 |         return false;
226 |       }
227 | 
228 |       // Copy the pieces of the jacobians into their final place.
229 |       active_parameter_count = 0;
230 | 
231 |       current_derivative_section = initial_derivative_section;
232 |       current_derivative_section_cursor = initial_derivative_section_cursor;
233 | 
234 |       for (int i = 0, parameter_cursor = 0; i < num_parameter_blocks; ++i) {
235 |         for (int j = 0; j < parameter_block_sizes()[i];
236 |              ++j, parameter_cursor++) {
237 |           if (active_parameter_count < Stride &&
238 |               parameter_cursor >=
239 |                   (start_derivative_section[current_derivative_section] +
240 |                    current_derivative_section_cursor)) {
241 |             if (jacobians[i] != nullptr) {
242 |               for (int k = 0; k < num_residuals(); ++k) {
243 |                 jacobians[i][k * parameter_block_sizes()[i] + j] =
244 |                     output_jets[k].v[active_parameter_count];
245 |               }
246 |               ++active_parameter_count;
247 |               ++current_derivative_section_cursor;
248 |             } else {
249 |               ++current_derivative_section;
250 |               current_derivative_section_cursor = 0;
251 |             }
252 |           }
253 |         }
254 |       }
255 | 
256 |       // Only copy the residuals over once (even though we compute them on
257 |       // every loop).
258 |       if (pass == num_strides - 1) {
259 |         for (int k = 0; k < num_residuals(); ++k) {
260 |           residuals[k] = output_jets[k].a;
261 |         }
262 |       }
263 |     }
264 |     return true;
265 |   }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Ghi chú: đây là template – một số kiểu dữ liệu còn để trống, chỉ được điền khi dùng. CFG dưới đây dựng cho trường hợp DynamicAutoDiffCostFunction<DynamicTwoParameterBlockFunctor> (lấy từ một chỗ Ceres dùng thật).

Số điểm rẽ nhánh: 19 (và 1 lệnh CHECK)

START → 1
1   CHECK_GT(num_residuals(), 0)                                   đúng → 2   sai → DỪNG
2   if (jacobians == nullptr)                                      đúng → 3   sai → 4
3   operator* (ImplicitCastExpr, FunctionToPointerDecay, typename add_lvalue_reference<element_type>::type (*)(void) const noexcept(noexcept(*std::declval<pointer>())))
    return (* functor_)(parameters, residuals)                     → END
4   const int num_parameter_blocks = static_cast<int>(parameter_block_sizes().size())
    const int num_parameters = std::accumulate(parameter_block_sizes().begin(), parameter_block_sizes().end(), 0)
    num_residuals()
    num_parameter_blocks, nullptr
    int num_active_parameters = 0
    bool in_derivative_section = false
    int parameter_cursor = 0
    int i = 0                                                      → 5
5   vòng for, điều kiện: i < num_parameter_blocks                  đúng → 6   sai → 17
6   jet_parameters[i] = &input_jets[parameter_cursor]
    const int parameter_block_size = parameter_block_sizes()[i]    → 7
7   if (jacobians[i] != nullptr)                                   đúng → 8   sai → 16
8   if (!in_derivative_section)                                    đúng → 9   sai → 10
9   start_derivative_section.push_back(parameter_cursor)
    in_derivative_section = true                                   → 10
10  num_active_parameters += parameter_block_size                  → 11
11  int j = 0                                                      → 12
12  vòng for, điều kiện: j < parameter_block_size                  đúng → 13   sai → 15
13  input_jets[parameter_cursor].a = parameters[i][j]              → 14
14  ++j                                                            → 12
15  ++i                                                            → 5
16  in_derivative_section = false                                  → 11
17  if (num_active_parameters == 0)                                đúng → 18   sai → 19
18  operator* (ImplicitCastExpr, FunctionToPointerDecay, typename add_lvalue_reference<element_type>::type (*)(void) const noexcept(noexcept(*std::declval<pointer>())))
    return (* functor_)(parameters, residuals)                     → END
19  start_derivative_section.push_back(parameter_cursor)
    int num_strides = static_cast<int>(ceil(num_active_parameters / static_cast<float>(4)))
    int current_derivative_section = 0
    int current_derivative_section_cursor = 0
    int pass = 0                                                   → 20
20  vòng for, điều kiện: pass < num_strides                        đúng → 21   sai → 55
21  const int initial_derivative_section = current_derivative_section
    const int initial_derivative_section_cursor = current_derivative_section_cursor
    int active_parameter_count = 0
    parameter_cursor = 0
    int i = 0                                                      → 22
22  vòng for, điều kiện: i < num_parameter_blocks                  đúng → 23   sai → 32
23  int j = 0                                                      → 24
24  vòng for, điều kiện: j < parameter_block_sizes()[i]            đúng → 25   sai → 31
25  input_jets[parameter_cursor].v.setZero()                       → 26
26  if (active_parameter_count < 4 && parameter_cursor >= (start_derivative_section[current_derivative_section] + current_derivative_section_cursor))   đúng → 27   sai → 29
27  if (jacobians[i] != nullptr)                                   đúng → 28   sai → 30
28  input_jets[parameter_cursor].v[active_parameter_count] = 1.
    ++active_parameter_count
    ++current_derivative_section_cursor                            → 29
29  ++j                                                            → 24
30  ++current_derivative_section
    current_derivative_section_cursor = 0                          → 29
31  ++i                                                            → 22
32  operator* (ImplicitCastExpr, FunctionToPointerDecay, typename add_lvalue_reference<element_type>::type (*)(void) const noexcept(noexcept(*std::declval<pointer>())))   → 33
33  if (!(* functor_)(&jet_parameters[0], &output_jets[0]))        đúng → 34   sai → 35
34  return false                                                   → END
35  active_parameter_count = 0
    current_derivative_section = initial_derivative_section
    current_derivative_section_cursor = initial_derivative_section_cursor
    int i = 0
    int parameter_cursor = 0                                       → 36
36  vòng for, điều kiện: i < num_parameter_blocks                  đúng → 37   sai → 49
37  int j = 0                                                      → 38
38  vòng for, điều kiện: j < parameter_block_sizes()[i]            đúng → 39   sai → 48
39  if (active_parameter_count < 4 && parameter_cursor >= (start_derivative_section[current_derivative_section] + current_derivative_section_cursor))   đúng → 40   sai → 46
40  if (jacobians[i] != nullptr)                                   đúng → 41   sai → 47
41  int k = 0                                                      → 42
42  vòng for, điều kiện: k < num_residuals()                       đúng → 43   sai → 45
43  jacobians[i][k * parameter_block_sizes()[i] + j] = output_jets[k].v[active_parameter_count]   → 44
44  ++k                                                            → 42
45  ++active_parameter_count
    ++current_derivative_section_cursor                            → 46
46  ++j                                                            → 38
47  ++current_derivative_section
    current_derivative_section_cursor = 0                          → 46
48  ++i                                                            → 36
49  if (pass == num_strides - 1)                                   đúng → 50   sai → 54
50  int k = 0                                                      → 51
51  vòng for, điều kiện: k < num_residuals()                       đúng → 52   sai → 54
52  residuals[k] = output_jets[k].a                                → 53
53  ++k                                                            → 51
54  ++pass                                                         → 20
55  return true                                                    → END
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
#include "ceres/dynamic_autodiff_cost_function.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/jet.h"
```

- Đây là method của class `ceres::DynamicAutoDiffCostFunction`: tạo một object của class rồi gọi method trên object đó.
- Đây là template (khuôn mẫu): khi tạo object hoặc gọi hàm phải chọn kiểu cụ thể phù hợp (xem ví dụ chỗ dùng trong Ceres ở ghi chú của CFG, nếu có).

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1130_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
