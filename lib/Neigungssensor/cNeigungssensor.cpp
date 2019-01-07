#include "cNeigungssensor.h"
#include "EEPROM.h"
#include <sstream>
#include <Wire.h>

#include "cStatusLog.h"
#include "cWebServer.h"

#define MODULE_NEIGUNG "NEIGUNGSSENSOR"

//const char* site PROGMEM = "<html> <head> <title>ESP32 WiFi Test - BNO055 Datenauswertung</title> </head> <body> <script src=\"https://code.jquery.com/jquery-3.3.1.min.js\"></script> <script>$(function() { getData(); setInterval(getData, 90); });function getData() { $.get(\"/sensor_data\", function(data) { var parsed = $.parseJSON(data);$(\"#SENSOR_ORI_X\").text(parsed[\"x\"]); $(\"#SENSOR_ORI_Y\").text(parsed[\"y\"]); $(\"#SENSOR_ORI_Z\").text(parsed[\"z\"]); }) }</script> <h1>ESP32 WiFi Kommunikation Test</h1> <h2>BNO055 Sensordatenanzeige</h2> <p>&nbsp;</p> <h4>Neigung</h4> <table style=\"height: 125px; width: 154px; border-color: black;\" border=\"1\"> <tbody> <tr> <td style=\"width: 25px;\">&nbsp;x</td> <td id=\"SENSOR_ORI_X\" style=\"width: 105px;\">&nbsp;</td> </tr> <tr> <td style=\"width: 25px;\">&nbsp;y</td> <td id=\"SENSOR_ORI_Y\" style=\"width: 105px;\">&nbsp;</td> </tr> <tr> <td style=\"width: 25px;\">&nbsp;z</td> <td id=\"SENSOR_ORI_Z\" style=\"width: 105px;\">&nbsp;</td> </tr> </tbody> </table> </body> </html>";

// Konstruktor
// Hier 
cNeigungssensor::cNeigungssensor(int bno_addr) 
	: _bno(Adafruit_BNO055(55)), _calibRestored(false), _refreshRate(100)
{
	//Wire.begin();
	Serial.begin(115200);
	//_bno = Adafruit_BNO055(bno_addr);
	
	// Überprüfen, ob der BNO überhaupt erreichbar ist
	while (_bno.begin())
	{
		Serial.println("BNO055 nicht erkannt. Verkabelung oder I2C Adresse falsch!?");    
		//LOG->write(cStatusLogEntry(EStatusLogEntryType::FATAL_ERROR, MODULE_NEIGUNG, "BNO055 nicht erkannt. Verkabelung oder I2C Adresse falsch!?"));

		delay(1000);
	}

	// Versuche, falls vorhanden, Kalibierungsdaten vom EEPROM zu laden
	//loadCalibrationFromMemory();

	_neigungsBufferIndex = 0;
	_neigungsGeschwindigkeit = 0;
}


// Gibt einfach sämtliche Sensoreigenschaften aus
//
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


// Hole die Stati der Sensorelemente und gib sie aus
//
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
}


// Gibt den grad der Kalibierung an
//
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


// Gibt die Sensor-Offsets aus
//
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


