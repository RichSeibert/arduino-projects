#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  DDRD |= B00000100; 
}

void loop() {
  delay(50);
  int prox = sonar.ping_cm();
  delay(50);
  prox += sonar.ping_cm();
  delay(50);
  prox += sonar.ping_cm();
  prox /= 3;

  if(prox<=100){
    int x;
    while(sonar.ping_cm()<100 && sonar.ping_cm()>=0){
      x=0;
      while(x<150){ //activate servo
      PORTD |= B0000100;
      delayMicroseconds(1000);
      PORTD &= B1111011;
      delayMicroseconds(3000); 
      x++; 
      }
    }
        
    while(x>=150 && x<300){ //reset servo to original position
      PORTD |= B0000100;
      delayMicroseconds(2000);
      PORTD &= B1111011;
      delayMicroseconds(2000);  
      x++;
    }
  }
}
