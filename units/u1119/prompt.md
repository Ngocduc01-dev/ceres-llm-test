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

- Hàm: `Finalize(int num_additional_elements)`, trả về `void`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::DynamicCompressedRowSparseMatrix`
- Vị trí: `internal/ceres/dynamic_compressed_row_sparse_matrix.cc`, dòng 65–99

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
65 | void DynamicCompressedRowSparseMatrix::Finalize(int num_additional_elements) {
66 |   // `num_additional_elements` is provided as an argument so that additional
67 |   // storage can be reserved when it is known by the finalizer.
68 |   CHECK_GE(num_additional_elements, 0);
69 | 
70 |   // Count the number of non-zeros and resize `cols_` and `values_`.
71 |   int num_jacobian_nonzeros = 0;
72 |   for (const auto& dynamic_col : dynamic_cols_) {
73 |     num_jacobian_nonzeros += dynamic_col.size();
74 |   }
75 | 
76 |   SetMaxNumNonZeros(num_jacobian_nonzeros + num_additional_elements);
77 | 
78 |   // Flatten `dynamic_cols_` into `cols_` and `dynamic_values_`
79 |   // into `values_`.
80 |   int index_into_values_and_cols = 0;
81 |   for (int i = 0; i < num_rows(); ++i) {
82 |     mutable_rows()[i] = index_into_values_and_cols;
83 |     const int num_nonzero_columns = dynamic_cols_[i].size();
84 |     if (num_nonzero_columns > 0) {
85 |       memcpy(mutable_cols() + index_into_values_and_cols,
86 |              &dynamic_cols_[i][0],
87 |              dynamic_cols_[i].size() * sizeof(dynamic_cols_[0][0]));
88 |       memcpy(mutable_values() + index_into_values_and_cols,
89 |              &dynamic_values_[i][0],
90 |              dynamic_values_[i].size() * sizeof(dynamic_values_[0][0]));
91 |       index_into_values_and_cols += dynamic_cols_[i].size();
92 |     }
93 |   }
94 |   mutable_rows()[num_rows()] = index_into_values_and_cols;
95 | 
96 |   CHECK_EQ(index_into_values_and_cols, num_jacobian_nonzeros)
97 |       << "Ceres bug: final index into values_ and cols_ should be equal to "
98 |       << "the number of jacobian nonzeros. Please contact the developers!";
99 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 3 (và 2 lệnh CHECK)

START → 1
1   CHECK_GE(num_additional_elements, 0)                           đúng → 2   sai → DỪNG
2   int num_jacobian_nonzeros = 0                                  → 3
3   for (const auto &dynamic_col : dynamic_cols_)                  đúng → 4   sai → 6
4   const auto &dynamic_col
    num_jacobian_nonzeros += dynamic_col.size()                    → 5
5   ++ (bước tiếp của vòng for)                                    → 3
6   SetMaxNumNonZeros(num_jacobian_nonzeros + num_additional_elements)
    int index_into_values_and_cols = 0
    int i = 0                                                      → 7
7   vòng for, điều kiện: i < num_rows()                            đúng → 8   sai → 12
8   mutable_rows()[i] = index_into_values_and_cols
    const int num_nonzero_columns = dynamic_cols_[i].size()        → 9
9   if (num_nonzero_columns > 0)                                   đúng → 10   sai → 11
10  memcpy(mutable_cols() + index_into_values_and_cols, &dynamic_cols_[i][0], dynamic_cols_[i].size() * sizeof (dynamic_cols_[0][0]))
    memcpy(mutable_values() + index_into_values_and_cols, &dynamic_values_[i][0], dynamic_values_[i].size() * sizeof (dynamic_values_[0][0]))
    index_into_values_and_cols += dynamic_cols_[i].size()          → 11
11  ++i                                                            → 7
12  mutable_rows()[num_rows()] = index_into_values_and_cols        → 13
13  CHECK_EQ(index_into_values_and_cols, num_jacobian_nonzeros)    đúng → END   sai → DỪNG
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
#include "ceres/dynamic_compressed_row_sparse_matrix.h"
```

- Đây là method của class `ceres::internal::DynamicCompressedRowSparseMatrix`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `DynamicCompressedRowSparseMatrix`:
Các constructor:
```cpp
  DynamicCompressedRowSparseMatrix(int num_rows, int num_cols, int initial_max_num_nonzeros)
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1119_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
