#ifndef LIVELOG__H
#define LIVELOG__H

#include <vector>
#include <string>

template<class T>
using SufficientValuesReachedCallback_t = std::function<void(std::vector<T> values, std::vector<std::string> headers, int num_data_in_row, int rows)>;

// Klasse, um Messdaten live zu erfassen
// Falls eine festgelegte Menge an Messreihen erreich wird, wird ein Callback ausgelöst,
// an dem die Daten zur weiteren Verarbeitung überreicht werden
template<class T>
class cLivelog
{
    private:
        int _num_rows;
        int _current_row;
        int _data_per_row;
        std::vector<std::string> _column_headers;
        std::vector<T> _data;

        SufficientValuesReachedCallback_t<T> _sufficient_values_reached;

        void setup_columns(std::string str)
        {
            _column_headers.push_back(str);
        }

        template <class... TRest>
        void setup_columns(std::string first, TRest... rest)
        {
            _column_headers.push_back(first);
            setup_columns(rest...);
        }

    public:
        template <class... TRest>
        cLivelog(int num_rows, std::string first, TRest... rest)
        {
            setup_columns(first, rest...);
            _num_rows = num_rows;
            _current_row = 0;
            _data.resize(_num_rows * _column_headers.size());
            _data_per_row = _column_headers.size();
        }

        void SetSufficientValuesReachedCallback(SufficientValuesReachedCallback_t<T> cb)
        {
            _sufficient_values_reached = cb;
        }

        void write(std::vector<T> data_row)
        {   
            // Mehr Daten pro Reihe als festgelegt? Bullshit wird nicht geduldet
            if (data_row.size() > _data_per_row)
            {
                Serial.println("LUL");
                return;
            }
            
            // Daten in momentane Zeile schreiben
            for(int i = 0; i < _data_per_row; i++)
            {
                _data.at(i + _current_row * _data_per_row) = data_row[i];
            }

            

            // Momentane Zeile hochzählen
            _current_row++;

            // Maximale Zeilenanzahl erreicht?
            if(_current_row >= _num_rows)
            {
                // Callback-Funktion hinterlegt?
                if(_sufficient_values_reached)
                {
                    // Callback ausführen und Daten übermitteln
                    _sufficient_values_reached(_data, _column_headers, _data_per_row, _num_rows);
                }

                // Wieder von vorne beginnen
                _current_row = 0;
            }
        }

        // JSON Objekt zusammenbauen und als string zurückgeben
        //
        static std::string make_json(char* type, std::vector<T> values, std::vector<std::string> headers, int num_data_in_row, int rows)
        {
            const int BUFFER_SIZE = (int)(values.size() * sizeof(T) * 2.0f);

            // Buffer erstellen
            DynamicJsonBuffer jsnbuf(BUFFER_SIZE);

            // Stammobjekt erstellen
            JsonObject& root = jsnbuf.createObject();

            // Typ spezifizieren
            root["type"] = type;

            // Data Objekt unter Stammobjekt 
            JsonObject& data = root.createNestedObject("data");
            data["ValuesPerRow"] = num_data_in_row;
            data["TotalRows"] = rows;

            // Titel der Spalten der Messreihen als Array in Data objekt erstellen
            JsonArray& titles = data.createNestedArray("titles");
            for(int i = 0; i < headers.size(); i++)
                titles.add(headers[i].c_str());

            // Messdatenobjekt in Data Objekt als Array und Messdaten einfügen
            JsonArray& measurements = data.createNestedArray("measurements");
            for(int i = 0; i < values.size(); i++)
                measurements.add(values[i]);

            String str_buf;
            root.printTo(str_buf);

            Serial.println("DONE");

            return std::string(str_buf.c_str());
        }
        

};


#endif