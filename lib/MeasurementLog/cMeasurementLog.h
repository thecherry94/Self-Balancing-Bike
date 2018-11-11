

#include <string>
#include <vector>
#include <sstream>

#ifndef MEASUREMENTLOG__H
#define MEASUREMENTLOG__H

template<typename CharT>
class DecimalSeparator : public std::numpunct<CharT>
{
public:
    DecimalSeparator(CharT Separator)
    : m_Separator(Separator)
    {}

protected:
    CharT do_decimal_point()const
    {
        return m_Separator;
    }

private:
    CharT m_Separator;
};




enum EMeasurementLogFormatting
{
    FORMAT_EXCEL
};


// Neue Messdatenlog-Klasse
// Die alte war für unseren Compiler nicht kompatibel (wegen C++14 features)
// Sie ist wesentlich unflexibler und noch nicht fertig
//
template<class T>
class cMeasurementLog
{
    private:
        std::vector<std::string> _column_headers;    
        std::vector<T> _data;

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
        cMeasurementLog(std::string first, TRest... rest)
        {
            setup_columns(first, rest...);
        }

        template <class... TRest>
        void write(T first, TRest... rest)
        {
            _data.push_back(first);
            write(rest...);
        }

        void write(T data)
        {
            _data.push_back(data);
        }

        void reset()
        {
            _data.clear();
        }

        std::string exprt(EMeasurementLogFormatting f)
        {
            std::stringstream ss;
            ss.imbue(std::locale(ss.getloc(), new DecimalSeparator<char>(',')));
            
            int j = 0;

            switch(f)
            {
                case EMeasurementLogFormatting::FORMAT_EXCEL:
                    
                    for (int i = 0; i < _column_headers.size(); i++)
                        ss << _column_headers[i] << ";";
                    
                    ss << "\n";

                    for (int i = 0; i < _data.size();  i++)
                    {   
                        ss << _data[i];
                        j++;
                        
                        if (j >= _column_headers.size())
                        {
                            ss << "\n";
                            j = 0;
                        }
                        else
                            ss << ";";

                        
                    }
                
                break;
            }

            return ss.str();
        }
};

#endif