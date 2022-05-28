# HappyGame

**I. Hướng dẫn cài đặt HappyGame**

- B1: Bấm vào link download file ZIP: https://github.com/lqnquang/HappyGame/archive/refs/heads/main.zip hoặc bấm vào link github: https://github.com/lqnquang/HappyGame , chọn Code, chọn Download ZIP.
     
- B2: Giải nén file ZIP được thư mục HappyGame-main. 

- B3: Truy cập vào thư mục vừa giải nén, tìm và chạy file HappyGame.exe để bắt đầu trò chơi.


**II. Mô tả trò chơi**

HappyGame là trò chơi thể loại phiêu lưu, hành động, 2d. Người chơi sẽ điều khiển nhân vật di chuyển vượt địa hình đồng thời tiêu diệt quái vật trên đường để đạt
điểm cao nhất. Sẽ xuất hiện các đồng xu trên đường mà người chơi cần thu nhập, đồng xu sử dụng để mua đạn, các loại đạn khác nhau sẽ có giá cao hơn, hiệu năng tốt 
hơn và cho điểm số tiêu diệt cao hơn. Mục tiêu của trò chơi là đạt điểm cao nhất một cách tối ưu, sử dụng hiệu quả các đồng xu thu nhập được và tránh bị tiêu diệt 
bởi quái vật.
     
  
**III. Mô tả chi tiết**

- Menu mở đầu gồm 2 chức năng, ô "Play Game" bắt đầu trò chơi, ô "Exit" để thoát trò chơi hoặc người chơi có thể nhấn phím "Esc" để thoát.
     
- Menu kết thúc gồm 2 chức năng, ô "Play again" để bắt đầu lại trò chơi, ô "Exit" để thoát trò chơi.
          
- Sử dụng phím A và D để di chuyển nhân vật sang trái hoặc phải, phím Space để nhảy.
     
- Bấm chuột trái để bắn đạn loại 1, chuột phải để bắn đạn loại 2.
     
     + Đạn 1 có giá 1 xu, tốc độ bình thường, tiêu diệt quái vật được cộng 1 điểm/quái vật.
          
     + Đạn 2 có giá 5 xu, tốc độ gấp đôi, có thể bắn xuyên mục tiêu và được cộng 3 điểm/quái vật.
          
- Quái vật được chia làm 2 loại, xuất hiện tại các vị trí chỉ định trước, có thể di chuyển trong khoảng cách nhất định hoặc bắn đạn về phía trước.
     
- Trò chơi kết thúc khi nhân vật hết mạng hoặc tiêu diệt toàn bộ quái vật.
     
- Lưu ý: trường hợp không thể tiêu diệt hết quái vật, người chơi có thể nhấn phím "0" để kết thúc trò chơi và chọn "play again" ở menu kết thúc (nhân vật sẽ chết 
khi nhấn phím "0", đây là chữa lỗi tạm thời, lỗi này sẽ được cập nhật ở phiên bản sau).
     
**IV. Các kỹ thuật lập trình đã sử dụng**

- Mảng/Mảng hai chiều(vector): sử dụng để vẽ map, lưu danh sách quái vật.
     
- Class: dùng tạo kiểu, VD: nhân vật sẽ xây dựng lớp MainObject, đạn sẽ có lớp BulletObject,...
     
- Dùng các hàm mà sdl2 cung cấp để xây dựng trò chơi, dùng sdl2 để tạo cửa sổ trò chơi, load các hiệu ứng, chèn âm thanh, viết chữ số,...
     
- Sử dụng con trỏ trong khai báo biến, sử dụng tham biến thay cho tham trị.
     
- Tách chương trình thành các file riêng, mỗi file là một chức năng riêng.
     
- Dùng các câu lệnh mà ngôn ngữ c++ cung cấp sẵn.
     
**V. Kết luận, hướng phát triển và các điều tâm đắc rút ra**

- Hướng phát triển: Đầu tiên là sửa một số lỗi nhỏ còn tồn tại, tạo lại menu đầy đủ chức năng hơn, tiếp đó là thêm các tính năng cho trò chơi như các loại đạn 
mới, item hỗ trợ, nhiều loại quái hơn, boss hoặc các miniboss và mở rộng map.

- Kết luận và các điều tâm đắc: HappyGame là thành quả sau một quá trình học hỏi, tìm hiểu và hỗ trợ. Có thể coi đây là sản phẩm đầu tiên em làm ra, mặc dù còn nhiều thiếu sót, cũng như gặp nhiều hạn chế về kiến thức, nhưng HappyGame bao hàm hầu hết vốn hiểu biết của bản thân về lập trình mà em tích lũy được. Trong quá trình xây dựng HappyGame em cũng học hỏi được rất nhiều điều, rèn luyện và trau dồi các kỹ năng cơ bản của một lập trình viên.
