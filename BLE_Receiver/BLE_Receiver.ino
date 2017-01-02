//#include <SoftwareSerial.h>   // 引用程式庫

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 500;           // interval at which to blink (milliseconds)

// 定義連接藍牙模組的序列埠
//SoftwareSerial BT(8, 9); // 接收腳, 傳送腳
char val;  // 儲存接收資料的變數
const byte LED_PIN = 13;  // 定義LED腳位
const byte RELAY1_PIN = 5; //Bulb
const byte RELAY2_PIN = 6; //Fan
const byte RELAY3_PIN = 7; //Music

const int PIRSensor = 2;     // 紅外線動作感測器連接的腳位
int sensorValue = 0;         // 紅外線動作感測器訊號變數

void setup() {
  // 設定HC-05藍牙模組，AT命令模式的連線速率。
  Serial.begin(38400);
  Serial1.begin(38400);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(RELAY3_PIN, OUTPUT);
  pinMode(PIRSensor, INPUT);

  Serial.println("Receiver: Household Remote Control is ready!");
}
 
void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    
    // 讀取 PIR Sensor 的狀態
    sensorValue = digitalRead(PIRSensor);
    // 判斷 PIR Sensor 的狀態
    if (sensorValue == HIGH) {  //Bulb ON
        digitalWrite(LED_PIN, HIGH);
        digitalWrite(RELAY1_PIN, LOW);
        // 回應命令發送端，告知「已開電燈泡、關LED燈」
        Serial.println("Bulb ON");
//        Serial1.println("Bulb ON");
    } else {  //Bulb OFF
        digitalWrite(LED_PIN, LOW);
        digitalWrite(RELAY1_PIN, HIGH);
        // 回應命令發送端，告知「已關電燈泡、開LED燈」
        Serial.println("Bulb OFF");
//        Serial1.println("Bulb OFF");
    }
  }
  
  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
  if (Serial1.available()) {
    val = Serial1.read();
    if (val == '0') { //Fan ON
      digitalWrite(RELAY2_PIN, LOW);
      Serial.println("Fan ON");
//      Serial1.println("Fan ON");
    } else if (val == '1') { //Fan OFF
      digitalWrite(RELAY2_PIN, HIGH);
      Serial.println("Fan OFF.");
//      Serial1.println("Fan OFF.");
    } else if (val == '2') { //Fan ON
      digitalWrite(RELAY3_PIN, LOW);
      Serial.println("Music ON");
//      Serial1.println("Music ON");
    } else if (val == '3') { //Fan OFF
      digitalWrite(RELAY3_PIN, HIGH);
      Serial.println("Music OFF");
//      Serial1.println("Music OFF");
    } 
  }
  
}
