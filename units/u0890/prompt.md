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

- Hàm: `GetBestSchurTemplateSpecialization(int * row_block_size, int * e_block_size, int * f_block_size)`, trả về `void`
- Loại: hàm tự do (không thuộc class)
- Namespace: `ceres::internal`
- Vị trí: `internal/ceres/schur_templates.cc`, dòng 48–224

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
 48 | void GetBestSchurTemplateSpecialization(int* row_block_size,
 49 |                                         int* e_block_size,
 50 |                                         int* f_block_size) {
 51 |   LinearSolver::Options options;
 52 |   options.row_block_size = *row_block_size;
 53 |   options.e_block_size = *e_block_size;
 54 |   options.f_block_size = *f_block_size;
 55 |   *row_block_size = Eigen::Dynamic;
 56 |   *e_block_size = Eigen::Dynamic;
 57 |   *f_block_size = Eigen::Dynamic;
 58 | #ifndef CERES_RESTRICT_SCHUR_SPECIALIZATION
 59 |   if ((options.row_block_size == 2) &&
 60 |      (options.e_block_size == 2) &&
 61 |      (options.f_block_size == 2)) {
 62 |     *row_block_size = 2;
 63 |     *e_block_size = 2;
 64 |     *f_block_size = 2;
 65 |     return;
 66 |   }
 67 |   if ((options.row_block_size == 2) &&
 68 |      (options.e_block_size == 2) &&
 69 |      (options.f_block_size == 3)) {
 70 |     *row_block_size = 2;
 71 |     *e_block_size = 2;
 72 |     *f_block_size = 3;
 73 |     return;
 74 |   }
 75 |   if ((options.row_block_size == 2) &&
 76 |      (options.e_block_size == 2) &&
 77 |      (options.f_block_size == 4)) {
 78 |     *row_block_size = 2;
 79 |     *e_block_size = 2;
 80 |     *f_block_size = 4;
 81 |     return;
 82 |   }
 83 |   if ((options.row_block_size == 2) &&
 84 |      (options.e_block_size == 2)) {
 85 |     *row_block_size = 2;
 86 |     *e_block_size = 2;
 87 |     *f_block_size = Eigen::Dynamic;
 88 |     return;
 89 |   }
 90 |   if ((options.row_block_size == 2) &&
 91 |      (options.e_block_size == 3) &&
 92 |      (options.f_block_size == 3)) {
 93 |     *row_block_size = 2;
 94 |     *e_block_size = 3;
 95 |     *f_block_size = 3;
 96 |     return;
 97 |   }
 98 |   if ((options.row_block_size == 2) &&
 99 |      (options.e_block_size == 3) &&
100 |      (options.f_block_size == 4)) {
101 |     *row_block_size = 2;
102 |     *e_block_size = 3;
103 |     *f_block_size = 4;
104 |     return;
105 |   }
106 |   if ((options.row_block_size == 2) &&
107 |      (options.e_block_size == 3) &&
108 |      (options.f_block_size == 6)) {
109 |     *row_block_size = 2;
110 |     *e_block_size = 3;
111 |     *f_block_size = 6;
112 |     return;
113 |   }
114 |   if ((options.row_block_size == 2) &&
115 |      (options.e_block_size == 3) &&
116 |      (options.f_block_size == 9)) {
117 |     *row_block_size = 2;
118 |     *e_block_size = 3;
119 |     *f_block_size = 9;
120 |     return;
121 |   }
122 |   if ((options.row_block_size == 2) &&
123 |      (options.e_block_size == 3)) {
124 |     *row_block_size = 2;
125 |     *e_block_size = 3;
126 |     *f_block_size = Eigen::Dynamic;
127 |     return;
128 |   }
129 |   if ((options.row_block_size == 2) &&
130 |      (options.e_block_size == 4) &&
131 |      (options.f_block_size == 3)) {
132 |     *row_block_size = 2;
133 |     *e_block_size = 4;
134 |     *f_block_size = 3;
135 |     return;
136 |   }
137 |   if ((options.row_block_size == 2) &&
138 |      (options.e_block_size == 4) &&
139 |      (options.f_block_size == 4)) {
140 |     *row_block_size = 2;
141 |     *e_block_size = 4;
142 |     *f_block_size = 4;
143 |     return;
144 |   }
145 |   if ((options.row_block_size == 2) &&
146 |      (options.e_block_size == 4) &&
147 |      (options.f_block_size == 6)) {
148 |     *row_block_size = 2;
149 |     *e_block_size = 4;
150 |     *f_block_size = 6;
151 |     return;
152 |   }
153 |   if ((options.row_block_size == 2) &&
154 |      (options.e_block_size == 4) &&
155 |      (options.f_block_size == 8)) {
156 |     *row_block_size = 2;
157 |     *e_block_size = 4;
158 |     *f_block_size = 8;
159 |     return;
160 |   }
161 |   if ((options.row_block_size == 2) &&
162 |      (options.e_block_size == 4) &&
163 |      (options.f_block_size == 9)) {
164 |     *row_block_size = 2;
165 |     *e_block_size = 4;
166 |     *f_block_size = 9;
167 |     return;
168 |   }
169 |   if ((options.row_block_size == 2) &&
170 |      (options.e_block_size == 4)) {
171 |     *row_block_size = 2;
172 |     *e_block_size = 4;
173 |     *f_block_size = Eigen::Dynamic;
174 |     return;
175 |   }
176 |   if (options.row_block_size == 2) {
177 |     *row_block_size = 2;
178 |     *e_block_size = Eigen::Dynamic;
179 |     *f_block_size = Eigen::Dynamic;
180 |     return;
181 |   }
182 |   if ((options.row_block_size == 3) &&
183 |      (options.e_block_size == 3) &&
184 |      (options.f_block_size == 3)) {
185 |     *row_block_size = 3;
186 |     *e_block_size = 3;
187 |     *f_block_size = 3;
188 |     return;
189 |   }
190 |   if ((options.row_block_size == 4) &&
191 |      (options.e_block_size == 4) &&
192 |      (options.f_block_size == 2)) {
193 |     *row_block_size = 4;
194 |     *e_block_size = 4;
195 |     *f_block_size = 2;
196 |     return;
197 |   }
198 |   if ((options.row_block_size == 4) &&
199 |      (options.e_block_size == 4) &&
200 |      (options.f_block_size == 3)) {
201 |     *row_block_size = 4;
202 |     *e_block_size = 4;
203 |     *f_block_size = 3;
204 |     return;
205 |   }
206 |   if ((options.row_block_size == 4) &&
207 |      (options.e_block_size == 4) &&
208 |      (options.f_block_size == 4)) {
209 |     *row_block_size = 4;
210 |     *e_block_size = 4;
211 |     *f_block_size = 4;
212 |     return;
213 |   }
214 |   if ((options.row_block_size == 4) &&
215 |      (options.e_block_size == 4)) {
216 |     *row_block_size = 4;
217 |     *e_block_size = 4;
218 |     *f_block_size = Eigen::Dynamic;
219 |     return;
220 |   }
221 | 
222 | #endif
223 |   return;
224 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 0

START → 1
1   options.row_block_size = *row_block_size
    options.e_block_size = *e_block_size
    options.f_block_size = *f_block_size
    *row_block_size = Eigen::Dynamic
    *e_block_size = Eigen::Dynamic
    *f_block_size = Eigen::Dynamic
    return                                                         → END
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
#include "ceres/schur_templates.h"
#include "ceres/linear_solver.h"
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u0890_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