// Diese Funktion versucht, falls vorhanden, Kalibierungsdaten aus dem EEPROM zu laden.
// Falls diese nicht vorhanden sind, wird die Funktion eine Routine starten und der Sensor
// muss einmal manuell kalibiert werden
//
bool cNeigungssensor::loadCalibrationFromMemory()
{
	/*LOG->write(cStatusLogEntry(
		EStatusLogEntryType::NOTIFICATION, MODULE_NEIGUNG,
		"[BNO055] Initialisiere Kalibrierungsroutine..."));
*/
	long bnoID = 0;   // Mit dieser Variable wird überprüft, ob eine Kalibrierungskonfiguration existiert?
	int eeAddr = 0;   // Adresse im EEPROM

	EEPROM.get(eeAddr, bnoID);

	// Überprüfe EEPROM auf ggf. vorhande Kalibierungskonfiguration
	//
	adafruit_bno055_offsets_t calibrationData;
	sensor_t sensor;
	_bno.getSensor(&sensor);

	// Konstruiere String für Log-Eintrag
	//
	std::stringstream ss;
	ss << "BNO ID aus Speicher: \t" << bnoID << "\n" << "BNO ID erfasst: \t" << sensor.sensor_id;

	// Logeintrag
	/*LOG->write(cStatusLogEntry(
		EStatusLogEntryType::NOTIFICATION, MODULE_NEIGUNG,
		ss.str()));
*/
	// BNO055 Kalibierungskonfig nicht gefunden
	//
	if(bnoID != sensor.sensor_id)
	{
		Serial.println("[BNO055] Keine bisherige Kalibrierungskonfiguration im Speicher gefunden.");
		/*LOG->write(cStatusLogEntry(
		EStatusLogEntryType::WARNING, MODULE_NEIGUNG,
		"Keine bisherige Kalibrierungskonfiguration im Speicher gefunden."));*/
	}
	else
	{
		Serial.println("Kalibrierung gefunden");
		/*LOG->write(cStatusLogEntry(
		EStatusLogEntryType::NOTIFICATION, MODULE_NEIGUNG,
		"Kalibrierungskonfiguration im Speicher gefunden. Kalibrierung wird hergestellt."));*/

		// Stelle Kalibierung aus Speicher wieder her
		//
		eeAddr += sizeof(long);

		EEPROM.get(eeAddr, calibrationData);
		displaySensorOffsets(calibrationData);

		_bno.setSensorOffsets(calibrationData);

		_calibRestored = true;
	}

	displaySensorDetails();
	displaySensorStatus();

	_bno.setExtCrystalUse(true);

	sensors_event_t event;
	_bno.getEvent(&event);

	// Das Magnetometer muss dennoch bei jedem Neustart (kurz!) neu kalibiert werden.
	// Meist reicht ein kleines bisschen Wackeln
	//
	if(_calibRestored)
	{
		/*LOG->write(cStatusLogEntry(
		EStatusLogEntryType::NOTIFICATION, MODULE_NEIGUNG,
		"BNO055 Kalibrierungskonfiguration gefunden - Magnetometer wird justiert."));*/

		Serial.println("Sensor leicht bewegen, um Magnetometer zu kalibrieren.");
		/*while (!_bno.isFullyCalibrated())
		{
			_bno.getEvent(&event);
			displayCalStatus();
			Serial.println("");
			delay(_refreshRate);
		}*/
	}
	else
	{
		/*LOG->write(cStatusLogEntry(
		EStatusLogEntryType::NOTIFICATION, MODULE_NEIGUNG,
		"BNO055 Kalibrierungskonfiguration NICHT gefunden - Sensor wird vollständig kalibiert."));
		Serial.println("Sensor muss vollstaendig kalibriert werden.");*/

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

	/*LOG->write(cStatusLogEntry(
		EStatusLogEntryType::NOTIFICATION, MODULE_NEIGUNG,
		"BNO055 ist nun vollständig kalibiert und einsatzbereit."));*/

	Serial.println("BNO055 vollständig kalibriert");
	Serial.println("--------------------------------");
	Serial.println("Ergebnis: ");
	adafruit_bno055_offsets_t newCalib;
	_bno.getSensorOffsets(newCalib);
	displaySensorOffsets(newCalib);

	if(!_calibRestored)
	{
		Serial.println("Neue Kalibrierung wird nun gespeichert...");
		/*LOG->write(cStatusLogEntry(
			EStatusLogEntryType::NOTIFICATION, MODULE_NEIGUNG,
			"Kalibierung wird nun in EEPROM gespeichert."));*/

		eeAddr = 0; //(int)EE_ADDRESS_NEIGUNG;
		_bno.getSensor(&sensor);
		bnoID = sensor.sensor_id;

		EEPROM.put(eeAddr, bnoID);
		EEPROM.commit();

		eeAddr += sizeof(long);
		EEPROM.put(eeAddr, newCalib);
		EEPROM.commit();
		
		Serial.println("Neue Kalibierung erfolgreich abgespeichert!");
	}
	//displayCalStatus();
	//delay(3000);

	/*LOG->write(cStatusLogEntry(
		EStatusLogEntryType::NOTIFICATION, MODULE_NEIGUNG,
		"Kalibierungskonfiguration wurde erfolgreich in EEPROM gespeichert"));*/

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

bool cNeigungssensor::IsFullyCalibrated()
{
	return true; // _bno.isFullyCalibrated();
}


imu::Vector<3> cNeigungssensor::getRawData(Adafruit_BNO055::adafruit_vector_type_t type)
{
//	_neigungsBuffer[_neigungsBufferIndex++] = _bno.getVector(type);
	_neigungsBuffer[_neigungsBufferIndex++] = 5; // Julian

	if (_neigungsBufferIndex >= 9)
	{
		_neigungsBufferIndex = 0;
		for (int i = 0; i < 10; i++)
			_neigungsGeschwindigkeit += _neigungsBuffer[i];
		
		_neigungsGeschwindigkeit /= 10.0f;
	}

	return _bno.getVector(type);
}

float cNeigungssensor::GetNeigungswinkelgeschwindigkeitZ()
{
	return _neigungsGeschwindigkeit;
}