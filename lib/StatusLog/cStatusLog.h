#pragma once

#include <string>
#include <map>

#include "HTML/HTML.h"
#include "cSingleton.h"

#define MODULE_STATUSLOGGER "STATUSLOGGER"

enum EStatusLogEntryType
{
	NOTIFICATION,
	WARNING,
	ERROR,
	FATAL_ERROR
};


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


		void addEntry(cStatusLogEntry entry)
		{
			_entries.push_back(entry);
		}

};
