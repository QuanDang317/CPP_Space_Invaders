🎮 Giới thiệu Game: Space Invaders (C++ + Raylib)
1. Tổng quan
Space Invaders là trò chơi bắn súng không gian cổ điển, được nhóm mình phát triển lại bằng ngôn ngữ C++ và sử dụng thư viện Raylib – một thư viện mã nguồn mở hiện đại, đơn giản, và mạnh mẽ để lập trình game 2D.
________________________________________
 2. Công nghệ sử dụng
•	Ngôn ngữ lập trình: C++
•	 Thư viện đồ họa: Raylib
•	 Hướng tiếp cận: Lập trình hướng đối tượng (OOP)
•	 Điều khiển: Qua bàn phím (keyboard input)
________________________________________
3. Cách chơi
Người chơi điều khiển một tàu vũ trụ dưới đáy màn hình, bắn đạn để tiêu diệt các hàng quái vật ngoài hành tinh đang di chuyển dần xuống. Nếu quái vật chạm đáy, hoặc người chơi hết mạng, trò chơi sẽ kết thúc.
 Điều khiển:
Chức năng	Phím điều khiển
Di chuyển sang trái	← 
Di chuyển sang phải	→ 
Bắn đạn	Space (Phím cách)
Thoát game	Esc
________________________________________
 4. Các tính năng nổi bật
•	Giao diện retro theo phong cách pixel-art cổ điển.
•	 Có hệ thống Level, Score, High Score, mạng sống hiển thị rõ ràng.
•	 Hệ thống hàng rào phòng thủ có thể bị phá hủy.
•	 Hiệu ứng đạn bay, va chạm, và âm thanh (nếu tích hợp).
•	 Tăng độ khó theo thời gian (speed up / thêm enemy).
________________________________________
5. Lý do chọn Raylib
   - Đơn giản, dễ học, dễ tích hợp với C++, quản lý tốt input, audio, graphics 2D., hỗ trợ nhiều nền tảng: Windows, Linux, macOS.
Qua đây bọn mình muốn giới thiệu sơ qua về thư viện Raylib:
Giới Thiệu Raylib - Thư viện lập trình game đơn giản, mạnh mẽ
Raylib là một thư viện mã nguồn mở được thiết kế để giúp các lập trình viên dễ dàng phát triển game 2D (và một phần 3D). Raylib đặc biệt thích hợp cho những người mới học lập trình game, sinh viên, hoặc những dự án đơn giản và nhanh gọn.
•	 Thiết kế với mục tiêu: Đơn giản, rõ ràng, dễ học
•	 Viết bằng C nhưng có thể dùng tốt trong C++
•	 Được hỗ trợ trên Windows, Linux, macOS, Web (HTML5), và nhiều nền tảng khác.
Cách Raylib hoạt động (áp dụng vào game của nhóm bạn)
Raylib cung cấp các hàm đơn giản để xử lý các chức năng cơ bản khi lập trình game:
Chức năng	Hàm Raylib tiêu biểu
Khởi tạo cửa sổ	InitWindow(width, height, title)
Đóng cửa sổ game	CloseWindow()
Xử lý vòng lặp game chính	while (!WindowShouldClose())
Vẽ hình ảnh, sprite	DrawTexture(), DrawRectangle()
Xử lý phím bấm	IsKeyDown(), IsKeyPressed()
Cập nhật màn hình	BeginDrawing(), EndDrawing()
Tải ảnh / âm thanh	LoadTexture(), LoadSound()
6. Một số hình ảnh minh họa
  chua update
 7. Định hướng phát triển
•	Thêm hệ thống nâng cấp vũ khí
•	Thêm nhiều loại kẻ địch khác nhau
•	Tích hợp âm thanh và nhạc nền
•	Tối ưu hiệu suất cho các thiết bị yếu
Phân Tích Thiết Kế Game Của Nhóm
 1. Giao diện người chơi (UI)
•	Phong cách: Nhóm đã chọn phong cách retro pixel-art đúng chất Space Invaders gốc, tạo cảm giác hoài cổ và đơn giản nhưng dễ nhìn.
•	Màu sắc: Tông nền đen kết hợp với màu vàng và xanh tạo độ tương phản cao, giúp người chơi dễ tập trung vào nhân vật và đạn.
•	Hiển thị thông tin rõ ràng:
o	Góc trên trái: SCORE (điểm hiện tại)
o	Góc trên phải: HIGH-SCORE (điểm cao nhất)
o	Góc dưới phải: LEVEL 01 (mức chơi hiện tại)
o	Góc dưới trái: 3 biểu tượng tàu = 3 mạng
 2. Thiết kế kẻ địch
•	Gồm nhiều loại kẻ địch khác nhau:
o	Hàng trên cùng: tàu mẹ màu cam – có thể là loại mạnh nhất.
o	Các hàng giữa: kẻ địch tầm trung – nhiều hơn, dễ tiêu diệt hơn.
o	Kẻ địch được bố trí theo lưới ma trận, đúng phong cách truyền thống.
•	Kẻ địch có hiệu ứng khi trúng đạn (trong hình có vài địch đang nổ), cho thấy có xử lý va chạm tốt.
3. Tàu người chơi
•	Được đặt ở chính giữa cạnh dưới màn hình, dễ điều khiển và phù hợp với game loop dạng bắn lên.
•	Có ba mạng, biểu tượng được thể hiện bằng 3 chiếc tàu nhỏ góc dưới bên trái.
 4. Hệ thống phòng thủ
•	Có 4 khối chắn màu vàng: là hàng rào phòng thủ, giúp chắn đạn từ kẻ địch.
•	Thiết kế có lỗ hổng bị bắn phá, chứng tỏ nhóm đã xử lý tốt việc thay đổi sprite (hoặc texture) theo sát thương.
5. Đạn và va chạm
•	Đạn từ tàu người chơi đi lên, đạn kẻ địch đi xuống (thể hiện rõ bằng vệt đạn màu vàng).
•	Trong ảnh có ít nhất 3 viên đạn đang bay, cho thấy hệ thống bắn đạn đã hoạt động tốt.
 6. Bố cục màn hình
•	Mọi thành phần được đặt đối xứng và cân đối.
•	Khung vàng bao quanh tạo cảm giác cổ điển như máy arcade thật.
•	Việc chia khu vực rõ ràng giúp người chơi dễ quan sát:
o	Trên: kẻ địch 	Giữa: phòng thủ		Dưới: người chơi
