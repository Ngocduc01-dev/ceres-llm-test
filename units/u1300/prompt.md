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

- Hàm: `operator()(const IterationSummary & summary)`, trả về `CallbackReturnType`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::LoggingCallback`
- Vị trí: `internal/ceres/callbacks.cc`, dòng 82–126

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
 82 | CallbackReturnType LoggingCallback::operator()(
 83 |     const IterationSummary& summary) {
 84 |   std::string output;
 85 |   if (minimizer_type == LINE_SEARCH) {
 86 |     output = StringPrintf(
 87 |         "% 4d: f:% 8e d:% 3.2e g:% 3.2e h:% 3.2e s:% 3.2e e:% 3d it:% 3.2e "
 88 |         "tt:% 3.2e",
 89 |         summary.iteration,
 90 |         summary.cost,
 91 |         summary.cost_change,
 92 |         summary.gradient_max_norm,
 93 |         summary.step_norm,
 94 |         summary.step_size,
 95 |         summary.line_search_function_evaluations,
 96 |         summary.iteration_time_in_seconds,
 97 |         summary.cumulative_time_in_seconds);
 98 |   } else if (minimizer_type == TRUST_REGION) {
 99 |     // clang-format off
100 |     if (summary.iteration == 0) {
101 |       output = "iter      cost      cost_change  |gradient|   |step|    tr_ratio  tr_radius  ls_iter  iter_time  total_time\n";  // NOLINT
102 |     }
103 |     output += StringPrintf(
104 |         "% 4d % 8e   % 3.2e   % 3.2e  % 3.2e  % 3.2e % 3.2e     % 4d   % 3.2e   % 3.2e",  // NOLINT
105 |         // clang-format on
106 |         summary.iteration,
107 |         summary.cost,
108 |         summary.cost_change,
109 |         summary.gradient_max_norm,
110 |         summary.step_norm,
111 |         summary.relative_decrease,
112 |         summary.trust_region_radius,
113 |         summary.linear_solver_iterations,
114 |         summary.iteration_time_in_seconds,
115 |         summary.cumulative_time_in_seconds);
116 |   } else {
117 |     LOG(FATAL) << "Unknown minimizer type.";
118 |   }
119 | 
120 |   if (log_to_stdout_) {
121 |     std::cout << output << std::endl;
122 |   } else {
123 |     VLOG(1) << output;
124 |   }
125 |   return SOLVER_CONTINUE;
126 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 3 (và 1 lệnh CHECK)

START → 1
1   if (minimizer_type == LINE_SEARCH)                             đúng → 2   sai → 6
2   operator= (ImplicitCastExpr, FunctionToPointerDecay, basic_string<char> &(*)(basic_string<char> &&) noexcept(_Alloc_traits::_S_nothrow_move()))
    output = StringPrintf("% 4d: f:% 8e d:% 3.2e g:% 3.2e h:% 3.2e s:% 3.2e e:% 3d it:% 3.2e tt:% 3.2e", summary.iteration, summary.cost, summary.cost_change, summary.gradient_max_norm, summary.step_norm, summary.step_size, summary.line_search_function_evaluations, summary.iteration_time_in_seconds, summary.cumulative_time_in_seconds)   → 3
3   if (log_to_stdout_)                                            đúng → 4   sai → 5
4   operator<< (ImplicitCastExpr, FunctionToPointerDecay, __ostream_type &(*)(__ostream_type &(*)(__ostream_type &)))
    std::cout << output << std::endl                               → 5
5   return SOLVER_CONTINUE                                         → END
6   LOG(FATAL)                                                     đúng → 7   sai → DỪNG
7   if (summary.iteration == 0)                                    đúng → 8   sai → 9
8   output = "iter      cost      cost_change  |gradient|   |step|    tr_ratio  tr_radius  ls_iter  iter_time  total_time\n"   → 9
9   output += StringPrintf("% 4d % 8e   % 3.2e   % 3.2e  % 3.2e  % 3.2e % 3.2e     % 4d   % 3.2e   % 3.2e", summary.iteration, summary.cost, summary.cost_change, summary.gradient_max_norm, summary.step_norm, summary.relative_decrease, summary.trust_region_radius, summary.linear_solver_iterations, summary.iteration_time_in_seconds, summary.cumulative_time_in_seconds)   → 3
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
#include "ceres/iteration_callback.h"
#include "ceres/callbacks.h"
```

- Đây là method của class `ceres::internal::LoggingCallback`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `LoggingCallback`:
Các constructor:
```cpp
  LoggingCallback(const MinimizerType minimizer_type, const bool log_to_stdout)
  LoggingCallback(MinimizerType minimizer_type, bool log_to_stdout)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1300_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
