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

- Hàm: `MatrixMatrixMultiplyNaive(xem mã nguồn – hàm được sinh ra từ macro)`, trả về `void`
- Loại: hàm template (hàm mẫu, kiểu dữ liệu được điền khi dùng)
- Namespace: `ceres::internal`
- Vị trí: `internal/ceres/small_blas.h`, dòng 177–244

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
177 | CERES_GEMM_BEGIN(MatrixMatrixMultiplyNaive) {
178 |   CERES_GEMM_NAIVE_HEADER
179 |   DCHECK_EQ(NUM_COL_A, NUM_ROW_B);
180 | 
181 |   const int NUM_ROW_C = NUM_ROW_A;
182 |   const int NUM_COL_C = NUM_COL_B;
183 |   DCHECK_LE(start_row_c + NUM_ROW_C, row_stride_c);
184 |   DCHECK_LE(start_col_c + NUM_COL_C, col_stride_c);
185 |   const int span = 4;
186 | 
187 |   // Calculate the remainder part first.
188 | 
189 |   // Process the last odd column if present.
190 |   if (NUM_COL_C & 1) {
191 |     int col = NUM_COL_C - 1;
192 |     const double* pa = &A[0];
193 |     for (int row = 0; row < NUM_ROW_C; ++row, pa += NUM_COL_A) {
194 |       const double* pb = &B[col];
195 |       double tmp = 0.0;
196 |       for (int k = 0; k < NUM_COL_A; ++k, pb += NUM_COL_B) {
197 |         tmp += pa[k] * pb[0];
198 |       }
199 | 
200 |       const int index = (row + start_row_c) * col_stride_c + start_col_c + col;
201 |       CERES_GEMM_STORE_SINGLE(C, index, tmp);
202 |     }
203 | 
204 |     // Return directly for efficiency of extremely small matrix multiply.
205 |     if (NUM_COL_C == 1) {
206 |       return;
207 |     }
208 |   }
209 | 
210 |   // Process the couple columns in remainder if present.
211 |   if (NUM_COL_C & 2) {
212 |     int col = NUM_COL_C & (~(span - 1));
213 |     const double* pa = &A[0];
214 |     for (int row = 0; row < NUM_ROW_C; ++row, pa += NUM_COL_A) {
215 |       const double* pb = &B[col];
216 |       double tmp1 = 0.0, tmp2 = 0.0;
217 |       for (int k = 0; k < NUM_COL_A; ++k, pb += NUM_COL_B) {
218 |         double av = pa[k];
219 |         tmp1 += av * pb[0];
220 |         tmp2 += av * pb[1];
221 |       }
222 | 
223 |       const int index = (row + start_row_c) * col_stride_c + start_col_c + col;
224 |       CERES_GEMM_STORE_PAIR(C, index, tmp1, tmp2);
225 |     }
226 | 
227 |     // Return directly for efficiency of extremely small matrix multiply.
228 |     if (NUM_COL_C < span) {
229 |       return;
230 |     }
231 |   }
232 | 
233 |   // Calculate the main part with multiples of 4.
234 |   int col_m = NUM_COL_C & (~(span - 1));
235 |   for (int col = 0; col < col_m; col += span) {
236 |     for (int row = 0; row < NUM_ROW_C; ++row) {
237 |       const int index = (row + start_row_c) * col_stride_c + start_col_c + col;
238 |       // clang-format off
239 |       MMM_mat1x4(NUM_COL_A, &A[row * NUM_COL_A],
240 |                  &B[col], NUM_COL_B, &C[index], kOperation);
241 |       // clang-format on
242 |     }
243 |   }
244 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Ghi chú: đây là template – một số kiểu dữ liệu còn để trống, chỉ được điền khi dùng. CFG dưới đây dựng cho trường hợp MatrixMatrixMultiplyNaive<-1, -1, -1, -1, -1>.

Số điểm rẽ nhánh: 10 (và 11 lệnh CHECK)

START → 1
1   CERES_GEMM_NAIVE_HEADER                                        đúng → 2   sai → DỪNG
2   CERES_GEMM_NAIVE_HEADER                                        đúng → 3   sai → DỪNG
3   CERES_GEMM_NAIVE_HEADER                                        đúng → 4   sai → DỪNG
4   CERES_GEMM_NAIVE_HEADER                                        đúng → 5   sai → DỪNG
5   CERES_GEMM_NAIVE_HEADER                                        đúng → 6   sai → DỪNG
6   CERES_GEMM_NAIVE_HEADER                                        đúng → 7   sai → DỪNG
7   CERES_GEMM_NAIVE_HEADER                                        đúng → 8   sai → DỪNG
8   CERES_GEMM_NAIVE_HEADER                                        đúng → 9   sai → DỪNG
9   (-1 == Eigen::Dynamic) || ...                                  → 10
10  !((__builtin_expect(!((-1 == Eigen::Dynamic) || (-1 == num_row_a)), 0))) ? ... : ...   → 11
11  !((__builtin_expect(!((-1 == Eigen::Dynamic) || (-1 == num_col_a)), 0))) ? ... : ...   → 12
12  !((__builtin_expect(!((-1 == Eigen::Dynamic) || (-1 == num_row_b)), 0))) ? ... : ...   → 13
13  !((__builtin_expect(!((-1 == Eigen::Dynamic) || (-1 == num_col_b)), 0))) ? ... : ...   → 14
14  const int NUM_ROW_A = (-1 != Eigen::Dynamic ? -1 : num_row_a)
    -1 != Eigen::Dynamic ? ... : ...                               → 15
15  const int NUM_COL_A = (-1 != Eigen::Dynamic ? -1 : num_col_a)
    -1 != Eigen::Dynamic ? ... : ...                               → 16
16  const int NUM_ROW_B = (-1 != Eigen::Dynamic ? -1 : num_row_b)
    -1 != Eigen::Dynamic ? ... : ...                               → 17
17  const int NUM_COL_B = (-1 != Eigen::Dynamic ? -1 : num_col_b)   → 18
18  DCHECK_EQ(NUM_COL_A, NUM_ROW_B)                                đúng → 19   sai → DỪNG
19  const int NUM_ROW_C = NUM_ROW_A
    const int NUM_COL_C = NUM_COL_B                                → 20
20  DCHECK_LE(start_row_c + NUM_ROW_C, row_stride_c)               đúng → 21   sai → DỪNG
21  DCHECK_LE(start_col_c + NUM_COL_C, col_stride_c)               đúng → 22   sai → DỪNG
22  const int span = 4                                             → 23
23  if (NUM_COL_C & 1)                                             đúng → 24   sai → 36
24  int col = NUM_COL_C - 1
    const double *pa = &A[0]
    int row = 0                                                    → 25
25  vòng for, điều kiện: row < NUM_ROW_C                           đúng → 26   sai → 34
26  const double *pb = &B[col]
    double tmp = 0.
    int k = 0                                                      → 27
27  vòng for, điều kiện: k < NUM_COL_A                             đúng → 28   sai → 30
28  tmp += pa[k] * pb[0]                                           → 29
29  ++k                                                            → 27
30  const int index = (row + start_row_c) * col_stride_c + start_col_c + col
    if -1 > 0                                                      → 31
31  if -1 < 0                                                      → 32
32  C[index] -= tmp                                                → 33
33  ++row                                                          → 25
34  if (NUM_COL_C == 1)                                            đúng → 35   sai → 36
35  return                                                         → END
36  if (NUM_COL_C & 2)                                             đúng → 37   sai → 49
37  int col = NUM_COL_C & (~(span - 1))
    const double *pa = &A[0]
    int row = 0                                                    → 38
38  vòng for, điều kiện: row < NUM_ROW_C                           đúng → 39   sai → 47
39  const double *pb = &B[col]
    double tmp1 = 0.
    double tmp2 = 0.
    int k = 0                                                      → 40
40  vòng for, điều kiện: k < NUM_COL_A                             đúng → 41   sai → 43
41  double av = pa[k]
    tmp1 += av * pb[0]
    tmp2 += av * pb[1]                                             → 42
42  ++k                                                            → 40
43  const int index = (row + start_row_c) * col_stride_c + start_col_c + col
    if -1 > 0                                                      → 44
44  if -1 < 0                                                      → 45
45  C[index] -= tmp1
    C[index + 1] -= tmp2                                           → 46
46  ++row                                                          → 38
47  if (NUM_COL_C < span)                                          đúng → 48   sai → 49
48  return                                                         → END
49  int col_m = NUM_COL_C & (~(span - 1))
    int col = 0                                                    → 50
50  vòng for, điều kiện: col < col_m                               đúng → 51   sai → END
51  int row = 0                                                    → 52
52  vòng for, điều kiện: row < NUM_ROW_C                           đúng → 53   sai → 55
53  const int index = (row + start_row_c) * col_stride_c + start_col_c + col
    MMM_mat1x4(NUM_COL_A, &A[row * NUM_COL_A], &B[col], NUM_COL_B, &C[index], -1)   → 54
54  ++row                                                          → 52
55  col += span                                                    → 50
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
#include "ceres/small_blas.h"
#include "ceres/small_blas_generic.h"
```

- Đây là template (khuôn mẫu): khi tạo object hoặc gọi hàm phải chọn kiểu cụ thể phù hợp.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1061_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
