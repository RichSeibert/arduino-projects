/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  DDRD |= B00000100; 
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  long x=0;
  while(x<50){
  PORTD |= B0000100;
  delayMicroseconds(2000);
  PORTD &= B1111011;
  delayMicroseconds(2000); 
  x++; 
  }
  while(x>=50 && x<1000){
  PORTD |= B0000100;
  delayMicroseconds(1000);
  PORTD &= B1111011;
  delayMicroseconds(3000);  
  x++;
  }
  Serial.println(x);
}
