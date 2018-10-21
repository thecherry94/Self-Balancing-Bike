#include "cMeasurementLog.h"

#include <fstream>
#include <vector>
#include <string>


void make_example_sinus(cMeasurementLog<float, float>& pLog, float amplitude, float frequency, float total_time, float time_step);


int main()
{	



	// Wir geben jeder Messreihe einen Namen
	//
	std::vector<std::string> column_header;
	column_header.push_back("Zeit [sec]");
	column_header.push_back("Neigung [°]");


	// in den <> werden die Anzahl und der jeweilige Datentyp der Messreihen angegeben
	// Im Beispiel: 1. Zeit, 2. Wert
	cMeasurementLog<float, float> example_measurements(column_header);

	// F�lle Beispiel mit sinus
	make_example_sinus(example_measurements, 5.0f, 1.0f, 5.0f, 0.05f);

	// Gew�nschtes Format exportieren
	std::string mes = example_measurements.exprt("");

	// In Datei speichern
	// Auf esp per wifi herunterladbar zuk�nftig
	//
	std::ofstream out("example_measurement.txt");
	out << mes;
	out.close();




	// --> Beliebige Datentypen m�glich! <--

	/*
	cMeasurementLog<std::string, float> mes;
	mes.write("Hallo", 0);
	mes.write("das ist", 2.32f);
	mes.write("ein Test!", 21.532f);


	std::string res = mes.exprt("");
	*/


	return 0;
}



// F�lle Messblatt mit test sinus
//
void make_example_sinus(
	cMeasurementLog<float, float>& pLog, 
	float amplitude, float frequency, 
	float total_time, float time_step)
{
	int num_ticks = total_time / time_step;

	for (int tk = 0; tk < num_ticks; tk++)
	{
		float time = tk * time_step;
		pLog.write(time, amplitude * sin(2.0*PI*frequency * time));
	}
}