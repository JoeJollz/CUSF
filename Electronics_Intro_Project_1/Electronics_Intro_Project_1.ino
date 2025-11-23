#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <SD.h>

Adafruit_BMP085 bmp; // creating an object called bmp. bmp is the instance i use to called functions. 
File logFile;  // variable name 'logFile' of type file. Can write into this file as well. 

const int chipSelect = 5; // SD card CS pin on ArduinoNano

void setup() {
  Serial.begin(9600); 
  Wire.begin(); 
  while (!bmp.begin()) { // bmp.being() attempts to initialise the sensor. ! = not. 
    Serial.println("Could not connect to BMP180 sensor.");
  }

  while (!SD.begin(chipSelect)) { // SD.begin() attempts to initialise the SD card reader.
    Serial.println("SD card init failed"); 
  }
  
  Serial.println("SD card initialised");

  logFile = SD.open("data.txt", FILE_WRITE);
  while (!logFile) {
    Serial.println("Failed to open data.txt");
  }
  Serial.println("logging started");
}

void loop() {
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0; // hPa

 Serial.print("Temp: ");
 Serial.print(temperature);
 Serial.print(" °C, Pressure: ");
 Serial.print(pressure);
 Serial.println(" hPa");

  logFile.print(millis());
  logFile.print(", ");
  logFile.print(temperature);
  logFile.print(", ");
  logFile.println(pressure); 
  logFile.flush();

  delay(100);
  
}
