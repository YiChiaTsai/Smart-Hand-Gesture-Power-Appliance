//#include <SoftwareSerial.h>   // 引用程式庫
 
// 定義連接藍牙模組的序列埠
//SoftwareSerial BT(8, 9); // 接收腳, 傳送腳
char val;  // 儲存接收資料的變數
 
void setup() {
  Serial.begin(38400);   // 與電腦序列埠連線
  Serial.println("Household Remote Control is ready!");
 
  // 藍牙透傳模式的預設連線速率。
  Serial1.begin(38400);
}
 
void loop() {
  // 若收到「序列埠監控視窗」的資料，則送到藍牙模組
  if (Serial.available()) {
    val = Serial.read();
    Serial1.print(val);
  }
 
  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
  if (Serial1.available()) {
    val = Serial1.read();
    Serial.print(val);
  }
}
