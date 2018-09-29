#include "cNeigungssensor.h"
#include "EEPROM.h"
#include <sstream>

const char* site PROGMEM = "<html> <head> <title>ESP32 WiFi Test - BNO055 Datenauswertung</title> </head> <body> <script src=\"https://code.jquery.com/jquery-3.3.1.min.js\"></script> <script>$(function() { getData(); setInterval(getData, 90); });function getData() { $.get(\"/sensor_data\", function(data) { var parsed = $.parseJSON(data);$(\"#SENSOR_ORI_X\").text(parsed[\"x\"]); $(\"#SENSOR_ORI_Y\").text(parsed[\"y\"]); $(\"#SENSOR_ORI_Z\").text(parsed[\"z\"]); }) }</script> <h1>ESP32 WiFi Kommunikation Test</h1> <h2>BNO055 Sensordatenanzeige</h2> <p>&nbsp;</p> <h4>Neigung</h4> <table style=\"height: 125px; width: 154px; border-color: black;\" border=\"1\"> <tbody> <tr> <td style=\"width: 25px;\">&nbsp;x</td> <td id=\"SENSOR_ORI_X\" style=\"width: 105px;\">&nbsp;</td> </tr> <tr> <td style=\"width: 25px;\">&nbsp;y</td> <td id=\"SENSOR_ORI_Y\" style=\"width: 105px;\">&nbsp;</td> </tr> <tr> <td style=\"width: 25px;\">&nbsp;z</td> <td id=\"SENSOR_ORI_Z\" style=\"width: 105px;\">&nbsp;</td> </tr> </tbody> </table> </body> </html>";

cNeigungssensor::cNeigungssensor(int bno_addr) 
  : _bno(Adafruit_BNO055(bno_addr)), _calibRestored(false), _refreshRate(100)
{
  //_bno = Adafruit_BNO055(bno_addr);

  if (!_bno.begin())
  {
    Serial.print("BNO055 nicht erkannt. Verkabelung oder I2C Adresse falsch!?");
    // TODO Fehler loggen
    while (1);
  }

  loadCalibrationFromMemory();

  _com.connect("HIT-FRITZBOX-7490", "63601430989011937932");
  _com.attachEvent("/sensor_data", [&](AsyncWebServerRequest* r) 
  {
    sensors_vec_t v;
    v = getEvent().orientation;

    std::stringstream ss;
    ss << "{";
    ss << "\"x\":" << v.x << ", ";
    ss << "\"y\":" << v.y << ", ";
    ss << "\"z\":" << v.z;
    ss << "}";

    r->send(200, "text/plain", ss.str().c_str());

  });

  _com.attachEvent("/sensor", [&](AsyncWebServerRequest* r) 
  {
    r->send(200, "text/html", site);
  });
}


