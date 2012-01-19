#include <VirtualWire.h>

const int pinOutputLed = 13;
const int pinOutputSensorTriggered = 2;
const int pinInputSensor1 = 3;

const char expectedMessage[5] = {'b','o','o','m'};
char actualMessage[5];

void setup() {                
  pinMode(pinOutputLed, OUTPUT);     
  pinMode(pinOutputSensorTriggered, OUTPUT);
  pinMode(pinInputSensor1, INPUT);

  vw_setup(2000); //Bits per sec
  vw_rx_start();
  
  Serial.begin(9600);
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  
  //listening for wireless sensors
  if (vw_get_message(buf, &buflen)) // Non-blocking 
  {
    Serial.print("New message in: ");
    int i; 
    for (i = 0; i < buflen; i++) {
      actualMessage[i] = buf[i];
    }
    Serial.println(actualMessage);
    
    if (IsValidMessage())
      NotifySensorTriggered();
  }
  
  //checking wired sensors
  if (digitalRead(pinInputSensor1) == HIGH)
    NotifySensorTriggered();

}

boolean IsValidMessage(){
  if ((actualMessage[0] == expectedMessage[0]) && (actualMessage[1] == expectedMessage[1]) && (actualMessage[2] == expectedMessage[2]) && (actualMessage[3] == expectedMessage[3]))
    return true;
  else
    return false;
}

void NotifySensorTriggered(){
  digitalWrite(pinOutputLed, HIGH); 
  digitalWrite(pinOutputSensorTriggered, HIGH); 
  delay(2000);
  digitalWrite(pinOutputLed, LOW); 
  digitalWrite(pinOutputSensorTriggered, LOW); 
}

