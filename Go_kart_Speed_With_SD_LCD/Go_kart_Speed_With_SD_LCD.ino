#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(10, 9, 6, 5, 3, 2);
File myFile;
//^^^^^^ used for SD card

int revolution = 0;
int sensor_read = 0; //varaible used to store sensor data
int sensor_threshold = 50; // set value depending on pull-up resistor value 
long start_time = micros(); //millis is the number of microseconds since the program started
long time_diff = 0; //in miliseconds
float w = 0; //angular velocity in revolutions per minute
float wheel_radius = 0.1397; //in meters
float linear_speed = 0; //in MPH
float radius_ratio = 0.1427; //magnet placement radius/wheel radius ????? was .1427
float axel_radius = 0.02;
float meters_per_min_to_MPH = 0.03728;
int i = 0;

void setup() {
Serial.begin(9600);

lcd.begin(16,2);
lcd.print("Speed (MPH)");

while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
}

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

myFile = SD.open("speeds.txt", FILE_WRITE);


if (myFile) {
    myFile.println("--------------------Start--------------------");
    myFile.close();
} 
else {
    // if the file didn't open, print an error:
    Serial.println("error opening file");
}

}




void loop() {
sensor_read = analogRead(A0);

if (sensor_read < sensor_threshold){
  revolution = 1;
  start_time = micros();
}
else {
  revolution = 0;
}

if(revolution == 0){
  long current_time = micros(); //keep updating current time
  time_diff = current_time - start_time;
  i = 1;
}
else{
  if (i == 1){
    
    w = 60000000*((2*3.14159)/time_diff); //revolution per a microsecond converted to angular velocity in rad/min
    linear_speed = (w*axel_radius)*meters_per_min_to_MPH*(1/radius_ratio)/2; 
        Serial.println(linear_speed);
    lcd.setCursor(0,1);
    lcd.print(linear_speed);
    myFile = SD.open("speeds.txt", FILE_WRITE);
    myFile.print(micros());
    myFile.print(", ");
    myFile.println(linear_speed);
    myFile.close();
    
    i = 0;
  }
}


}
