# Nhật ký sử dụng AI (AI Usage Log)
## Tuần 1
| Ngày | Lời nhắc (Prompt/Question) | Công cụ AI | Cách nhóm áp dụng vào dự án |
| :--- | :--- | :--- | :--- |
| 10/10/2026 | "Bạn hãy xác định những yêu cầu cần đạt và gợi ý cấu trúc cho dự án Suffix Array cho nhóm 2 người." | Gemini 3.1 Pro | Lấy ý tưởng cấu trúc thư mục chuẩn (src, data, docs), khung file C++ ban đầu và gợi ý phân công nhiệm vụ cho 2 thành viên. |
| 11/10/2026 | "Giảng viên yêu cầu bổ sung algorithm choice + timeline trước khi duyệt. Gợi ý giúp tôi." | Gemini 3.1 Pro | Quyết định chọn thuật toán Prefix Doubling để xây dựng Suffix Array đạt $O(n \log^2 n)$ và Binary Search. Tham khảo khung thời gian 4 tuần để báo cáo giảng viên. |
| 12/10/2026 | "file pattern_search và suffix array để làm gì" | Gemini 3.1 Pro| Hiểu rõ chức năng phân tách file: `suffix_array.cpp` dùng cho tiền xử lý, còn `search.cpp` dùng để xử lý các truy vấn tìm kiếm. |
| 14/10/2026 | "Tôi chưa hiểu link blob/commit cụ thể thể hiện công việc đã làm là gì." | Gemini 3.1 Pro | Phân biệt được link thư mục gốc (repo root) và link trỏ đến từng file (blob/commit) để nộp lại link báo cáo công việc cho đúng. |
----------------------
## Tuần 2
# Nhật ký sử dụng AI (AI Usage Log)

| Ngày | Lời nhắc (Prompt/Question) | Công cụ AI | Cách nhóm áp dụng vào dự án |
| :--- | :--- | :--- | :--- |
| 14/10/2026 | "Bạn hãy xác định những yêu cầu cần đạt và gợi ý cấu trúc cho dự án Suffix Array cho nhóm 2 người." | Gemini 3.1 Pro | Lấy ý tưởng cấu trúc thư mục chuẩn (src, data, docs), khung file C++ boilerplate và chia đầu việc cho 2 thành viên. |
| 14/10/2026 | "Giảng viên yêu cầu bổ sung algorithm choice + timeline trước khi duyệt. Gợi ý giúp tôi." | Gemini 3.1 Pro | Quyết định chọn thuật toán Prefix Doubling ($O(n \log^2 n)$) và Binary Search. Tham khảo khung thời gian 4 tuần để cập nhật plan với GVHD. |
| 14/10/2026 | "file pattern_search và suffix array để làm gì" | Gemini | Hiểu rõ chức năng phân tách module: `suffix_array.cpp` chuyên xử lý tiền kỳ (preprocessing), còn `search.cpp` chuyên xử lý truy vấn tìm kiếm. |
| 14/10/2026 | "Tôi chưa hiểu link blob/commit cụ thể thể hiện công việc đã làm là gì." | Gemini 3.1 Pro | Phân biệt được link repo root với link blob/commit. Áp dụng để lấy đúng đường dẫn file cụ thể trên GitHub nhằm khắc phục lỗi nộp báo cáo. |
| 25/10/2026 | "bây giờ tới tôi làm pattern_search", "hàm comparePattern để làm gì", "ví dụ mẫu" | Gemini 3.1 Pro | Nắm được logic của hàm so sánh tiền tố (comparePattern) để điều hướng không gian tìm kiếm trong Binary Search. Tham khảo ví dụ trace tay để hiểu luồng chạy. |
| 25/10/2026 | "Vậy 2 file đó làm sao để kết hợp đưa vào file main.cpp", "tại sao các biến phải có dấu &" | Gemini 3.1 Pro | Tạo các file header (`.h`) để liên kết các hàm từ nhiều file `.cpp` khác nhau vào `main.cpp`. Ứng dụng kỹ thuật truyền tham chiếu (`&`) kết hợp `const` để tối ưu hóa hiệu năng, tránh sao chép dữ liệu khi benchmark mảng lớn. |
----------------------
## Tuần 3
# Nhật ký sử dụng AI (AI Usage Log)

