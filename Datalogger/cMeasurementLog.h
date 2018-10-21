#include <string>
#include <vector>
#include <sstream>
#include <tuple>

#include <random>



template <class ... Ts>
class cMeasurementLog
{
	private:
		std::vector<std::string> _columnNames;
		std::vector<std::tuple<Ts...>> _measurements;


	public:

		cMeasurementLog(std::vector<std::string> columnNames)
		{
			_columnNames = columnNames;
		}

		void write(std::tuple<Ts...> t)
		{
			_measurements.push_back(t);
		}

		void write(Ts... t)
		{
			_measurements.push_back(std::tuple<Ts...>(t...));
		}

		std::string exprt(std::string type)
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

				typename std::vector<std::tuple<Ts...>>::iterator itData;
				for (itData = _measurements.begin(); itData != _measurements.end(); itData++)
				{
					for_each_in_tuple(*itData, [&](const auto& x)
					{
						ss << x << "\t";
					});
					ss << "\n";
				}

				return ss.str();
			}

			return "";
		}

		void clear()
		{
			_measurements.clear();
		}

};



// Copypasta
// Man kann ein std::tuple nicht mit runtime-Werten indizieren, sonder nur mit compiletile-Werten
// => Workaround
// https://stackoverflow.com/questions/26902633/how-to-iterate-over-a-stdtuple-in-c-11

template<class F, class...Ts, std::size_t...Is>
void for_each_in_tuple(const std::tuple<Ts...> & tuple, F func, std::index_sequence<Is...>){
    using expander = int[];
    (void)expander { 0, ((void)func(std::get<Is>(tuple)), 0)... };
}

template<class F, class...Ts>
void for_each_in_tuple(const std::tuple<Ts...> & tuple, F func){
    for_each_in_tuple(tuple, func, std::make_index_sequence<sizeof...(Ts)>());
}

