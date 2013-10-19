#include "TypeConverter.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace dbobject {
namespace TypeConverter {

template<>
std::string toString(const boost::posix_time::time_duration& duration, ConversionType)
{
    return boost::posix_time::to_iso_string(duration);
}

template<>
std::string toString(const boost::posix_time::ptime& time, ConversionType)
{
    return boost::posix_time::to_iso_string(time);
}

template<>
std::string toString(const boost::gregorian::date& date, ConversionType)
{
    return boost::gregorian::to_iso_string(date);
}

}
}
