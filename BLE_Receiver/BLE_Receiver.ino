//#include <SoftwareSerial.h>   // 引用程式庫
 
// 定義連接藍牙模組的序列埠
//SoftwareSerial BT(8, 9); // 接收腳, 傳送腳
char val;  // 儲存接收資料的變數
const byte LED_PIN = 13;  // 定義LED腳位
const byte RELAY1_PIN = 12;
const byte RELAY2_PIN = 2;

void setup() {
  // 設定HC-05藍牙模組，AT命令模式的連線速率。
  Serial1.begin(38400);
  pinMode(LED_PIN, OUTPUT);
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
}
 
void loop() {
  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
  if (Serial1.available()) {
    val = Serial1.read();
    if (val == '1') { ////Bulb OFF
      digitalWrite(LED_PIN, HIGH);
      digitalWrite(RELAY2_PIN, HIGH);
      Serial.println("Bulb OFF, and LED ON");
      // 回應命令發送端，告知「已關電燈泡、開LED燈」
      Serial1.println("Bulb OFF, and LED ON");
    } else if (val == '0') { //Bulb ON
      digitalWrite(LED_PIN, LOW);
      digitalWrite(RELAY2_PIN, LOW);
      Serial.println("Bulb ON, and LED OFF");
      // 回應命令發送端，告知「已開電燈泡、關LED燈」
      Serial1.println("Bulb ON, and LED OFF");
    } else if (val == '3') { //Fan OFF
      digitalWrite(RELAY1_PIN, HIGH);
      Serial.println("Fan OFF");
      // 回應命令發送端，告知「已關燈」
      Serial1.println("Fan OFF");
    } else if (val == '2') { //Fan ON
      digitalWrite(RELAY1_PIN, LOW);
      Serial.println("Fan ON");
      // 回應命令發送端，告知「已關燈」
      Serial1.println("Fan ON");
    }
    
  }
}
