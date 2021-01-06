#include <SoftwareSerial.h>

SoftwareSerial btSerial(2,3);

int SensorPin = A0;

void setup()
{
  Serial.begin(9600);
  btSerial.begin(9600);
}

void loop()
{

  int SensorReading = analogRead(SensorPin);
  int mfsr_r18 = map(SensorReading, 0, 1024, 0, 255);
  Serial.println(mfsr_r18);
  //delay(1000);

  if(mfsr_r18 > 100){
        btSerial.write("1");      
  } else {
        btSerial.write("0");              
  }

  if(btSerial.available()){
    while(btSerial.available()){
      Serial.write(btSerial.read());
    }
  }
}
