#include "cStatusLog.h"




cStatusLogEntry::cStatusLogEntry(EStatusLogEntryType type, const std::string mod, const std::string msg)
{
	_type = type;
	_module = mod;
	_message = msg;
}


std::string cStatusLogEntry::get_color(EStatusLogEntryType t)
{
	switch (t)
	{
	case EStatusLogEntryType::NOTIFICATION:
		return "black";
	case EStatusLogEntryType::WARNING:
		return "yellow";
	case EStatusLogEntryType::ERROR:
		return "red";
	case EStatusLogEntryType::FATAL_ERROR:
		return "purple";
	}

	return "black";
}


HTML::Element cStatusLogEntry::exprt()
{
	//std::stringstream ss;
	//ss << "<p style=\"color: " << get_color(_type) << ";\">" << "[" << _module << "] " <<  _message << "</p><br />";

	std::string color = get_color(_type);
	/*
	
	CTML::Node node_base("p");
	CTML::Node node_basic("a");
	node_basic
		.SetContent(std::string("[") + _module + "] " + _message)
		.SetAttribute("style", "color:" + color + ";");

	node_base.AppendChild(node_basic);

	return node_base;

	*/

	HTML::Paragraph p("");
	p << HTML::Text(std::string("[") + _module + "] " + _message);
	p.addAttribute("style", "color:" + color + ";");

	return p;


}



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




HTML::Element cMyStatusLogEntry::exprt()
{
	HTML::Element basic_node = cStatusLogEntry::exprt();

	basic_node << HTML::Break() << "My additional data: " + patch::to_string(_myData);

	return basic_node;
}

