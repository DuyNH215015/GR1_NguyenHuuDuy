#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#if true
  #include <siot_core_lib.h>   // SIOT Core Lib - all packages or you could select each package manually.
#else
  #include <WiFiSelfEnroll.h>  // SIOT Core Lib - self setup WiFi network
#endif

// Định nghĩa các thông số cho màn hình OLED
#define SCREEN_WIDTH 128                // Chiều rộng màn hình OLED
#define SCREEN_HEIGHT 64                // Chiều cao màn hình OLED
#define OLED_RESET -1                   // Reset pin của OLED (không sử dụng)
#define SCREEN_ADDRESS 0x3C             // Địa chỉ I2C của OLED

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Handler adhoc wifi station
WiFiSelfEnroll * MyWiFi = new WiFiSelfEnroll();

void setup() {
  Serial.begin(115200);

  // Khởi động màn hình OLED
  Wire.begin(14, 12); // GPIO14 (D5) là SCL, GPIO12 (D6) là SDA
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();  // Hiển thị màn hình trắng trong 2 giây
  delay(2000);
  display.clearDisplay();

  // Thiết lập WiFi
  MyWiFi->setup();
  delay(1000); // Chờ một chút để WiFi kết nối
}

void loop() {
  // Cập nhật trạng thái WiFi
  String deviceID = MyWiFi->GetDeviceID();
  String ssid = MyWiFi->GetSSID();
  String password = MyWiFi->GetPassword();
  
  // Hiển thị thông tin trên màn hình OLED
  display.clearDisplay();
  display.setTextSize(1);      
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println(F("WiFi Info:"));
  display.print(F("ID: "));
  display.println(deviceID);
  display.print(F("SSID: "));
  display.println(ssid);
  display.print(F("Pass: "));
  display.println(password);
  display.display();
  
  // In thông tin ra Serial Monitor để debug
  Serial.println(deviceID);
  Serial.printf("  %s / %s \n", ssid.c_str(), password.c_str());
  
  delay(2000); // Đợi 2 giây trước khi cập nhật lại màn hình
}
