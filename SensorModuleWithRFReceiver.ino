#include <VirtualWire.h>

const int pinOutputLed = 13;
const char expectedMessage[5] = {'b','o','o','m'};
char actualMessage[5];

void setup() {                
  pinMode(pinOutputLed, OUTPUT);     
  vw_setup(2000); //Bits per sec
  vw_rx_start();
  
  Serial.begin(9600);
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  
  if (vw_get_message(buf, &buflen)) // Non-blocking 
  {
    Serial.print("New message in: ");
    int i; 
    for (i = 0; i < buflen; i++) {
      actualMessage[i] = buf[i];
    }
    Serial.println(actualMessage);
    
    if (IsMessageValid()){
      digitalWrite(pinOutputLed, HIGH); 
      delay(1000);
      digitalWrite(pinOutputLed, LOW); 
    }
  }
}

boolean IsMessageValid(){
  if ((actualMessage[0] == expectedMessage[0]) && (actualMessage[1] == expectedMessage[1]) && (actualMessage[2] == expectedMessage[2]) && (actualMessage[3] == expectedMessage[3]))
    return true;
  else
    return false;
}
