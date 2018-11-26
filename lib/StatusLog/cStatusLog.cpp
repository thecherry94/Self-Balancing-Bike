#include "cStatusLog.h"



// Konstruktor
// Werte werden initialisiert
//
cStatusLogEntry::cStatusLogEntry(EStatusLogEntryType type, const std::string mod, const std::string msg)
{
	_type = type;
	_module = mod;
	_message = msg;
}


// Gibt eine Farbe zurück abhg. von dem Eintragstyp damit der Text in HTML formatiert wird
//
std::string cStatusLogEntry::get_color(EStatusLogEntryType t)
{
	switch (t)
	{
		case EStatusLogEntryType::NOTIFICATION:
			return "black";
		case EStatusLogEntryType::WARNING:
			return "yellow";
		case EStatusLogEntryType::SUCCESS:
			return "green";
		case EStatusLogEntryType::ERROR:
			return "red";
		case EStatusLogEntryType::FATAL_ERROR:
			return "purple";
	}

	return "black";
}


// Exportfunktion, die vorgibt, wie ein einzelner Eintrag beim Export formatiert wird
//
/*
HTML::Element cStatusLogEntry::exprt()
{
	//std::stringstream ss;
	//ss << "<p style=\"color: " << get_color(_type) << ";\">" << "[" << _module << "] " <<  _message << "</p><br />";

	std::string color = get_color(_type);
	
	CTML::Node node_base("p");
	CTML::Node node_basic("a");
	node_basic
		.SetContent(std::string("[") + _module + "] " + _message)
		.SetAttribute("style", "color:" + color + ";");

	node_base.AppendChild(node_basic);

	return node_base;

	

	HTML::Paragraph p("");
	p << HTML::Text(std::string("[") + _module + "] " + _message);
	p.addAttribute("style", "color:" + color + ";");

	return p;


}
*/

// Exportfunktion, die vorgibt, wie der gesamte Log beim Export formatiert wird
//
/*
HTML::Document cStatusLog::exprt()
{
	HTML::Document doc("ESP32 HTML Report");
	


	std::vector<cStatusLogEntry>::iterator it;
	for (it = _entries.begin(); it != _entries.end(); it++)
	{
		doc << it->exprt();
	}

	return doc;
}



// Beispiel, um zu zeigen, wie man ein eigenes Exportverhalten definieren kann
//
HTML::Element cMyStatusLogEntry::exprt()
{
	HTML::Element basic_node = cStatusLogEntry::exprt();

	basic_node << HTML::Break() << "My additional data: " + patch::to_string(_myData);

	return basic_node;
}

*/

