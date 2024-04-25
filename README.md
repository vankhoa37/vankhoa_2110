# Chess Game

## Demo
- Xem Demo Game tại: [https://youtu.be/Jduux9_fKS8](https://youtu.be/Jduux9_fKS8)

## Hướng dẫn cách tải
1. Tải game bao gồm source code tại: 
2. Tải game không bao gồm source code: 

## Cấu trúc Game
Game gồm 3 phần:
1. **Người đấu với người**
   - 2 người chơi trên cùng một máy.
   - Bàn cờ tự xoay sau mỗi nước đi để thuận tiện quan sát.
   - Mỗi người chơi có một lần trợ giúp.
   
2. **Người với máy**
   - Người chơi chơi với một con bot AI (stockfish 5).
   - Sử dụng hàm connector1 để kết nối với phần mềm AI và lấy nước đi.
   - AI trả về các nước đi dưới dạng văn bản để xử lý và đưa lên bàn cờ.

3. **Giải đố**
   - 4 màn giải đố với độ khó tăng dần.
   - Người chơi phải tìm nước đi chuẩn xác để tiếp tục ván cờ.
   - Màn giải đố kết thúc khi người chơi giành ưu thế hoặc chiếu hết cờ.

## Source Code
### 4.1 Các hàm chung
- **Board[8][8]:** Mảng lưu trữ giá trị các ô trong bàn cờ.
- **loadPosition:** Load quân cờ lên bàn cờ từ ảnh.
- **isPositionInsideRect:** Kiểm tra vị trí của chuột trong bàn cờ.
- **isValidMove:** Kiểm tra nước đi có hợp lệ không.
- **handlePieceMovement:** Di chuyển quân cờ (chưa hoàn thiện).
- **isCastling:** Kiểm tra có thực hiện nhập thành không.
- **castling:** Thực hiện nhập thành.

### 4.2 Các hàm riêng
- **stokfishMove, stockFishMovePromote, x:** Xử lý nước đi từ dạng chữ sang bàn cờ.

### 4.3 Các file .hpp
- **Connector1.hpp:** Kết nối với AI và nhận nước đi.
- **Promotechess.hpp:** Xử lý phong cấp cho nước đi của AI.
- **chooseChessPromote.hpp:** Hiển thị bảng chọn quân cờ để phong cấp.
- **suggest_printer.hpp:** In gợi ý lên màn hình cho người chơi.
- **music.hpp:** Tạo âm thanh cho trò chơi.
- **SDL2ImageRender:** Chuyển đổi ảnh để tạo menu.

## Tham khảo và Đồ họa
### 5.1 Tham khảo Code
- **YTB FamTrinli:** Connector1.hpp (đã chỉnh sửa để phù hợp hơn).

### 5.2 Đồ họa
- **Bàn cờ và các quân cờ:** YTB FamTrinli.
- **Menu ảnh:** Cap màn hình game Master Chess.
- **Các hình ảnh khác:** Góp nhặt từ nhiều nguồn khác nhau.
- **Âm thanh:** Chủ yếu từ fixabay.com.
