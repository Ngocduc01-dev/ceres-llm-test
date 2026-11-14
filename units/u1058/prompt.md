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
- Thuộc class: `ceres::DynamicNumericDiffCostFunction` (class template)
- Vị trí: `include/ceres/dynamic_numeric_diff_cost_function.h`, dòng 97–154

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
 97 |   bool Evaluate(double const* const* parameters,
 98 |                 double* residuals,
 99 |                 double** jacobians) const override {
100 |     using internal::NumericDiff;
101 |     CHECK_GT(num_residuals(), 0)
102 |         << "You must call DynamicNumericDiffCostFunction::SetNumResiduals() "
103 |         << "before DynamicNumericDiffCostFunction::Evaluate().";
104 | 
105 |     const std::vector<int32_t>& block_sizes = parameter_block_sizes();
106 |     CHECK(!block_sizes.empty())
107 |         << "You must call DynamicNumericDiffCostFunction::AddParameterBlock() "
108 |         << "before DynamicNumericDiffCostFunction::Evaluate().";
109 | 
110 |     const bool status =
111 |         internal::VariadicEvaluate<internal::DynamicParameterDims>(
112 |             *functor_.get(), parameters, residuals);
113 |     if (jacobians == nullptr || !status) {
114 |       return status;
115 |     }
116 | 
117 |     // Create local space for a copy of the parameters which will get mutated.
118 |     int parameters_size = accumulate(block_sizes.begin(), block_sizes.end(), 0);
119 |     std::vector<double> parameters_copy(parameters_size);
120 |     std::vector<double*> parameters_references_copy(block_sizes.size());
121 |     parameters_references_copy[0] = &parameters_copy[0];
122 |     for (size_t block = 1; block < block_sizes.size(); ++block) {
123 |       parameters_references_copy[block] =
124 |           parameters_references_copy[block - 1] + block_sizes[block - 1];
125 |     }
126 | 
127 |     // Copy the parameters into the local temp space.
128 |     for (size_t block = 0; block < block_sizes.size(); ++block) {
129 |       memcpy(parameters_references_copy[block],
130 |              parameters[block],
131 |              block_sizes[block] * sizeof(*parameters[block]));
132 |     }
133 | 
134 |     for (size_t block = 0; block < block_sizes.size(); ++block) {
135 |       if (jacobians[block] != nullptr &&
136 |           !NumericDiff<CostFunctor,
137 |                        kMethod,
138 |                        ceres::DYNAMIC,
139 |                        internal::DynamicParameterDims,
140 |                        ceres::DYNAMIC,
141 |                        ceres::DYNAMIC>::
142 |               EvaluateJacobianForParameterBlock(functor_.get(),
143 |                                                 residuals,
144 |                                                 options_,
145 |                                                 this->num_residuals(),
146 |                                                 block,
147 |                                                 block_sizes[block],
148 |                                                 &parameters_references_copy[0],
149 |                                                 jacobians[block])) {
150 |         return false;
151 |       }
152 |     }
153 |     return true;
154 |   }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Ghi chú: đây là template – một số kiểu dữ liệu còn để trống, chỉ được điền khi dùng. CFG dưới đây dựng cho trường hợp DynamicNumericDiffCostFunction<PlusFunctor, RIDDERS> (lấy từ một chỗ Ceres dùng thật).

Số điểm rẽ nhánh: 5 (và 2 lệnh CHECK)

START → 1
1   CHECK_GT(num_residuals(), 0)                                   đúng → 2   sai → DỪNG
2   const std::vector<int32_t> &block_sizes = parameter_block_sizes()   → 3
3   CHECK(!block_sizes.empty())                                    đúng → 4   sai → DỪNG
4   const bool status = internal::VariadicEvaluate<internal::DynamicParameterDims>(*functor_.get(), parameters, residuals)   → 5
5   if (jacobians == nullptr || !status)                           đúng → 6   sai → 7
6   return status                                                  → END
7   int parameters_size = accumulate(block_sizes.begin(), block_sizes.end(), 0)
    block_sizes.size()
    parameters_references_copy[0] = &parameters_copy[0]
    size_t block = 1                                               → 8
8   vòng for, điều kiện: block < block_sizes.size()                đúng → 9   sai → 11
9   parameters_references_copy[block] = parameters_references_copy[block - 1] + block_sizes[block - 1]   → 10
10  ++block                                                        → 8
11  size_t block = 0                                               → 12
12  vòng for, điều kiện: block < block_sizes.size()                đúng → 13   sai → 15
13  memcpy(parameters_references_copy[block], parameters[block], block_sizes[block] * sizeof (*parameters[block]))   → 14
14  ++block                                                        → 12
15  size_t block = 0                                               → 16
16  vòng for, điều kiện: block < block_sizes.size()                đúng → 17   sai → 20
17  if (jacobians[block] != nullptr && !NumericDiff<PlusFunctor, (NumericDiffMethodType)2U, ceres::DYNAMIC, internal::DynamicParameterDims, ceres::DYNAMIC, ceres::DYNAMIC>::EvaluateJacobianForParameterBlock(functor_.get(), residuals, options_, num_residuals(), block, block_sizes[block], &parameters_references_copy[0], jacobians[block]))   đúng → 18   sai → 19
18  return false                                                   → END
19  ++block                                                        → 16
20  return true                                                    → END
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
#include "ceres/dynamic_numeric_diff_cost_function.h"
#include "ceres/internal/numeric_diff.h"
```

- Đây là method của class `ceres::DynamicNumericDiffCostFunction`: tạo một object của class rồi gọi method trên object đó.
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1058_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
