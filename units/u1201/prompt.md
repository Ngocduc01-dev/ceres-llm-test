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

- Hàm: `CreateFakeBundleAdjustmentJacobian(int num_cameras, int num_points, int camera_size, int point_size, double visibility, std::mt19937 & prng)`, trả về `std::unique_ptr<BlockSparseMatrix>`
- Loại: hàm tự do (không thuộc class)
- Namespace: `ceres::internal`
- Vị trí: `internal/ceres/fake_bundle_adjustment_jacobian.cc`, dòng 44–97

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
44 | std::unique_ptr<BlockSparseMatrix> CreateFakeBundleAdjustmentJacobian(
45 |     int num_cameras,
46 |     int num_points,
47 |     int camera_size,
48 |     int point_size,
49 |     double visibility,
50 |     std::mt19937& prng) {
51 |   constexpr int kResidualSize = 2;
52 | 
53 |   CompressedRowBlockStructure* bs = new CompressedRowBlockStructure;
54 |   int c = 0;
55 |   // Add column blocks for each point
56 |   for (int i = 0; i < num_points; ++i) {
57 |     bs->cols.push_back(Block(point_size, c));
58 |     c += point_size;
59 |   }
60 | 
61 |   // Add column blocks for each camera.
62 |   for (int i = 0; i < num_cameras; ++i) {
63 |     bs->cols.push_back(Block(camera_size, c));
64 |     c += camera_size;
65 |   }
66 | 
67 |   std::bernoulli_distribution visibility_distribution(visibility);
68 |   int row_pos = 0;
69 |   int cell_pos = 0;
70 |   for (int i = 0; i < num_points; ++i) {
71 |     for (int j = 0; j < num_cameras; ++j) {
72 |       if (!visibility_distribution(prng)) {
73 |         continue;
74 |       }
75 |       bs->rows.emplace_back();
76 |       auto& row = bs->rows.back();
77 |       row.block.position = row_pos;
78 |       row.block.size = kResidualSize;
79 |       auto& cells = row.cells;
80 |       cells.resize(2);
81 | 
82 |       cells[0].block_id = i;
83 |       cells[0].position = cell_pos;
84 |       cell_pos += kResidualSize * point_size;
85 | 
86 |       cells[1].block_id = num_points + j;
87 |       cells[1].position = cell_pos;
88 |       cell_pos += kResidualSize * camera_size;
89 | 
90 |       row_pos += kResidualSize;
91 |     }
92 |   }
93 | 
94 |   auto jacobian = std::make_unique<BlockSparseMatrix>(bs);
95 |   VectorRef(jacobian->mutable_values(), jacobian->num_nonzeros()).setRandom();
96 |   return jacobian;
97 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Số điểm rẽ nhánh: 5

START → 1
1   constexpr int kResidualSize = 2
    CFGNewAllocator(CompressedRowBlockStructure *)
    CompressedRowBlockStructure *bs = new CompressedRowBlockStructure
    int c = 0
    int i = 0                                                      → 2
2   vòng for, điều kiện: i < num_points                            đúng → 3   sai → 5
3   bs->cols.push_back(Block(point_size, c))
    c += point_size                                                → 4
4   ++i                                                            → 2
5   int i = 0                                                      → 6
6   vòng for, điều kiện: i < num_cameras                           đúng → 7   sai → 9
7   bs->cols.push_back(Block(camera_size, c))
    c += camera_size                                               → 8
8   ++i                                                            → 6
9   int row_pos = 0
    int cell_pos = 0
    int i = 0                                                      → 10
10  vòng for, điều kiện: i < num_points                            đúng → 11   sai → 18
11  int j = 0                                                      → 12
12  vòng for, điều kiện: j < num_cameras                           đúng → 13   sai → 17
13  if (!visibility_distribution(prng))                            đúng → 14   sai → 16
14  continue                                                       → 15
15  ++j                                                            → 12
16  bs->rows.emplace_back()
    auto &row = bs->rows.back()
    row.block.position = row_pos
    row.block.size = kResidualSize
    auto &cells = row.cells
    cells.resize(2)
    cells[0].block_id = i
    cells[0].position = cell_pos
    cell_pos += kResidualSize * point_size
    cells[1].block_id = num_points + j
    cells[1].position = cell_pos
    cell_pos += kResidualSize * camera_size
    row_pos += kResidualSize                                       → 15
17  ++i                                                            → 10
18  VectorRef(jacobian->mutable_values(), jacobian->num_nonzeros()).setRandom()   → END
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
#include "ceres/fake_bundle_adjustment_jacobian.h"
#include "ceres/block_sparse_matrix.h"
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1201_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
