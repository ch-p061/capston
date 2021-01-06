#include <Wire.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial btSerial(2,3);
LiquidCrystal_I2C lcd(0x27, 16, 2);  //lcd 객체 선언

int SensorPin = A0;
int buzzPin = A2;

void setup() {
  Serial.begin(9600);
  btSerial.begin(9600);
  pinMode(buzzPin, OUTPUT);
  //lcd.init();
  lcd.begin(); //LCD 사용시작
  lcd.backlight();
}

void loop() {
  int SensorReading = analogRead(SensorPin);
  int mfsr_r18 = map(SensorReading,0,1024,0,255);
  Serial.println(mfsr_r18);

  if(mfsr_r18 > 30) { // 안장 o
      byte data;
      data = btSerial.read();

      if(data == '1'){ // 헬멧 O     
         digitalWrite(buzzPin, LOW); // 헬멧 o, 안장 o
         lcd.setCursor(0,0);
         lcd.print("Setting Ok!");
      } else {       
         digitalWrite(buzzPin, HIGH); // 헬멧 x, 안장 O
         lcd.setCursor(0,0);
         lcd.print("Wear Helmat");
      }
  } else { // 안장 x
      byte data;
      data = btSerial.read();

      if(data == '0'){ // 헬멧 X      
         digitalWrite(buzzPin, LOW); // 헬멧 X, 안장 X
         lcd.setCursor(0,0);
         lcd.print("Power Off");
      } else {     
         digitalWrite(buzzPin, HIGH); // 헬멧 O , 안장 X
         lcd.setCursor(0,0);
         lcd.print("Break Time!");
      }
  }
}
