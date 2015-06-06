#ifndef DATETIME_H
#define DATETIME_H

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "TypeConverter.h"

namespace datetime
{
    typedef boost::posix_time::time_duration Time;
    typedef boost::gregorian::date Date;
    typedef boost::gregorian::date_duration Day;
    typedef boost::posix_time::ptime Datetime;
    typedef int Second;

    enum Weekday {
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    };

    const Day day(1);

    Weekday day_of_week(Date);
    Weekday day_of_week(Datetime);
    Weekday next_day(Weekday);
    Time time_of_day(Datetime);
    Date date_of_datetime(Datetime);
    Day operator"" _days(unsigned long long);
    Time absolute_time_difference(Datetime, Datetime);
    Time absolute_time_difference(Time, Time);
    Second to_seconds(Time);
    Time seconds_to_time(Second);
    Time time_now();
    Datetime date_now();
}

namespace TypeConverter {
namespace impl {
    template<> struct TypeConverter<datetime::Time> {
        static std::string toString(const datetime::Time&, const Settings&);
        static datetime::Time fromString(const std::string&, const Settings&);
    };

    template<> struct TypeConverter<datetime::Date> {
        static std::string toString(const datetime::Date&, const Settings&);
        static datetime::Date fromString(const std::string&, const Settings&);
    };

    template<> struct TypeConverter<datetime::Datetime> {
        static std::string toString(const datetime::Datetime&, const Settings&);
        static datetime::Datetime fromString(const std::string&, const Settings&);
    };

    template<> struct TypeConverter<datetime::Weekday> {
        static std::string toString(const datetime::Weekday&, const Settings&);
        static datetime::Weekday fromString(const std::string&, const Settings&);
    };
}
}

#endif
