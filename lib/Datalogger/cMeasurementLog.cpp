#include "cMeasurementLog.h"


/*
template <class ... Ts>
void cMeasurementLog<Ts...>::write(std::tuple<Ts...> t)



template <class ... Ts>
void cMeasurementLog<Ts...>::write(Ts... t)
{
	_measurements.push_back(std::tuple<Ts...>(t...));
}


template <class ... Ts>
std::string cMeasurementLog<Ts...>::exprt(std::string type)
{
	if (type == "table" || type == "")
	{
		std::stringstream ss;

		std::vector<std::string>::iterator itCols;
		for (itCols = _columnNames.begin(); itCols != _columnNames.end(); itCols++)
		{
			ss << *itCols << "\t";
		}
		ss << "\n";

		std::vector<std::tuple<Ts...>>::iterator itData;
		for (itData = _measurements.begin(); itData != _measurements.end(); itData++)
		{
			for_each(*itData, [&, val] 
			{
				ss << val << "\t";
			});
			ss << "\n";
		}

		return ss.str();
	}

	return "";
}
*/