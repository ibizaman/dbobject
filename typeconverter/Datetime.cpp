#include "Datetime.h"
#include <algorithm>

datetime::Weekday datetime::day_of_week(datetime::Date date)
{
    Weekday day;

    switch (date.day_of_week())
    {
        case boost::gregorian::Monday:
            day = datetime::Monday;
            break;
        case boost::gregorian::Tuesday:
            day = datetime::Tuesday;
            break;
        case boost::gregorian::Wednesday:
            day = datetime::Wednesday;
            break;
        case boost::gregorian::Thursday:
            day = datetime::Thursday;
            break;
        case boost::gregorian::Friday:
            day = datetime::Friday;
            break;
        case boost::gregorian::Saturday:
            day = datetime::Saturday;
            break;
        case boost::gregorian::Sunday:
            day = datetime::Sunday;
            break;
    }

    return day;
}

datetime::Weekday datetime::day_of_week(datetime::Datetime datetime)
{
    return day_of_week(datetime.date());
}

datetime::Weekday datetime::next_day(Weekday day)
{
    Weekday nextDay = datetime::Monday;

    switch (day)
    {
        case datetime::Monday:
            nextDay = datetime::Tuesday;
            break;
        case datetime::Tuesday:
            nextDay = datetime::Wednesday;
            break;
        case datetime::Wednesday:
            nextDay = datetime::Thursday;
            break;
        case datetime::Thursday:
            nextDay = datetime::Friday;
            break;
        case datetime::Friday:
            nextDay = datetime::Saturday;
            break;
        case datetime::Saturday:
            nextDay = datetime::Sunday;
            break;
        case datetime::Sunday:
            nextDay = datetime::Monday;
            break;
    }

    return nextDay;
}

datetime::Time datetime::time_of_day(datetime::Datetime datetime)
{
    return datetime.time_of_day();
}

datetime::Date datetime::date_of_datetime(datetime::Datetime datetime)
{
    return datetime.date();
}

datetime::Day datetime::operator"" _days(unsigned long long days)
{
    return Day(static_cast<long long>(days));
}

datetime::Time datetime::absolute_time_difference(datetime::Datetime from, datetime::Datetime to)
{
    auto duration = from - to;
    if (duration.is_negative()) {
        duration = duration.invert_sign();
    }
    return duration;
}

datetime::Time datetime::absolute_time_difference(datetime::Time from, datetime::Time to)
{
    auto duration = from - to;
    if (duration.is_negative()) {
        duration = duration.invert_sign();
    }
    return duration;
}

datetime::Second datetime::to_seconds(datetime::Time time)
{
    return time.total_seconds();
}

datetime::Time datetime::seconds_to_time(datetime::Second seconds)
{
    return datetime::Time(0,0,seconds,0);
}

datetime::Time datetime::time_now()
{
    return date_now().time_of_day();
}

datetime::Datetime datetime::date_now()
{
    return boost::posix_time::second_clock::universal_time();
}

std::string TypeConverter::impl::TypeConverter<datetime::Time>::toString(const datetime::Time& duration, const Settings&)
{
    return boost::posix_time::to_simple_string(duration);
}

datetime::Time TypeConverter::impl::TypeConverter<datetime::Time>::fromString(const std::string& str, const Settings&)
{
    try {
        return boost::posix_time::duration_from_string(str);
    } catch(std::out_of_range&) {
        throw ImpossibleConversion("Format for Time is HH:MM:SS", str, "the values are out of range");
    } catch(boost::bad_lexical_cast&) {
        throw ImpossibleConversion("Format for Time is HH:MM:SS", str, "the format is unknown");
    }
}

std::string TypeConverter::impl::TypeConverter<datetime::Date>::toString(const datetime::Date& date, const Settings& settings)
{
    return ::TypeConverter::toString(date.year(), settings)
     +'/'+ ::TypeConverter::toString(date.month().as_number(), settings)
     +'/'+ ::TypeConverter::toString(date.day(), settings);
}

