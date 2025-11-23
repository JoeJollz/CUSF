#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <SD.h>

Adafruit_BMP085 bmp; // creating an object called bmp. bmp is the instance i use to called functions. 
File logFile;  // variable name 'logFile' of type file. Can write into this file as well. 

<<<<<<< HEAD
const int chipSelect = 5; // SD card CS pin on ArduinoNano
=======
const int chipSelect = 10; // SD card CS pin on ArduinoNano
>>>>>>> 271e95edf60452da15e1e5dc73dd8d2fb28255d5

void setup() {
  Serial.begin(9600); 
  Wire.begin(); 
  if (!bmp.begin()) { // bmp.being() attempts to initialise the sensor. ! = not. 
    //Serial.println("Could not connect to BMP180 sensor.");
    while (1);
  }

  if (!SD.begin(chipSelect)) { // SD.begin() attempts to initialise the SD card reader.
    //Serial.println("SD card init failed"); 
    while (1);
  }
  Serial.println("SD card initialised");

  logFile = SD.open("data.txt", FILE_WRITE);
  if (!logFile) {
    //Serial.println("Failed to open data.txt");
    while (1);
  }
  //Serial.println("logging started");
}

void loop() {
  float temperature = bmp.readTemperature();
<<<<<<< HEAD

  float pressure = bmp.readPressure() / 100.0; // hPa
  pressure -= 200  // set initial pressure to 0 for first 10 entries. So measures relative pressure.
=======
  float pressure = bmp.readPressure() / 100.0; // hPa
>>>>>>> 271e95edf60452da15e1e5dc73dd8d2fb28255d5

 // Serial.print("Temp: ");
 // Serial.print(temperature);
 // Serial.print(" °C, Pressure: ");
 // Serial.print(pressure);
 // Serial.println(" hPa")

  logFile.print(millis());
  logFile.print(", ");
  logFile.print(temperature);
  logFile.print(", ");
  logFile.println(pressure); 
<<<<<<< HEAD
  logFile.flush() // change fliushing to only once in 1000. 

  //delay(100);
=======
  logFile.flush()

  delay(100);
>>>>>>> 271e95edf60452da15e1e5dc73dd8d2fb28255d5
  
}
