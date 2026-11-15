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

- Hàm: `DetectStructure(const CompressedRowBlockStructure & bs, const int num_eliminate_blocks, int * row_block_size, int * e_block_size, int * f_block_size)`, trả về `void`
- Loại: hàm tự do (không thuộc class)
- Namespace: `ceres::internal`
- Vị trí: `internal/ceres/detect_structure.cc`, dòng 38–119

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
 38 | void DetectStructure(const CompressedRowBlockStructure& bs,
 39 |                      const int num_eliminate_blocks,
 40 |                      int* row_block_size,
 41 |                      int* e_block_size,
 42 |                      int* f_block_size) {
 43 |   const int num_row_blocks = bs.rows.size();
 44 |   *row_block_size = 0;
 45 |   *e_block_size = 0;
 46 |   *f_block_size = 0;
 47 | 
 48 |   // Iterate over row blocks of the matrix, checking if row_block,
 49 |   // e_block or f_block sizes remain constant.
 50 |   for (int r = 0; r < num_row_blocks; ++r) {
 51 |     const CompressedRow& row = bs.rows[r];
 52 |     // We do not care about the sizes of the blocks in rows which do
 53 |     // not contain e_blocks.
 54 |     if (row.cells.front().block_id >= num_eliminate_blocks) {
 55 |       break;
 56 |     }
 57 | 
 58 |     // Detect fixed or dynamic row block size.
 59 |     if (*row_block_size == 0) {
 60 |       *row_block_size = row.block.size;
 61 |     } else if (*row_block_size != Eigen::Dynamic &&
 62 |                *row_block_size != row.block.size) {
 63 |       VLOG(2) << "Dynamic row block size because the block size changed from "
 64 |               << *row_block_size << " to " << row.block.size;
 65 |       *row_block_size = Eigen::Dynamic;
 66 |     }
 67 | 
 68 |     // Detect fixed or dynamic e-block size.
 69 |     const int e_block_id = row.cells.front().block_id;
 70 |     if (*e_block_size == 0) {
 71 |       *e_block_size = bs.cols[e_block_id].size;
 72 |     } else if (*e_block_size != Eigen::Dynamic &&
 73 |                *e_block_size != bs.cols[e_block_id].size) {
 74 |       VLOG(2) << "Dynamic e block size because the block size changed from "
 75 |               << *e_block_size << " to " << bs.cols[e_block_id].size;
 76 |       *e_block_size = Eigen::Dynamic;
 77 |     }
 78 | 
 79 |     // Detect fixed or dynamic f-block size. We are only interested in
 80 |     // rows with e-blocks, and the e-block is always the first block,
 81 |     // so only rows of size greater than 1 are of interest.
 82 |     if (row.cells.size() > 1) {
 83 |       if (*f_block_size == 0) {
 84 |         const int f_block_id = row.cells[1].block_id;
 85 |         *f_block_size = bs.cols[f_block_id].size;
 86 |       }
 87 | 
 88 |       for (int c = 1;
 89 |            (c < row.cells.size()) && (*f_block_size != Eigen::Dynamic);
 90 |            ++c) {
 91 |         const int f_block_id = row.cells[c].block_id;
 92 |         if (*f_block_size != bs.cols[f_block_id].size) {
 93 |           VLOG(2) << "Dynamic f block size because the block size "
 94 |                   << "changed from " << *f_block_size << " to "
 95 |                   << bs.cols[f_block_id].size;
 96 |           *f_block_size = Eigen::Dynamic;
 97 |         }
 98 |       }
 99 |     }
100 | 
101 |     // clang-format off
102 |     const bool is_everything_dynamic = (*row_block_size == Eigen::Dynamic &&
103 |                                         *e_block_size == Eigen::Dynamic &&
104 |                                         *f_block_size == Eigen::Dynamic);
105 |     // clang-format on
106 |     if (is_everything_dynamic) {
107 |       break;
108 |     }
109 |   }
110 | 
111 |   CHECK_NE(*row_block_size, 0) << "No rows found";
112 |   CHECK_NE(*e_block_size, 0) << "No e type blocks found";
113 |   // clang-format off
114 |   VLOG(1) << "Schur complement static structure <"
115 |           << *row_block_size << ","
116 |           << *e_block_size << ","
117 |           << *f_block_size << ">.";
118 |   // clang-format on
119 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 11 (và 2 lệnh CHECK)

START → 1
1   const int num_row_blocks = bs.rows.size()
    *row_block_size = 0
    *e_block_size = 0
    *f_block_size = 0
    int r = 0                                                      → 2
2   vòng for, điều kiện: r < num_row_blocks                        đúng → 3   sai → 6
3   const CompressedRow &row = bs.rows[r]                          → 4
4   if (row.cells.front().block_id >= num_eliminate_blocks)        đúng → 5   sai → 8
5   break                                                          → 6
6   CHECK_NE(*row_block_size, 0)                                   đúng → 7   sai → DỪNG
7   CHECK_NE(*e_block_size, 0)                                     đúng → END   sai → DỪNG
8   if (*row_block_size == 0)                                      đúng → 9   sai → 26
9   *row_block_size = row.block.size                               → 10
10  const int e_block_id = row.cells.front().block_id              → 11
11  if (*e_block_size == 0)                                        đúng → 12   sai → 25
12  *e_block_size = bs.cols[e_block_id].size                       → 13
13  if (row.cells.size() > 1)                                      đúng → 14   sai → 21
14  if (*f_block_size == 0)                                        đúng → 15   sai → 16
15  const int f_block_id = row.cells[1].block_id
    *f_block_size = bs.cols[f_block_id].size                       → 16
16  int c = 1                                                      → 17
17  vòng for, điều kiện: (c < row.cells.size()) && (*f_block_size != Eigen::Dynamic)   đúng → 18   sai → 21
18  const int f_block_id = row.cells[c].block_id                   → 19
19  if (*f_block_size != bs.cols[f_block_id].size)                 đúng → 20   sai → 20
20  ++c                                                            → 17
21  const bool is_everything_dynamic = (*row_block_size == Eigen::Dynamic && *e_block_size == Eigen::Dynamic && *f_block_size == Eigen::Dynamic)   → 22
22  if (is_everything_dynamic)                                     đúng → 23   sai → 24
23  break                                                          → 6
24  ++r                                                            → 2
25  if (*e_block_size != Eigen::Dynamic && *e_block_size != bs.cols[e_block_id].size)   đúng → 13   sai → 13
26  if (*row_block_size != Eigen::Dynamic && *row_block_size != row.block.size)   đúng → 10   sai → 10
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
#include "ceres/detect_structure.h"
#include "ceres/block_structure.h"
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u0785_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
