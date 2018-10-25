#pragma once

#include <string>
#include <map>

#include "HTML/HTML.h"
#include "cSingleton.h"

// Define um schneller auf die Statuslog-Instanz zuzugrefen
#define LOG cStatusLog::instance()

// Modulname für Statuslogger-Meldungen
#define MODULE_STATUSLOG "STATUSLOGGER"

// Enum um Statusmeldungstypen zu bestimmen
//
enum EStatusLogEntryType
{
	NOTIFICATION,
	SUCCESS,
	WARNING,
	ERROR,
	FATAL_ERROR
};


// Basisklasse für Statuseinträge
// Kann direkt benutzt oder vererbt werden
// exprt Funktion muss überschrieben werden
//
class cStatusLogEntry
{
	protected:
		EStatusLogEntryType _type;
		std::string _module;
		std::string _message;

		

		std::string get_color(EStatusLogEntryType t);

	public:

		cStatusLogEntry(EStatusLogEntryType type, const std::string mod, const std::string msg);


		virtual HTML::Element exprt();

};


// Beispiel für eine eigene Statuslog-Klasse
//
class cMyStatusLogEntry : public cStatusLogEntry
{
	private:
		float _myData;

	public:

		cMyStatusLogEntry(EStatusLogEntryType type, std::string mod, std::string msg, float mydata) 
			: cStatusLogEntry(type, mod, msg)
		{
			_myData = mydata;
		}

		HTML::Element exprt();
};



// Die Statuslog-Klasse
// Wird als Singleton implementiert
//
class cStatusLog : public cSingleton<cStatusLog>
{
	friend class cSingleton<cStatusLog>;

	private:
		std::vector<cStatusLogEntry> _entries;
		
		std::string _title;
		std::string _subtitle;


	protected:
		cStatusLog() {};

	public:


		HTML::Document exprt();


		void write(cStatusLogEntry entry)
		{
			_entries.push_back(entry);
		}

};
