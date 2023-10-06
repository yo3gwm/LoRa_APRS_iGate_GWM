#include "bmp_utils.h"
#include "configuration.h"
#include "gps_utils.h"
#include "display.h"

#define SEALEVELPRESSURE_HPA (1013.25)
#define HEIGHT_CORRECTION 0             // in meters
#define CORRECTION_FACTOR (8.2296)      // for meters

extern Configuration  Config;
extern String         fifthLine;


namespace BMP_Utils {

Adafruit_BMP280   bmp;

void setup() {
  if (Config.bmp.active) {
    bool status;
    status = bmp.begin(0x76);  // Don't forget to join pins for righ direction on BMP280!
    if (!status) {
      Serial.println("Could not find a valid BMP280 sensor, check wiring!");
      show_display("ERROR", "", "BMP sensor active", "but no sensor found...");
      while (1); // sacar esto para que quede pegado si no encuentra BMP280
    } else {
      Serial.println("init : BMP280 Module  ...     done!");
    }
  } else {
    Serial.println("(BMP not 'active' in 'igate_conf.json')");
  }
}

String generateTempString(float bmpTemp) {
  String strTemp;
  strTemp = String((int)bmpTemp);
  switch (strTemp.length()) {
    case 1:
      return "00" + strTemp;
      break;
    case 2:
      return "0" + strTemp;
      break;
    case 3:
      return strTemp;
      break;
    default:
      return "-999";
  }
}

String generatePresString(float bmpPress) {
  String strPress;
  strPress = String((int)bmpPress);
   switch (strPress.length()) {
    case 1:
      return "000" + strPress + "0";
      break;
    case 2:
      return "00" + strPress + "0";
      break;
    case 3:
      return "0" + strPress + "0";
      break;
    case 4:
      return strPress + "0";
      break;
    case 5:
      return strPress;
      break;
    default:
      return "-99999";
  }
}

String readDataSensor() {
  String wx, tempStr, presStr;
  float newTemp   = bmp.readTemperature();
  float newPress  = (bmp.readPressure() / 100.0F);
  
  if (isnan(newTemp) || isnan(newPress)) {
    Serial.println("BMP280 Module data failed");
    wx = ".../...g...t...r...p...P...h..b.....";
    fifthLine = "";
    return wx;
  } else {
    tempStr = generateTempString((newTemp * 1.8) + 32);
    presStr = generatePresString(newPress + (HEIGHT_CORRECTION/CORRECTION_FACTOR));
    fifthLine = "BMP-> " + String(int(newTemp))+"C " + presStr.substring(0,4) + "hPa";
    wx = ".../...g...t" + tempStr + "r...p...P...h..b" + presStr;
    return wx;
  }
}

}