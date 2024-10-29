#define analogPin A1
#include <Adafruit_SSD1306.h>  //OLED用ライブラリ
#define SCREEN_WIDTH 128       // OLEDディスプレイの幅（ピクセル単位）
#define SCREEN_HEIGHT 32       // OLEDディスプレイの高さ（ピクセル単位）
// OLED処理
#define OLED_RESET 4         // リセット ピン番号 (Arduino リセット ピンを共有する場合は -1)
#define SCREEN_ADDRESS 0x3C  // アドレスについてはデータシートを参照。128x64 の場合は 0x3D、128x32 の場合は 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

long startMillis;
int count;

int threshold = 512;

void setup() {
  pinMode(13, OUTPUT);
  Wire.begin();
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

void loop() {
  startMillis = millis();
  digitalWrite(13, HIGH);
  while (analogRead(analogPin) > threshold) {
    delay(0);
  }
  while (analogRead(analogPin) < threshold) {
    delay(0);
  }
  digitalWrite(13, LOW);
  float time = millis() - startMillis;
  Serial.println(time);
  float Hz = (1000 / time);  //1秒あたりの振動数
  Serial.println(Hz);
  displaySet();
  display.print(Hz);
  display.print(" Hz");
  display.display();
}
