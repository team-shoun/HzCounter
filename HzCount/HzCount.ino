#define analogPin 1;
#include <Adafruit_SSD1306.h>  //OLED用ライブラリ
#define SCREEN_WIDTH 128       // OLEDディスプレイの幅（ピクセル単位）
#define SCREEN_HEIGHT 32       // OLEDディスプレイの高さ（ピクセル単位）

int startMillis;
int count;

int threshold = 512;

void displaySet() {
  display.clearDisplay();               // Clear the buffer
  display.setTextSize(1);               // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);  // Draw white text
  display.setCursor(0, 0);              // Start at top-left corner
}

void starting() {
  displaySet();
  display.println("Hz Countor");
  display.println("made by");
  display.println("Robotics");
  display.display();
  delay(1000);
}

void setup() {
  Serial.begin(9600);
  pinMode(analogPin, INPUT);
  //SSD1306_SWITCHCAPVCC = 内部で3.3Vからディスプレイ電圧を生成する
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 の割り当てに失敗しました"));
    for (;;)
      ;  //先に進まないで、永遠にループする
  }
  Serial.println("OLED OK...");
  display.clearDisplay();  //バッファをクリアする
  display.display();
  starting();
}

void loop() {
  startMillis = millis();
  count = 0 while (millis() - startMillis < 1000) {
    while (analogRead(analogPin) > threshold) {
      delay(0);
    }
    while (analogRead(analogPin) < threshold) {
      delay(0);
    }
    count += 1;
  }
  float Hz = (count / time) * 1000;  //1秒あたりの振動数
  displaySet();
  display.print(Hz);
  display.print(" Hz");
  display.display();
}
