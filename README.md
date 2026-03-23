# HỆ THỐNG QUẢN LÝ LỊCH HỌC VÀ THỜI KHÓA BIỂU (Case Study 4)

Dự án **Case_Study_4** là một ứng dụng console được phát triển bằng ngôn ngữ C++ với mục tiêu quản lý lịch học và thời khóa biểu của sinh viên/giảng viên. Ứng dụng này được xây dựng bởi **Nhóm 4**.

## 🌟 Tính Năng Chính
Hệ thống cung cấp một menu tương tác cho phép người dùng dễ dàng thực hiện các thao tác:
* **Thêm lớp học mới**: Nhập và lưu trữ thông tin của một môn học/lớp học mới vào hệ thống.
* **Xóa lớp học**: Gỡ bỏ thông tin của lớp học không còn tồn tại.
* **Cập nhật thông tin lớp học**: Chỉnh sửa dữ liệu của các lớp học đã được tạo trước đó.
* **Tìm kiếm mạnh mẽ**: Hỗ trợ tra cứu nhanh chóng lớp học thông qua Mã Môn Học hoặc Tên Môn Học.
* **Hiển thị danh sách đa dạng**: In ra danh sách các lớp học được sắp xếp theo Mã Môn Học, Tên Môn Học, hoặc theo Thời Gian để dễ dàng theo dõi.
* **Kiểm tra hiệu năng (Demo)**: Chức năng tích hợp sẵn để đánh giá hiệu suất (performance) của các thuật toán và cấu trúc dữ liệu đang sử dụng.

## 🛠 Cấu Trúc Đối Tượng & Dữ Liệu
Chương trình được thiết kế theo hướng đối tượng (OOP), với các lớp cốt lõi bao gồm:
* **Lớp `Time`**: Quản lý thông tin thời gian bắt đầu học với các thuộc tính Giờ (`Hours`) và Phút (`Minutes`). Lớp này được nạp chồng (overload) các toán tử so sánh (`<`, `>`, `==`) để phục vụ cho việc sắp xếp lịch học theo thời gian.
* **Lớp `Class`**: Lưu trữ toàn bộ thông tin chi tiết của một lớp học, bao gồm: Mã môn học (`Sub_id`), Tên môn học (`Sub_name`), Thời gian bắt đầu (`Start_Time`), Tên giảng viên (`Teacher_name`), và Số tín chỉ (`Credits`).

## 🚀 Hướng Dẫn Cài Đặt và Chạy Chương Trình
1. **Môi trường yêu cầu**: Bất kỳ trình biên dịch C++ nào (khuyến nghị sử dụng Visual Studio vì dự án bao gồm các thiết lập môi trường cho Visual Studio).
2. **Biên dịch và thực thi**: 
   * Compile project và chạy file `Main.cpp`. 
   * Tại file `Main.cpp`, chương trình sẽ tự động khởi tạo luồng xử lý `Function` và giao diện `Menu`, sau đó gọi hàm `ChayMenu()` để bắt đầu vòng lặp tương tác.
3. **Sử dụng**: Làm theo các chỉ dẫn trên màn hình, nhập các phím số tương ứng (từ 0 đến 9) để gọi các tính năng. Nhấn `0` khi muốn thoát chương trình.

---
*Kho lưu trữ này thuộc về bài tập Case Study môn học Cấu trúc Dữ liệu và Giải thuật.*
