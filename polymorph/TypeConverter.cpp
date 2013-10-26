#include "TypeConverter.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>

namespace dbobject {
namespace TypeConverter {

template<>
std::string toString(const boost::posix_time::time_duration& duration, ConversionType)
{
    return boost::posix_time::to_simple_string(duration);
}

template<>
std::string toString(const boost::gregorian::date& date, ConversionType)
{
    return toString(date.year())+'-'+toString(date.month().as_number())+'-'+toString(date.day());
}

template<>
boost::gregorian::date fromString(const std::string& str, ConversionType)
{
    return boost::gregorian::from_string(str);
}

template<>
std::string toString(const boost::posix_time::ptime& time, ConversionType)
{
    return toString(time.date()) + 'T' + toString(time.time_of_day());
}

template<>
boost::posix_time::ptime fromString(const std::string& str, ConversionType)
{
    auto split_at = str.find('T');
    std::string date(str.begin(), str.begin()+split_at);
    std::string time(str.begin()+split_at+1, str.end());
    return boost::posix_time::ptime(fromString<boost::gregorian::date>(date), fromString<boost::posix_time::time_duration>(time));
}

}
}
