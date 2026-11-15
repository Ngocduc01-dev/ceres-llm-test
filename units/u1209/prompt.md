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

- Hàm: `ParallelInvoke(ContextImpl* context, int start, int end, int num_threads, F&& function, int min_block_size)`, trả về `void`
- Loại: hàm template (hàm mẫu, kiểu dữ liệu được điền khi dùng)
- Namespace: `ceres::internal`
- Vị trí: `internal/ceres/parallel_invoke.h`, dòng 164–268

Mã nguồn (số ở đầu dòng là số dòng trong file):
```cpp
164 | template <typename F>
165 | void ParallelInvoke(ContextImpl* context,
166 |                     int start,
167 |                     int end,
168 |                     int num_threads,
169 |                     F&& function,
170 |                     int min_block_size) {
171 |   CHECK(context != nullptr);
172 | 
173 |   // Maximal number of work items scheduled for a single thread
174 |   //  - Lower number of work items results in larger runtimes on unequal tasks
175 |   //  - Higher number of work items results in larger losses for synchronization
176 |   constexpr int kWorkBlocksPerThread = 4;
177 | 
178 |   // Interval [start, end) is being split into
179 |   // num_threads * kWorkBlocksPerThread contiguous disjoint blocks.
180 |   //
181 |   // In order to avoid creating empty blocks of work, we need to limit
182 |   // number of work blocks by a total number of indices.
183 |   const int num_work_blocks = std::min((end - start) / min_block_size,
184 |                                        num_threads * kWorkBlocksPerThread);
185 | 
186 |   // We use a std::shared_ptr because the main thread can finish all
187 |   // the work before the tasks have been popped off the queue.  So the
188 |   // shared state needs to exist for the duration of all the tasks.
189 |   auto shared_state =
190 |       std::make_shared<ParallelInvokeState>(start, end, num_work_blocks);
191 | 
192 |   // A function which tries to schedule another task in the thread pool and
193 |   // perform several chunks of work. Function expects itself as the argument in
194 |   // order to schedule next task in the thread pool.
195 |   auto task = [context, shared_state, num_threads, &function](auto& task_copy) {
196 |     int num_jobs_finished = 0;
197 |     const int thread_id = shared_state->thread_id.fetch_add(1);
198 |     // In order to avoid dead-locks in nested parallel for loops, task() will be
199 |     // invoked num_threads + 1 times:
200 |     //  - num_threads times via enqueueing task into thread pool
201 |     //  - one more time in the main thread
202 |     //  Tasks enqueued to thread pool might take some time before execution, and
203 |     //  the last task being executed will be terminated here in order to avoid
204 |     //  having more than num_threads active threads
205 |     if (thread_id >= num_threads) return;
206 |     const int num_work_blocks = shared_state->num_work_blocks;
207 |     if (thread_id + 1 < num_threads &&
208 |         shared_state->block_id < num_work_blocks) {
209 |       // Add another thread to the thread pool.
210 |       // Note we are taking the task as value so the copy of shared_state shared
211 |       // pointer (captured by value at declaration of task lambda-function) is
212 |       // copied and the ref count is increased. This is to prevent it from being
213 |       // deleted when the main thread finishes all the work and exits before the
214 |       // threads finish.
215 |       context->thread_pool.AddTask([task_copy]() { task_copy(task_copy); });
216 |     }
217 | 
218 |     const int start = shared_state->start;
219 |     const int base_block_size = shared_state->base_block_size;
220 |     const int num_base_p1_sized_blocks = shared_state->num_base_p1_sized_blocks;
221 | 
222 |     while (true) {
223 |       // Get the next available chunk of work to be performed. If there is no
224 |       // work, return.
225 |       int block_id = shared_state->block_id.fetch_add(1);
226 |       if (block_id >= num_work_blocks) {
227 |         break;
228 |       }
229 |       ++num_jobs_finished;
230 | 
231 |       // For-loop interval [start, end) was split into num_work_blocks,
232 |       // with num_base_p1_sized_blocks of size base_block_size + 1 and remaining
233 |       // num_work_blocks - num_base_p1_sized_blocks of size base_block_size
234 |       //
235 |       // Then, start index of the block #block_id is given by a total
236 |       // length of preceeding blocks:
237 |       //  * Total length of preceeding blocks of size base_block_size + 1:
238 |       //     min(block_id, num_base_p1_sized_blocks) * (base_block_size + 1)
239 |       //
240 |       //  * Total length of preceeding blocks of size base_block_size:
241 |       //     (block_id - min(block_id, num_base_p1_sized_blocks)) *
242 |       //     base_block_size
243 |       //
244 |       // Simplifying sum of those quantities yields a following
245 |       // expression for start index of the block #block_id
246 |       const int curr_start = start + block_id * base_block_size +
247 |                              std::min(block_id, num_base_p1_sized_blocks);
248 |       // First num_base_p1_sized_blocks have size base_block_size + 1
249 |       //
250 |       // Note that it is guaranteed that all blocks are within
251 |       // [start, end) interval
252 |       const int curr_end = curr_start + base_block_size +
253 |                            (block_id < num_base_p1_sized_blocks ? 1 : 0);
254 |       // Perform each task in current block
255 |       const auto range = std::make_tuple(curr_start, curr_end);
256 |       InvokeOnSegment(thread_id, range, function);
257 |     }
258 |     shared_state->block_until_finished.Finished(num_jobs_finished);
259 |   };
260 | 
261 |   // Start scheduling threads and doing work. We might end up with less threads
262 |   // scheduled than expected, if scheduling overhead is larger than the amount
263 |   // of work to be done.
264 |   task(task);
265 | 
266 |   // Wait until all tasks have finished.
267 |   shared_state->block_until_finished.Block();
268 | }
```

## 3.2. CFG của unit

CFG đã được dựng sẵn bằng công cụ phân tích mã nguồn:
```
Ghi chú: đây là template – một số kiểu dữ liệu còn để trống, chỉ được điền khi dùng. CFG dưới đây dựng cho trường hợp ParallelInvoke<(lambda at /work/ceres-solver/internal/ceres/block_jacobi_preconditioner.cc:68:15)>.

Số điểm rẽ nhánh: 0 (và 1 lệnh CHECK)

START → 1
1   CHECK(context != nullptr)   đúng → END   sai → DỪNG
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
#include "ceres/context_impl.h"
#include "ceres/parallel_invoke.h"
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

**D. File test:** đúng **một** khối code C++, dòng đầu là `// FILE: u1209_test.cc`. Mỗi test case ở bảng B là một `TEST(...)`, ngay trên đó có 1 dòng comment ghi path.

---

# 7. LƯU Ý

- Chỉ dùng tên hàm, kiểu dữ liệu có trong mã nguồn và các `#include` ở mục 3.3. Không tự bịa hàm.
- Không sửa mã nguồn của Ceres.
- Code phải đầy đủ, không viết `...` thay cho phần code còn thiếu.
- Không giải thích lý thuyết ngoài các bảng ở mục 6.
