#ifndef BMP_UTILS_H_
#define BMP_UTILS_H_

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

namespace BMP_Utils {

void setup();
String generateTempString(float bmpTemp);
String generatePresString(float bmpPress);
String readDataSensor();

}

#endif