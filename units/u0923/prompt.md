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

- Hàm: `Create(const LinearSolver::Options & options)`, trả về `std::unique_ptr<SchurEliminatorBase>`
- Loại: method (hàm thành viên của class)
- Thuộc class: `ceres::internal::SchurEliminatorBase`
- Vị trí: `internal/ceres/schur_eliminator.cc`, dòng 51–161

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
 51 | std::unique_ptr<SchurEliminatorBase> SchurEliminatorBase::Create(
 52 |     const LinearSolver::Options& options) {
 53 | #ifndef CERES_RESTRICT_SCHUR_SPECIALIZATION
 54 |   if ((options.row_block_size == 2) &&
 55 |      (options.e_block_size == 2) &&
 56 |      (options.f_block_size == 2)) {
 57 |     return std::make_unique<SchurEliminator<2, 2, 2>>(options);
 58 |   }
 59 |   if ((options.row_block_size == 2) &&
 60 |      (options.e_block_size == 2) &&
 61 |      (options.f_block_size == 3)) {
 62 |     return std::make_unique<SchurEliminator<2, 2, 3>>(options);
 63 |   }
 64 |   if ((options.row_block_size == 2) &&
 65 |      (options.e_block_size == 2) &&
 66 |      (options.f_block_size == 4)) {
 67 |     return std::make_unique<SchurEliminator<2, 2, 4>>(options);
 68 |   }
 69 |   if ((options.row_block_size == 2) &&
 70 |      (options.e_block_size == 2)) {
 71 |     return std::make_unique<SchurEliminator<2, 2, Eigen::Dynamic>>(options);
 72 |   }
 73 |   if ((options.row_block_size == 2) &&
 74 |      (options.e_block_size == 3) &&
 75 |      (options.f_block_size == 3)) {
 76 |     return std::make_unique<SchurEliminator<2, 3, 3>>(options);
 77 |   }
 78 |   if ((options.row_block_size == 2) &&
 79 |      (options.e_block_size == 3) &&
 80 |      (options.f_block_size == 4)) {
 81 |     return std::make_unique<SchurEliminator<2, 3, 4>>(options);
 82 |   }
 83 |   if ((options.row_block_size == 2) &&
 84 |      (options.e_block_size == 3) &&
 85 |      (options.f_block_size == 6)) {
 86 |     return std::make_unique<SchurEliminator<2, 3, 6>>(options);
 87 |   }
 88 |   if ((options.row_block_size == 2) &&
 89 |      (options.e_block_size == 3) &&
 90 |      (options.f_block_size == 9)) {
 91 |     return std::make_unique<SchurEliminator<2, 3, 9>>(options);
 92 |   }
 93 |   if ((options.row_block_size == 2) &&
 94 |      (options.e_block_size == 3)) {
 95 |     return std::make_unique<SchurEliminator<2, 3, Eigen::Dynamic>>(options);
 96 |   }
 97 |   if ((options.row_block_size == 2) &&
 98 |      (options.e_block_size == 4) &&
 99 |      (options.f_block_size == 3)) {
100 |     return std::make_unique<SchurEliminator<2, 4, 3>>(options);
101 |   }
102 |   if ((options.row_block_size == 2) &&
103 |      (options.e_block_size == 4) &&
104 |      (options.f_block_size == 4)) {
105 |     return std::make_unique<SchurEliminator<2, 4, 4>>(options);
106 |   }
107 |   if ((options.row_block_size == 2) &&
108 |      (options.e_block_size == 4) &&
109 |      (options.f_block_size == 6)) {
110 |     return std::make_unique<SchurEliminator<2, 4, 6>>(options);
111 |   }
112 |   if ((options.row_block_size == 2) &&
113 |      (options.e_block_size == 4) &&
114 |      (options.f_block_size == 8)) {
115 |     return std::make_unique<SchurEliminator<2, 4, 8>>(options);
116 |   }
117 |   if ((options.row_block_size == 2) &&
118 |      (options.e_block_size == 4) &&
119 |      (options.f_block_size == 9)) {
120 |     return std::make_unique<SchurEliminator<2, 4, 9>>(options);
121 |   }
122 |   if ((options.row_block_size == 2) &&
123 |      (options.e_block_size == 4)) {
124 |     return std::make_unique<SchurEliminator<2, 4, Eigen::Dynamic>>(options);
125 |   }
126 |   if (options.row_block_size == 2) {
127 |     return std::make_unique<SchurEliminator<2, Eigen::Dynamic, Eigen::Dynamic>>(options);
128 |   }
129 |   if ((options.row_block_size == 3) &&
130 |      (options.e_block_size == 3) &&
131 |      (options.f_block_size == 3)) {
132 |     return std::make_unique<SchurEliminator<3, 3, 3>>(options);
133 |   }
134 |   if ((options.row_block_size == 4) &&
135 |      (options.e_block_size == 4) &&
136 |      (options.f_block_size == 2)) {
137 |     return std::make_unique<SchurEliminator<4, 4, 2>>(options);
138 |   }
139 |   if ((options.row_block_size == 4) &&
140 |      (options.e_block_size == 4) &&
141 |      (options.f_block_size == 3)) {
142 |     return std::make_unique<SchurEliminator<4, 4, 3>>(options);
143 |   }
144 |   if ((options.row_block_size == 4) &&
145 |      (options.e_block_size == 4) &&
146 |      (options.f_block_size == 4)) {
147 |     return std::make_unique<SchurEliminator<4, 4, 4>>(options);
148 |   }
149 |   if ((options.row_block_size == 4) &&
150 |      (options.e_block_size == 4)) {
151 |     return std::make_unique<SchurEliminator<4, 4, Eigen::Dynamic>>(options);
152 |   }
153 | 
154 | #endif
155 |   VLOG(1) << "Template specializations not found for <"
156 |           << options.row_block_size << "," << options.e_block_size << ","
157 |           << options.f_block_size << ">";
158 |   return std::make_unique<SchurEliminator<Eigen::Dynamic,
159 |                                           Eigen::Dynamic,
160 |                                           Eigen::Dynamic>>(options);
161 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 0

START → END
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
#include "ceres/linear_solver.h"
#include "ceres/schur_eliminator.h"
```

- Đây là method của class `ceres::internal::SchurEliminatorBase`: tạo một object của class rồi gọi method trên object đó.

Cách tạo object của class `SchurEliminatorBase`:
- Class không tự khai báo constructor → tạo bằng constructor mặc định: `SchurEliminatorBase obj;`
- Class có hàm **thuần ảo** (chưa có code, phải viết ở class con) nên không tạo object trực tiếp được: viết một class con kế thừa và viết các hàm: `Init(int, bool, const CompressedRowBlockStructure *)`, `Eliminate(const BlockSparseMatrixData &, const double *, const double *, BlockRandomAccessMatrix *, double *)`, `BackSubstitute(const BlockSparseMatrixData &, const double *, const double *, const double *, double *)`.

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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u0923_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
