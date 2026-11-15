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

- Hàm: `RightMultiplyAndAccumulate(const double * x, double * y) const`, trả về `void`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::CompressedRowSparseMatrix`
- Vị trí: `internal/ceres/compressed_row_sparse_matrix.cc`, dòng 304–358

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
304 | void CompressedRowSparseMatrix::RightMultiplyAndAccumulate(const double* x,
305 |                                                            double* y) const {
306 |   CHECK(x != nullptr);
307 |   CHECK(y != nullptr);
308 | 
309 |   if (storage_type_ == StorageType::UNSYMMETRIC) {
310 |     RightMultiplyAndAccumulate(x, y, nullptr, 1);
311 |   } else if (storage_type_ == StorageType::UPPER_TRIANGULAR) {
312 |     // Because of their block structure, we will have entries that lie
313 |     // above (below) the diagonal for lower (upper) triangular matrices,
314 |     // so the loops below need to account for this.
315 |     for (int r = 0; r < num_rows_; ++r) {
316 |       int idx = rows_[r];
317 |       const int idx_end = rows_[r + 1];
318 | 
319 |       // For upper triangular matrices r <= c, so skip entries with r
320 |       // > c.
321 |       while (idx < idx_end && r > cols_[idx]) {
322 |         ++idx;
323 |       }
324 | 
325 |       for (; idx < idx_end; ++idx) {
326 |         const int c = cols_[idx];
327 |         const double v = values_[idx];
328 |         y[r] += v * x[c];
329 |         // Since we are only iterating over the upper triangular part
330 |         // of the matrix, add contributions for the strictly lower
331 |         // triangular part.
332 |         if (r != c) {
333 |           y[c] += v * x[r];
334 |         }
335 |       }
336 |     }
337 |   } else if (storage_type_ == StorageType::LOWER_TRIANGULAR) {
338 |     for (int r = 0; r < num_rows_; ++r) {
339 |       int idx = rows_[r];
340 |       const int idx_end = rows_[r + 1];
341 |       // For lower triangular matrices, we only iterate till we are r >=
342 |       // c.
343 |       for (; idx < idx_end && r >= cols_[idx]; ++idx) {
344 |         const int c = cols_[idx];
345 |         const double v = values_[idx];
346 |         y[r] += v * x[c];
347 |         // Since we are only iterating over the lower triangular part
348 |         // of the matrix, add contributions for the strictly upper
349 |         // triangular part.
350 |         if (r != c) {
351 |           y[c] += v * x[r];
352 |         }
353 |       }
354 |     }
355 |   } else {
356 |     LOG(FATAL) << "Unknown storage type: " << storage_type_;
357 |   }
358 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 9 (và 3 lệnh CHECK)

START → 1
1   CHECK(x != nullptr)                                            đúng → 2   sai → DỪNG
2   CHECK(y != nullptr)                                            đúng → 3   sai → DỪNG
3   if (storage_type_ == StorageType::UNSYMMETRIC)                 đúng → 4   sai → 5
4   RightMultiplyAndAccumulate(x, y, nullptr, 1)                   → END
5   if (storage_type_ == StorageType::UPPER_TRIANGULAR)            đúng → 6   sai → 17
6   int r = 0                                                      → 7
7   vòng for, điều kiện: r < num_rows_                             đúng → 8   sai → END
8   int idx = rows_[r]
    const int idx_end = rows_[r + 1]                               → 9
9   while (idx < idx_end && r > cols_[idx])                        đúng → 10   sai → 11
10  ++idx                                                          → 9
11  for (; idx < idx_end; ...)                                     đúng → 12   sai → 16
12  const int c = cols_[idx]
    const double v = values_[idx]
    y[r] += v * x[c]                                               → 13
13  if (r != c)                                                    đúng → 14   sai → 15
14  y[c] += v * x[r]                                               → 15
15  ++idx                                                          → 11
16  ++r                                                            → 7
17  LOG(FATAL)                                                     đúng → 18   sai → DỪNG
18  int r = 0                                                      → 19
19  vòng for, điều kiện: r < num_rows_                             đúng → 20   sai → END
20  int idx = rows_[r]
    const int idx_end = rows_[r + 1]                               → 21
21  for (; idx < idx_end && r >= cols_[idx]; ...)                  đúng → 22   sai → 26
22  const int c = cols_[idx]
    const double v = values_[idx]
    y[r] += v * x[c]                                               → 23
23  if (r != c)                                                    đúng → 24   sai → 25
24  y[c] += v * x[r]                                               → 25
25  ++idx                                                          → 21
26  ++r                                                            → 19
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
```

- Đây là method của class `ceres::internal::CompressedRowSparseMatrix`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `CompressedRowSparseMatrix`:
Các constructor:
```cpp
  CompressedRowSparseMatrix(int num_rows, int num_cols, int max_num_nonzeros)
  CompressedRowSparseMatrix(const double * diagonal, int num_rows)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1215_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
