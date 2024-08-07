#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C  

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200); // Mở cổng serial với tốc độ 115200 bps

  // Khởi tạo giao diện I2C và màn hình OLED
  Wire.begin(14, 12);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Dừng chương trình nếu khởi tạo màn hình OLED thất bại
  }

  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  // Kiểm tra xem có dữ liệu nào được gửi đến cổng serial hay không
  if (Serial.available() > 0) {
    // Đọc toàn bộ dữ liệu từ cổng serial
    String received = Serial.readString();
    Serial.println("Received: " + received);

    display.clearDisplay();
    
  
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);

    // In thông điệp nhận được lên màn hình OLED
    display.println("Received:");
    display.println(received);
    display.display();
  }
}
