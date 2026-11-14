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

- Hàm: `Degree2MaximumSpanningForest(const WeightedGraph<Vertex>& graph)`, trả về `std::unique_ptr<WeightedGraph<Vertex>>`
- Loại: hàm template (hàm mẫu, kiểu dữ liệu được điền khi dùng)
- Namespace: `ceres::internal`
- Vị trí: `internal/ceres/graph_algorithms.h`, dòng 260–340

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
260 | template <typename Vertex>
261 | std::unique_ptr<WeightedGraph<Vertex>> Degree2MaximumSpanningForest(
262 |     const WeightedGraph<Vertex>& graph) {
263 |   // Array of edges sorted in decreasing order of their weights.
264 |   std::vector<std::pair<double, std::pair<Vertex, Vertex>>> weighted_edges;
265 |   auto forest = std::make_unique<WeightedGraph<Vertex>>();
266 | 
267 |   // Disjoint-set to keep track of the connected components in the
268 |   // maximum spanning tree.
269 |   std::unordered_map<Vertex, Vertex> disjoint_set;
270 | 
271 |   // Sort of the edges in the graph in decreasing order of their
272 |   // weight. Also add the vertices of the graph to the Maximum
273 |   // Spanning Tree graph and set each vertex to be its own connected
274 |   // component in the disjoint_set structure.
275 |   const std::unordered_set<Vertex>& vertices = graph.vertices();
276 |   for (const Vertex& vertex1 : vertices) {
277 |     forest->AddVertex(vertex1, graph.VertexWeight(vertex1));
278 |     disjoint_set[vertex1] = vertex1;
279 | 
280 |     const std::unordered_set<Vertex>& neighbors = graph.Neighbors(vertex1);
281 |     for (const Vertex& vertex2 : neighbors) {
282 |       if (vertex1 >= vertex2) {
283 |         continue;
284 |       }
285 |       const double weight = graph.EdgeWeight(vertex1, vertex2);
286 |       weighted_edges.push_back(
287 |           std::make_pair(weight, std::make_pair(vertex1, vertex2)));
288 |     }
289 |   }
290 | 
291 |   // The elements of this vector, are pairs<edge_weight,
292 |   // edge>. Sorting it using the reverse iterators gives us the edges
293 |   // in decreasing order of edges.
294 |   std::sort(weighted_edges.rbegin(), weighted_edges.rend());
295 | 
296 |   // Greedily add edges to the spanning tree/forest as long as they do
297 |   // not violate the degree/cycle constraint.
298 |   for (int i = 0; i < weighted_edges.size(); ++i) {
299 |     const std::pair<Vertex, Vertex>& edge = weighted_edges[i].second;
300 |     const Vertex vertex1 = edge.first;
301 |     const Vertex vertex2 = edge.second;
302 | 
303 |     // Check if either of the vertices are of degree 2 already, in
304 |     // which case adding this edge will violate the degree 2
305 |     // constraint.
306 |     if ((forest->Neighbors(vertex1).size() == 2) ||
307 |         (forest->Neighbors(vertex2).size() == 2)) {
308 |       continue;
309 |     }
310 | 
311 |     // Find the id of the connected component to which the two
312 |     // vertices belong to. If the id is the same, it means that the
313 |     // two of them are already connected to each other via some other
314 |     // vertex, and adding this edge will create a cycle.
315 |     Vertex root1 = FindConnectedComponent(vertex1, &disjoint_set);
316 |     Vertex root2 = FindConnectedComponent(vertex2, &disjoint_set);
317 | 
318 |     if (root1 == root2) {
319 |       continue;
320 |     }
321 | 
322 |     // This edge can be added, add an edge in either direction with
323 |     // the same weight as the original graph.
324 |     const double edge_weight = graph.EdgeWeight(vertex1, vertex2);
325 |     forest->AddEdge(vertex1, vertex2, edge_weight);
326 |     forest->AddEdge(vertex2, vertex1, edge_weight);
327 | 
328 |     // Connected the two connected components by updating the
329 |     // disjoint_set structure. Always connect the connected component
330 |     // with the greater index with the connected component with the
331 |     // smaller index. This should ensure shallower trees, for quicker
332 |     // lookup.
333 |     if (root2 < root1) {
334 |       std::swap(root1, root2);
335 |     }
336 | 
337 |     disjoint_set[root2] = root1;
338 |   }
339 |   return forest;
340 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Ghi chú: đây là template – một số kiểu dữ liệu còn để trống, chỉ được điền khi dùng. CFG dưới đây dựng cho trường hợp Degree2MaximumSpanningForest<int>.

Số điểm rẽ nhánh: 7

START → 1
1   const std::unordered_set<int> &vertices = graph.vertices()     → 2
2   for (const int &vertex1 : vertices)                            đúng → 3   sai → 11
3   const int &vertex1
    forest->AddVertex(vertex1, graph.VertexWeight(vertex1))
    disjoint_set[vertex1] = vertex1
    const std::unordered_set<int> &neighbors = graph.Neighbors(vertex1)   → 4
4   for (const int &vertex2 : neighbors)                           đúng → 5   sai → 10
5   const int &vertex2                                             → 6
6   if (vertex1 >= vertex2)                                        đúng → 7   sai → 9
7   continue                                                       → 8
8   ++ (bước tiếp của vòng for)                                    → 4
9   const double weight = graph.EdgeWeight(vertex1, vertex2)
    weighted_edges.push_back(std::make_pair(weight, std::make_pair(vertex1, vertex2)))   → 8
10  ++ (bước tiếp của vòng for)                                    → 2
11  int i = 0                                                      → 12
12  vòng for, điều kiện: i < weighted_edges.size()                 đúng → 13   sai → END
13  const std::pair<int, int> &edge = weighted_edges[i].second
    const int vertex1 = edge.first
    const int vertex2 = edge.second                                → 14
14  if (forest->Neighbors(vertex1).size() == 2) || (forest->Neighbors(vertex2).size() == 2)   đúng → 15   sai → 17
15  continue                                                       → 16
16  ++i                                                            → 12
17  int root1 = FindConnectedComponent(vertex1, &disjoint_set)
    int root2 = FindConnectedComponent(vertex2, &disjoint_set)     → 18
18  if (root1 == root2)                                            đúng → 19   sai → 20
19  continue                                                       → 16
20  const double edge_weight = graph.EdgeWeight(vertex1, vertex2)
    forest->AddEdge(vertex1, vertex2, edge_weight)
    forest->AddEdge(vertex2, vertex1, edge_weight)                 → 21
21  if (root2 < root1)                                             đúng → 22   sai → 23
22  std::swap(root1, root2)                                        → 23
23  disjoint_set[root2] = root1                                    → 16
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
#include "ceres/graph.h"
#include "ceres/graph_algorithms.h"
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u0556_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
