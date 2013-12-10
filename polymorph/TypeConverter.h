#ifndef DBOBJECT_TYPECONVERTER_H
#define DBOBJECT_TYPECONVERTER_H

#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace dbobject {

namespace TypeConverter {
    enum ConversionType { BOOLALPHA, BOOLNUM };

    template<typename T> T fromString(const std::string&, ConversionType = BOOLALPHA);
    template<typename T> std::string toString(const T&, ConversionType = BOOLALPHA);

    template<> std::string toString(const boost::posix_time::time_duration&, ConversionType);
    template<> boost::posix_time::time_duration fromString(const std::string&, ConversionType);

    template<> std::string toString(const boost::gregorian::date&, ConversionType);
    template<> boost::gregorian::date fromString(const std::string&, ConversionType);

    template<> std::string toString(const boost::posix_time::ptime&, ConversionType);
    template<> boost::posix_time::ptime fromString(const std::string&, ConversionType);

    template<> std::string toString(const boost::gregorian::greg_weekday&, ConversionType);
    template<> boost::gregorian::greg_weekday fromString(const std::string&, ConversionType);
}

}

#include "TypeConverter.hpp"

#endif
