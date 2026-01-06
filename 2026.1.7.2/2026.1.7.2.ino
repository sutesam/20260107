// 定義腳位
const int buttonPin = 4;     // 按鈕連接到 D4
const int ledPin = 3;        // LED 連接到 D3

// 變數設定
int state = 0;               // 狀態計數：0=恆亮, 1=慢閃, 2=中閃, 3=快閃
bool lastButtonState = HIGH; // 紀錄上一次按鈕狀態 (假設使用內建上拉電阻)

void setup() {
  pinMode(ledPin, OUTPUT);
  // 使用 INPUT_PULLUP 讓電路更簡單，按鈕一端接 D4，另一端直接接 GND
  pinMode(buttonPin, INPUT_PULLUP); 
}

void loop() {
  // 1. 偵測按鈕動作 (偵測從高電位變為低電位的瞬間)
  bool currentButtonState = digitalRead(buttonPin);
  
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    state++;          // 切換到下一個狀態
    if (state > 3) {
      state = 0;      // 超過第四種狀態就回到 0 (恆亮)
    }
    delay(50);        // 簡單去彈跳
  }
  lastButtonState = currentButtonState;

  // 2. 根據目前狀態執行對應動作
  switch (state) {
    case 0: // 恆亮
      digitalWrite(ledPin, LOW);
      break;
    
    case 1: // 慢閃爍 (約 1 秒閃一次)
      blinkLED(500);
      break;
    
    case 2: // 不快不慢 (約 0.4 秒閃一次)
      blinkLED(200);
      break;
    
    case 3: // 快閃爍 (約 0.2 秒閃一次)
      blinkLED(100);
      break;
  }
}

// 閃爍副程式：使用 non-blocking 概念或簡單 delay
// 注意：在這裡使用 delay 會影響按鈕靈敏度，但在初學邏輯中較易理解
void blinkLED(int interval) {
  digitalWrite(ledPin, HIGH);
  delay(interval);
  digitalWrite(ledPin, LOW);
  delay(interval);
}