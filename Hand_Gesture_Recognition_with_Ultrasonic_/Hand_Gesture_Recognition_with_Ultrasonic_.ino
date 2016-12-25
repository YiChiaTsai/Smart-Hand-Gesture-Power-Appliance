/*
 * HCSR04Ultrasonic/examples/UltrasonicDemo/UltrasonicDemo.pde
 *
 * SVN Keywords
 * ----------------------------------
 * $Author: cnobile $
 * $Date: 2011-09-17 02:43:12 -0400 (Sat, 17 Sep 2011) $
 * $Revision: 29 $
 * ----------------------------------
 */

#include <Ultrasonic.h>
//#include <SoftwareSerial.h>   // 引用程式庫
 
// 定義連接藍牙模組的序列埠
//SoftwareSerial BT(8, 9); // 接收腳, 傳送腳
char val;  // 儲存接收資料的變數

#define TRIGGER_PIN1  10
#define ECHO_PIN1     11

#define TRIGGER_PIN2  12
#define ECHO_PIN2     13

Ultrasonic ultrasonic1(TRIGGER_PIN1, ECHO_PIN1);
Ultrasonic ultrasonic2(TRIGGER_PIN2, ECHO_PIN2);

int usIndex = 0;
float usSerial1[10] = {0};
float usSerial2[10] = {0};

float usAvg1 = 0;
float usAvg2 = 0;

int usSmiliarDiff = -1;
int usState = -1;
int usStateTemp = -2;
//0: Right To Left (Open Bulb)
//1: Left To Right (Close Bulb)
//2: Foward To Back
//3: Back To Foward
//4: Top To Down (Open Fan)
//5: Down To Top (Close Fan)

unsigned long previousMillis = 0;
const long interval = 3000;

void setup() {
  Serial.begin(38400);   // 與電腦序列埠連線
  Serial.println("Household Remote Control is ready!");
 
  // 藍牙透傳模式的預設連線速率。
  Serial1.begin(38400);
  
  previousMillis = millis();
}

void loop() {
  float cmMsec1, cmMsec2; 
//  float inMsec;
  long microsec1 = ultrasonic1.timing();
  long microsec2 = ultrasonic2.timing();

  cmMsec1 = ultrasonic1.convert(microsec1, Ultrasonic::CM);
  cmMsec2 = ultrasonic2.convert(microsec2, Ultrasonic::CM);
//  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);

  Serial.print("MS1: ");
  Serial.print(microsec1);
  Serial.print(", CM1: ");
  Serial.print(cmMsec1);
  Serial.print(", usAvg1: ");
  Serial.print(usAvg1);
  Serial.println();
  Serial.print("MS2: ");
  Serial.print(microsec2);
  Serial.print(", CM2: ");
  Serial.print(cmMsec2);
  Serial.print(", usAvg2: ");
  Serial.print(usAvg2);
  Serial.println();
  Serial.println(usState);
  Serial.println();

//  Serial.print(", IN: ");
//  Serial.println(inMsec);
  delay(100);

//  if(usIndex < 10) {
//    usAvg1 += cmMsec1;
//    usAvg2 += cmMsec2;
//    usIndex = usIndex + 1;
//  } else if (usIndex == 10) {
//    usAvg1 /= 10;
//    usAvg2 /= 10;
//    usIndex = usIndex + 1;
//  }

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
  
    if( abs(cmMsec1 - cmMsec2) > 100){
      
      if(cmMsec1 < cmMsec2){ //From right to left
        if(usState == 1){
            usState = -1;
        } else if(usState == -1){
          if(abs(abs(cmMsec1 - cmMsec2) - usSmiliarDiff) > 50) {
            usState = 0;
    //        Serial.println("Fuck From right to left, and open bulb");
            Serial.println("From RRR");
          }
        }
      }
      if(cmMsec1 > cmMsec2){ //From left to right
        if(usState == 0){
            usState = -1;
        } else if(usState == -1){
          if(abs(abs(cmMsec1 - cmMsec2) - usSmiliarDiff) > 50) {
            usState = 1;
    //        Serial.println("Fuck From left to right, and close bulb");
            Serial.println("From LLL");
          }
        }
      }
      
    }
    usSmiliarDiff = abs(cmMsec1 - cmMsec2);
  }

  // 若收到「序列埠監控視窗」的資料，則送到藍牙模組
  if (usState == 0) {
    if(usStateTemp != usState)
      Serial1.print('0');
  }else if (usState == 1) {
    if(usStateTemp != usState)
      Serial1.print('1');
  }
 
  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
  if (Serial1.available()) {
    val = Serial1.read();
    Serial.print(val);
  }

  usStateTemp = usState;
  
 }
