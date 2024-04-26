# vankhoa_2110
**CODE Game ở File Test**
# Chess Game

## Demo
- Xem Demo Game tại: [https://youtu.be/Jduux9_fKS8](https://youtu.be/Jduux9_fKS8)

## Hướng dẫn cách tải
1. Tải game bao gồm source code tại: [https://github.com/vankhoa37/vankhoa_2110.git](https://github.com/vankhoa37/vankhoa_2110.git)
2. Tải game không bao gồm source code: [https://drive.google.com/drive/folders/1Jbh6RKXlXDy81JDpAZotKmdrApRVKb5G?usp=drive_link](link driver)

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
- **Board[8][8]:** mỗi ô trong mảng này lưu trữ giá trị 1 ô trong bàn cờ, các quân cờ khác nhau sẽ có các giá trị khác nhau.
- **loadPosition:** : hàm load các quân cờ lên bàn cờ, quân cờ sẽ được tải trong một ảnh figures, hàm này sẽ cắt các quân cờ trong ảnh theo giá trị của bảng board và load lên bàn cờ
- **isPositionInsideRect:** hàm này kiểm tra xem chuột có trỏ đến 1 quân cờ trong bàn cờ hay không, trong chương trình nếu có sẽ thực hiện các bước điều chỉnh vị trí đến của quân cờ sao cho khớp với ô đến (không bị lệch hoặc quân cờ đứng giao nhiều ô)
- **isValidMove:** : hàm kiểm tra nước đi có phải là đi hợp lệ không (các quân cờ nằm trong bàn cờ và quân cờ không thể có ô bắt đầu và ô kết thúc giống nhau)
- **handlePieceMovement:** : hàm để di chuyển quân cờ theo chuột nhưng chưa làm được(bỏ đi cũng không ảnh hưởng gì đến code)
- **isCastling:** Kiểm tra có thực hiện nhập thành không.
- **castling:** Thực hiện nhập thành.

### 4.2 Các hàm riêng
- **stokfishMove, stockFishMovePromote, x:** : thực hiện các chức năng xử lý nước đi từ dạng chữ để thể hiện lên bàn cờ bằng cách thay đổi giá trị của mảng board

### 4.3 Các file .hpp
- **Connector1.hpp:** Kết nối với AI và nhận nước đi.
- **Promotechess.hpp:** Xử lý phong cấp cho nước đi của AI.
- **chooseChessPromote.hpp:** Hiển thị bảng chọn quân cờ để phong cấp.
- **suggest_printer.hpp:** In gợi ý lên màn hình cho người chơi.
- **music.hpp:** Tạo âm thanh cho trò chơi.
- **SDL2ImageRender:** Thực hiện việc chuyển đổi các ảnh để tạo menu dựa trên các ảnh có sẵn

## Tham khảo và Đồ họa
### 5.1 Tham khảo Code
- **YTB FamTrinli:** Tham khảo phần connector1.hpp để kết nối với một ứng dụng file .exe có sẵn (stockfish.exe), đã chỉnh sửa để phù hợp hơn với chương trình
### 5.2 Đồ họa
- **Bàn cờ và các quân cờ:** YTB FamTrinli.
- **Menu ảnh:** Cap màn hình game Master Chess.
- **Các hình ảnh khác:** Góp nhặt từ nhiều nguồn khác nhau.
- **Âm thanh:** Chủ yếu từ fixabay.com.

