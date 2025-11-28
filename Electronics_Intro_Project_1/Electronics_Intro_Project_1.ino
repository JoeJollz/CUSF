#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <SD.h>
//test connection. 
Adafruit_BMP085 bmp; // creating an object called bmp. bmp is the instance i use to called functions. 
File logFile;  // variable name 'logFile' of type file. Can write into this file as well. 

const int chipSelect = 5; // SD card CS pin on ArduinoNano
// Constants for the Barometric formula. (Apporximately accurate up to 10km)
const float T0 = 288.15; // Temp in kelvin, maybe we could change this so T = the first temp entry from our BMP data.
const float L = 0.0065; // rate of temp decrease with increasing altitude. 
const float R = 287.05; // units of J/kgK, 
const float P0 = 101325.0; // pressure in pascal at sea level. 
const float g = 9.80665; // gravity accel (m/s2)
// Defining some initial global variables.
float pressure_init; // variable to store the initial starting pressure
float altitude_init; // variable to store the corresponding starting altitude. 

// applying the barometric fomula for calc altitude. 
float calculateAltitude(float P) {

  float coeff = T0/L;
  float P_ratio = P/P0;
  float expon = -(R*L)/g;
  float alti = coeff * (pow(P_ratio, expon) - 1.0); // applying the barometric formula.
  return alti; // returning the altitude in meters. 
}

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

  pressure_init = bmp.readPressure(); // Pa reading, starting pressure.
  Serial.print("Initial pressure (Pa): ");
  Serial.println(pressure_init);
  altitude_init = calculateAltitude(pressure_init);
  Serial.print("Initial altitude (m): ");
  Serial.println(altitude_init);
  

  logFile = SD.open("data.txt", FILE_WRITE);
  if (logFile) {
    logFile.println("Time(ms),Temperature(C),Pressure(Pa),ABS Altitude(m),Rel Altitude(m)");
    logFile.flush();
    Serial.println("Logging started");
  }  else {
    Serial.println("Failed to open data.txt");
  }
}

void loop() {
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure() ; // Pa
  float abs_altitude = calculateAltitude(pressure);
  float rel_altitude = abs_altitude - altitude_init; 

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" °C, Pressure: ");
  Serial.print(pressure);
  Serial.print(" Pa, Abs Altitude: ");
  Serial.print(abs_altitude);
  Serial.print(" m, Relative altitude: ");
  Serial.print(rel_altitude);
  Serial.println(" m");

  logFile.print(millis());
  logFile.print(",");
  logFile.print(temperature);
  logFile.print(",");
  logFile.print(pressure);
  logFile.print(",");
  logFile.print(abs_altitude); 
  logFile.print(",");
  logFile.println(rel_altitude);
  logFile.flush();
}
