long duration;

void setup() {
  // initialize serial communication:
  DDRD |= B00001000; //pin 3 is output to the flight controller into pin 12
}

void loop() {
  
  duration = timer();
  
  if(duration <= 3500 && duration >= 500){  //about 2 feet, equation is 158 per inch
    duration = timer();
    if(duration <=3500 && duration >=500){
      PORTD |= B00001000; 
    } 
  }
  else{
    PORTD &= B11110111;
  }
  delay(50);
}

long timer(){
  DDRD |= B00000100;
  PORTD &= B11111011;
  delayMicroseconds(2);
  PORTD |= B0000100; 
  delayMicroseconds(5);
  PORTD &= B11111011;

  DDRD &= B11111011;
  return pulseIn(2, HIGH);
}