void cNeigungssensor::displaySensorDetails()
{
  sensor_t sensor;
  _bno.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print("Sensor:       "); Serial.println(sensor.name);
  Serial.print("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" xxx");
  Serial.print("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" xxx");
  Serial.print("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" xxx");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}


void cNeigungssensor::displaySensorStatus()
{
  /* Get the system status values (mostly for debugging purposes) */
  uint8_t system_status, self_test_results, system_error;
  system_status = self_test_results = system_error = 0;
  _bno.getSystemStatus(&system_status, &self_test_results, &system_error);

  /* Display the results in the Serial Monitor */
  Serial.println("");
  Serial.print("System Status: 0x");
  Serial.println(system_status, HEX);
  Serial.print("Self Test:     0x");
  Serial.println(self_test_results, HEX);
  Serial.print("System Error:  0x");
  Serial.println(system_error, HEX);
  Serial.println("");
  delay(500);
}


void cNeigungssensor::displayCalStatus()
{
  /* Get the four calibration values (0..3) */
  /* Any sensor data reporting 0 should be ignored, */
  /* 3 means 'fully calibrated" */
  uint8_t system, gyro, accel, mag;
  system = gyro = accel = mag = 0;
  _bno.getCalibration(&system, &gyro, &accel, &mag);

  /* The data should be ignored until the system calibration is > 0 */
  Serial.print("\t");
  if (!system)
  {
      Serial.print("! ");
  }

  /* Display the individual values */
  Serial.print("Sys:");
  Serial.print(system, DEC);
  Serial.print(" G:");
  Serial.print(gyro, DEC);
  Serial.print(" A:");
  Serial.print(accel, DEC);
  Serial.print(" M:");
  Serial.print(mag, DEC);
}


void cNeigungssensor::displaySensorOffsets(const adafruit_bno055_offsets_t &calibData)
{
  Serial.print("Accelerometer: ");
  Serial.print(calibData.accel_offset_x); Serial.print(" ");
  Serial.print(calibData.accel_offset_y); Serial.print(" ");
  Serial.print(calibData.accel_offset_z); Serial.print(" ");

  Serial.print("\nGyro: ");
  Serial.print(calibData.gyro_offset_x); Serial.print(" ");
  Serial.print(calibData.gyro_offset_y); Serial.print(" ");
  Serial.print(calibData.gyro_offset_z); Serial.print(" ");

  Serial.print("\nMag: ");
  Serial.print(calibData.mag_offset_x); Serial.print(" ");
  Serial.print(calibData.mag_offset_y); Serial.print(" ");
  Serial.print(calibData.mag_offset_z); Serial.print(" ");

  Serial.print("\nAccel Radius: ");
  Serial.print(calibData.accel_radius);

  Serial.print("\nMag Radius: ");
  Serial.print(calibData.mag_radius);
}


bool cNeigungssensor::loadCalibrationFromMemory()
{
  Serial.println("[BNO055] Initialisiere Kalibrierungsroutine...");
  delay(3000);

  long bnoID = 0;
  int eeAddr = 0; //(int)EE_ADDRESS_NEIGUNG;

  EEPROM.get(eeAddr, bnoID);

  adafruit_bno055_offsets_t calibrationData;
  sensor_t sensor;

  _bno.getSensor(&sensor);
  Serial.print("BNO ID aus Speicher: ");
  Serial.println(bnoID);
  Serial.print("BNO ID erfasst: ");
  Serial.println(sensor.sensor_id);

  if(bnoID != sensor.sensor_id)
  {
    Serial.println("[BNO055] Keine bisherige Kalibrierungskonfiguration im Speicher gefunden.");
    delay(2500);
  }
  else
  {
    Serial.println("[BNO055] Kalibrierungskonfiguration im Speicher gefunden.\nStelle Kalibierung wieder her...");
    delay(2500);

    eeAddr += sizeof(long);

    EEPROM.get(eeAddr, calibrationData);
    displaySensorOffsets(calibrationData);

    _bno.setSensorOffsets(calibrationData);

    _calibRestored = true;
  }

  displaySensorDetails();
  displaySensorStatus();
  delay(1000);

  _bno.setExtCrystalUse(true);

  sensors_event_t event;
  _bno.getEvent(&event);

  if(_calibRestored)
  {
    Serial.println("Sensor leicht bewegen, um Magnetometer zu kalibrieren.");
    while (!_bno.isFullyCalibrated())
    {
      _bno.getEvent(&event);
      delay(_refreshRate);
    }
  }
  else
  {
    Serial.println("Sensor muss vollstaendig kalibriert werden.");
    while (!_bno.isFullyCalibrated())
      {
          _bno.getEvent(&event);

          Serial.print("X: ");
          Serial.print(event.acceleration.x, 4);
          Serial.print("\tY: ");
          Serial.print(event.acceleration.y, 4);
          Serial.print("\tZ: ");
          Serial.print(event.acceleration.z, 4);

          /*imu::Vector<3> accel = _bno.getVector(Adafruit_BNO055::adafruit_vector_type_t::VECTOR_ACCELEROMETER);
          Serial.print("X: ");
          Serial.print(accel.x(), 4);
          Serial.print("\tY: ");
          Serial.print(accel.y(), 4);
          Serial.print("\tZ: ");
          Serial.print(accel.z(), 4);*/

          /* Optional: Display calibration status */
          displayCalStatus();

          /* New line for the next sample */
          Serial.println("");

          /* Wait the specified delay before requesting new data */
          delay(_refreshRate);
      }
  }

  Serial.println("BNO055 vollständig kalibriert");
  Serial.println("--------------------------------");
  Serial.println("Ergebnis: ");
  adafruit_bno055_offsets_t newCalib;
  _bno.getSensorOffsets(newCalib);
  displaySensorOffsets(newCalib);

  Serial.println("Neue Kalibrierung wird nun gespeichert...");

  eeAddr = 0; //(int)EE_ADDRESS_NEIGUNG;
  _bno.getSensor(&sensor);
  bnoID = sensor.sensor_id;

  EEPROM.put(eeAddr, bnoID);
  EEPROM.commit();

  eeAddr += sizeof(long);
  EEPROM.put(eeAddr, newCalib);
  EEPROM.commit();
  
  Serial.println("Neue Kalibierung erfolgreich abgespeichert!");
  displayCalStatus();
  delay(3000);

  return true;
}

void cNeigungssensor::displaySensorOrientation()
{
  sensors_event_t event;
  _bno.getEvent(&event);

  /* Display the floating point data */
  Serial.print("X: ");
  Serial.print(event.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event.orientation.y, 4);
  Serial.print("\tZ: ");
  Serial.println(event.orientation.z, 4);
}

sensors_event_t cNeigungssensor::getEvent()
{
  sensors_event_t event;
  _bno.getEvent(&event);

  return event;
}