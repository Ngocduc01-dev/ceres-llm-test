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

- Hàm: `FromTripletSparseMatrix(const TripletSparseMatrix & input, bool transpose)`, trả về `std::unique_ptr<CompressedRowSparseMatrix>`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::CompressedRowSparseMatrix`
- Vị trí: `internal/ceres/compressed_row_sparse_matrix.cc`, dòng 193–252

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
193 | std::unique_ptr<CompressedRowSparseMatrix>
194 | CompressedRowSparseMatrix::FromTripletSparseMatrix(
195 |     const TripletSparseMatrix& input, bool transpose) {
196 |   int num_rows = input.num_rows();
197 |   int num_cols = input.num_cols();
198 |   const int* rows = input.rows();
199 |   const int* cols = input.cols();
200 |   const double* values = input.values();
201 | 
202 |   if (transpose) {
203 |     std::swap(num_rows, num_cols);
204 |     std::swap(rows, cols);
205 |   }
206 | 
207 |   // index is the list of indices into the TripletSparseMatrix input.
208 |   std::vector<int> index(input.num_nonzeros(), 0);
209 |   for (int i = 0; i < input.num_nonzeros(); ++i) {
210 |     index[i] = i;
211 |   }
212 | 
213 |   // Sort index such that the entries of m are ordered by row and ties
214 |   // are broken by column.
215 |   std::sort(index.begin(), index.end(), RowColLessThan(rows, cols));
216 | 
217 |   VLOG(1) << "# of rows: " << num_rows << " # of columns: " << num_cols
218 |           << " num_nonzeros: " << input.num_nonzeros() << ". Allocating "
219 |           << ((num_rows + 1) * sizeof(int) +           // NOLINT
220 |               input.num_nonzeros() * sizeof(int) +     // NOLINT
221 |               input.num_nonzeros() * sizeof(double));  // NOLINT
222 | 
223 |   auto output = std::make_unique<CompressedRowSparseMatrix>(
224 |       num_rows, num_cols, input.num_nonzeros());
225 | 
226 |   if (num_rows == 0) {
227 |     // No data to copy.
228 |     return output;
229 |   }
230 | 
231 |   // Copy the contents of the cols and values array in the order given
232 |   // by index and count the number of entries in each row.
233 |   int* output_rows = output->mutable_rows();
234 |   int* output_cols = output->mutable_cols();
235 |   double* output_values = output->mutable_values();
236 | 
237 |   output_rows[0] = 0;
238 |   for (int i = 0; i < index.size(); ++i) {
239 |     const int idx = index[i];
240 |     ++output_rows[rows[idx] + 1];
241 |     output_cols[i] = cols[idx];
242 |     output_values[i] = values[idx];
243 |   }
244 | 
245 |   // Find the cumulative sum of the row counts.
246 |   for (int i = 1; i < num_rows + 1; ++i) {
247 |     output_rows[i] += output_rows[i - 1];
248 |   }
249 | 
250 |   CHECK_EQ(output->num_nonzeros(), input.num_nonzeros());
251 |   return output;
252 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 5 (và 1 lệnh CHECK)

START → 1
1   int num_rows = input.num_rows()
    int num_cols = input.num_cols()
    const int *rows = input.rows()
    const int *cols = input.cols()
    const double *values = input.values()                          → 2
2   if (transpose)                                                 đúng → 3   sai → 4
3   std::swap(num_rows, num_cols)
    std::swap(rows, cols)                                          → 4
4   input.num_nonzeros(), 0
    int i = 0                                                      → 5
5   vòng for, điều kiện: i < input.num_nonzeros()                  đúng → 6   sai → 8
6   index[i] = i                                                   → 7
7   ++i                                                            → 5
8   if (num_rows == 0)                                             đúng → END   sai → 9
9   int *output_rows = output->mutable_rows()
    int *output_cols = output->mutable_cols()
    double *output_values = output->mutable_values()
    output_rows[0] = 0
    int i = 0                                                      → 10
10  vòng for, điều kiện: i < index.size()                          đúng → 11   sai → 13
11  const int idx = index[i]
    ++output_rows[rows[idx] + 1]
    output_cols[i] = cols[idx]
    output_values[i] = values[idx]                                 → 12
12  ++i                                                            → 10
13  int i = 1                                                      → 14
14  vòng for, điều kiện: i < num_rows + 1                          đúng → 15   sai → 17
15  output_rows[i] += output_rows[i - 1]                           → 16
16  ++i                                                            → 14
17  CHECK_EQ(output->num_nonzeros(), input.num_nonzeros())         đúng → END   sai → DỪNG
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
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/triplet_sparse_matrix.h"
```

- Method này là `private` (bên ngoài class không gọi được). Thêm 2 dòng `#define private public` và `#define protected public` **sau** `#include "gtest/gtest.h"` và **trước** các `#include` của Ceres.
- Đây là method của class `ceres::internal::CompressedRowSparseMatrix`: tạo một object của class rồi gọi method trên object đó.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1236_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
