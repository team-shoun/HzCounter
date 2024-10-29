#include <Adafruit_SSD1306.h>  // OLED 用ライブラリ

// OLED 処理
#define SCREEN_WIDTH 128     // OLED ディスプレイの幅 (ピクセル単位)
#define SCREEN_HEIGHT 32     // OLED ディスプレイの高さ (ピクセル単位)
#define OLED_RESET 4         // リセット ピン番号 (Arduino リセット ピンを共有する場合は -1)
#define SCREEN_ADDRESS 0x3C  // アドレスについてはデータシートを参照。128x64 の場合は 0x3D、128x32 の場合は 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define ANALOG_PIN A1
#define THRESHOLD 512
#define NUM_SAMPLES 10

float frequencies[NUM_SAMPLES];
byte sampleIndex = 0;
float averageFrequency = 0;

void setup() {
  pinMode(13, OUTPUT);
  Wire.begin();
  Serial.begin(9600);
  pinMode(ANALOG_PIN, INPUT);

  // SSD1306_SWITCHCAPVCC = 内部で 3.3V からディスプレイ電圧を生成する
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 の割り当てに失敗しました"));
    for (;;)
      ;  // 先に進まないで、永遠にループする
  }
  Serial.println("OLED OK...");

  display.clearDisplay();  // バッファをクリアする
  display.display();
  starting();
}

void displaySet() {
  display.clearDisplay();               // バッファをクリアする
  display.setTextSize(1);               // 通常 1:1 ピクセルスケール
  display.setTextColor(SSD1306_WHITE);  // 白いテキストを描画
  display.setCursor(0, 0);              // 左上隅から開始
}

void starting() {
  displaySet();
  display.println("Hz Counter");
  display.println("made by");
  display.println("Robotics");
  display.display();
  delay(1000);
}

void loop() {
  long startMillis = millis();
  digitalWrite(13, HIGH);
  while (analogRead(ANALOG_PIN) > THRESHOLD) {
    delay(0);
  }
  while (analogRead(ANALOG_PIN) < THRESHOLD) {
    delay(0);
  }
  digitalWrite(13, LOW);
  sampleIndex += 1;
  float elapsedTime = millis() - startMillis;
  float frequency = (1000 / elapsedTime);  // 1 秒あたりの振動数

  if (sampleIndex >= NUM_SAMPLES) {
    sampleIndex = 0;
    float sum = 0;
    for (byte i = 0; i < NUM_SAMPLES; i++) {
      sum += frequencies[i];
    }
    averageFrequency = sum / NUM_SAMPLES;
  }
  // 平均周波数を表示する
  displaySet();
  display.print("Result: ");
  display.print(frequency);
  display.println(" Hz");
  display.print("Avg: ");
  display.print(averageFrequency);
  display.println(" Hz");
  display.display();
}