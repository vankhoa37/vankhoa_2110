# Chess Game

1. **Xem Demo Game tại:** [https://youtu.be/Jduux9_fKS8](https://youtu.be/Jduux9_fKS8)

2. **Hướng dẫn cách tải:**
   - 2.1 Tải game bao gồm source code tại:
   - 2.2 Tải game không bao gồm source code:

3. **Cấu trúc Game**
   - Game bao gồm 3 phần chính:
     - **3.1 Người đấu với người:**
       - Hai người chơi trên cùng một máy tính.
       - Bàn cờ tự động xoay sau mỗi nước đi.
       - Mỗi người chơi có một lượt trợ giúp.
     - **3.2 Người với máy:**
       - Người chơi chơi với một con bot AI (stockfish 5).
       - Sử dụng hàm connector1 để kết nối với phần mềm AI và lấy nước đi.
     - **3.3 Giải đố:**
       - Bao gồm 4 màn giải đố với các câu đố khác nhau và độ khó tăng dần.
       - Người chơi cần tìm ra các nước đi chuẩn xác để tiếp tục ván cờ.

4. **Về phần source code:**
   - **4.1 Các hàm chung:**
     - Board[8][8]
     - loadPosition
     - isPositionInsideRect
     - isValidMove
     - handlePieceMovement
     - isCastling
     - castling
   - **4.2 Các hàm riêng:**
     - stokfishMove
     - stockFishMovePromote
     - x
   - **4.3 Các file .hpp:**
     - Connector1.hpp: Kết nối với AI và nhận nước đi.
     - Promotechess.hpp: Xử lý phong cấp cho nước đi của AI.
     - chooseChessPromote.hpp: Hiển thị bảng chọn quân cờ để thực hiện phong cấp.
     - suggest_printer.hpp: In gợi ý lên màn hình cho người chơi.
     - music.hpp: Chứa các hàm tạo âm thanh cho trò chơi.
     - SDL2ImageRender: Thực hiện chuyển đổi ảnh để tạo menu dựa trên các ảnh có sẵn.

5. **Phần tham khảo và đồ họa cho game**
   - **5.1 Tham khảo Code:**
     - YTB FamTrinli: Tham khảo phần connector1.hpp và chỉnh sửa để phù hợp với chương trình.
   - **5.2 Đồ họa cho game:**
     - Bàn cờ và các quân cờ: YTB FamTrinli.
     - Phần các ảnh menu: Capture màn hình game Master Chess.
     - Các hình ảnh khác: Tổng hợp từ nhiều nguồn khác nhau.
     - Âm thanh cho game: Chủ yếu lấy từ fixabay.com.