| Ngày | Lời nhắc (Prompt/Question) | Công cụ AI | Cách nhóm áp dụng vào dự án |
| :--- | :--- | :--- | :--- |
| 30/10/2026 | "Cách gộp các file và sinh file small_test.txt để chạy thử nghiệm. Bị lỗi gạch đỏ khi `#include <suffix_array.h>` và lỗi multiple definition." | Gemini | Tạo các file header (`suffix_array.h`, `pattern_search.h`), sử dụng `#ifndef`, `#define` và dùng lệnh `g++ main.cpp suffix_array.cpp pattern_search.cpp -o dsa` để biên dịch chuẩn. |
| 31/10/2026 | "Code file suffix_array đã giống ban đầu chưa, tôi chỉ có thay thành vector mà thôi. Sửa giúp lỗi cú pháp." | Gemini | Fix lỗi cú pháp, chuyển đổi thành công mảng động C-style sang `std::vector` và `std::string` chuẩn xác trong toàn bộ hàm Prefix Doubling. |
| 31/10/2026 | "Thành viên kia đã tách thành benchmark riêng, bây giờ làm sao để kết nối nó với file main.cpp? Bỏ hàm main trong file benchmark.cpp đi được không?" | Gemini | Bỏ hàm `main` cũ, bọc logic đo thời gian bằng `<chrono>` và sinh truy vấn ngẫu nhiên thành hàm `runAutomatedBenchmark()` rồi gọi thẳng từ Menu của `main.cpp`. |
| 01/11/2026 | "Tại sao nó báo cáo là không chạy đc file large_text.txt? File đó đc lưu trong thư mục này lun (kèm hình ảnh)." | Gemini | Bỏ `freopen`, đổi sang dùng `std::ifstream` để giữ menu tương tác. Điều chỉnh lại cấu trúc thư mục hoặc xóa tiền tố `data/` trong code để đọc file thành công. |
| 02/11/2026 | "Cách tìm crossover point? Crossover point này đã hợp lí chưa? Cần vẽ trong excel thì làm sao?" | Gemini | Đưa công thức tính Crossover point vào file giải trình thuật toán (`Self_Explanation.md`). Làm theo hướng dẫn của AI để thiết lập 2 trục X, Y sang Logarithmic scale và vẽ biểu đồ phân tán (Scatter) trên Excel. |
----------------------
## Tuần 4
# Nhật ký sử dụng AI (AI Usage Log)

| Ngày | Lời nhắc (Prompt/Question) | Công cụ AI | Cách nhóm áp dụng vào dự án |
| :--- | :--- | :--- | :--- |
| 03/11/2026 | "Đây là nhận xét của giáo viên, hãy cho tôi biết tôi cần làm gì" | Gemini | Phân tích nhận xét của giảng viên, xác định các công việc trọng tâm cần hoàn thiện cho báo cáo tổng kết và buổi bảo vệ đồ án. |
| 03/11/2026 | "Bây giờ hãy giải quyết từ phần 3" | Gemini | Viết báo cáo đối chiếu thời gian thực tế so với lý thuyết Big-O. Thêm tính năng "Demo Thuyết Trình" vào `main.cpp` để so sánh tốc độ trực tiếp trên Terminal. |
| 03/11/2026 | "cho tôi cái file readme hoàn chỉnh" | Gemini | Tổng hợp và định dạng file `README.md` chuẩn Markdown, bao gồm bảng số liệu đối chiếu và cú pháp chèn ảnh đồ thị. |
| 03/11/2026 | "Hãy tạo cho tôi cái ảnh benchmark_chart.png" | Gemini | Vẽ đồ thị Crossover Point hiển thị trực quan sự chênh lệch thời gian (Log Scale) giữa Suffix Array và Naive Search. |