datetime::Date TypeConverter::impl::TypeConverter<datetime::Date>::fromString(const std::string& str, const Settings&)
{
    try {
        return boost::gregorian::from_string(str);
    } catch(std::out_of_range&) {
        throw ImpossibleConversion("Format for Date is YYYY/MM/DD", str, "the values are out of range");
    } catch(boost::bad_lexical_cast&) {
        throw ImpossibleConversion("Format for Date is YYYY/MM/DD", str, "the format is unknown");
    }
}

std::string TypeConverter::impl::TypeConverter<datetime::Datetime>::toString(const datetime::Datetime& time, const Settings& settings)
{
    return ::TypeConverter::toString(time.date(), settings)
     +'T'+ ::TypeConverter::toString(time.time_of_day(), settings);
}

datetime::Datetime TypeConverter::impl::TypeConverter<datetime::Datetime>::fromString(const std::string& str, const Settings&)
{
    auto split_at = str.find_first_of("T ");
    if (split_at == std::string::npos) {
        if (std::all_of(str.begin(), str.end(), ::isdigit)) {
            try {
                return boost::posix_time::from_time_t(
                        ::TypeConverter::fromString<int>(str)
                        );
            } catch(std::out_of_range& e) {
                throw ImpossibleConversion("Datetime", str, e.what());
            }
        } else {
            throw ImpossibleConversion("Datetime", str, "Did not find date and time separator, searched for 'T' or space ' '");
        }
    } else {
        std::string date_str(str, 0, split_at);
        std::string time_str(str, split_at+1);

        boost::gregorian::date date;
        try {
            date = ::TypeConverter::fromString<boost::gregorian::date>(date_str);
        } catch(ImpossibleConversion& e) {
            throw ImpossibleConversion("Datetime", str, "Format for Datetime is YYYY/MM/DDTHH:MM:SS, the given time format is incorrect");
        }

        boost::posix_time::time_duration time;
        try {
            time = ::TypeConverter::fromString<boost::posix_time::time_duration>(time_str);
        } catch(ImpossibleConversion& e) {
            throw ImpossibleConversion("Datetime", str, "Format for Datetime is YYYY/MM/DDTHH:MM:SS, the given date format is incorrect");
        }

        try {
            return boost::posix_time::ptime(date, time);
        } catch(std::out_of_range& e) {
            throw ImpossibleConversion("Datetime", str, e.what());
        }
    }
}

std::string TypeConverter::impl::TypeConverter<datetime::Weekday>::toString(const datetime::Weekday& time, const Settings&)
{
    std::string literal;

    switch(time) {
        case datetime::Monday:
            literal = "Monday";
            break;
        case datetime::Tuesday:
            literal = "Tuesday";
            break;
        case datetime::Wednesday:
            literal = "Wednesday";
            break;
        case datetime::Thursday:
            literal = "Thursday";
            break;
        case datetime::Friday:
            literal = "Friday";
            break;
        case datetime::Saturday:
            literal = "Saturday";
            break;
        case datetime::Sunday:
            literal = "Sunday";
            break;
    }

    return literal;
}

datetime::Weekday TypeConverter::impl::TypeConverter<datetime::Weekday>::fromString(const std::string& str, const Settings&)
{
    if (str == "Monday") {
        return datetime::Monday;
    } else if (str == "Tuesday") {
        return datetime::Tuesday;
    } else if (str == "Wednesday") {
        return datetime::Wednesday;
    } else if (str == "Thursday") {
        return datetime::Thursday;
    } else if (str == "Friday") {
        return datetime::Friday;
    } else if (str == "Saturday") {
        return datetime::Saturday;
    } else if (str == "Sunday") {
        return datetime::Sunday;
    } else {
        throw ImpossibleConversion("::datetime::Weekday", str, "not a weekday");
    }
}
