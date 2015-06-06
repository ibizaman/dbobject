#include "FileIO.h"

#include <boost/tokenizer.hpp>
#include <stdexcept>
#include <iostream>

namespace File
{

bool exists(const path& path)
{
    return ::boost::filesystem::exists(path);
}

bool is_regular_file(const path& path)
{
    return ::boost::filesystem::is_regular_file(path);
}

std::unique_ptr<std::ifstream> read(const path& path)
{
    if (!File::exists(path) || !File::is_regular_file(path)) {
        throw std::invalid_argument("File "+path.native()+" not found");
    }

    return std::unique_ptr<std::ifstream>(new ::boost::filesystem::ifstream(path));
}

std::string stripComments(const std::string& str)
{
    return str.substr(0, str.find_first_of('#'));
}

std::string stripWhitespace(const std::string& str)
{
    auto first = str.find_first_not_of(' ');
    auto last = str.find_last_not_of(' ')-first+1;
    if (first >= last) {
        return "";
    } else {
        return str.substr(first, last);
    }
}

Properties parseToPropertiesMap(std::istream& file)
{
    Properties properties;

    std::string line;
    while (safeGetline(file, line)) {
        line = stripComments(line);

        boost::char_separator<char> sep("=");
        boost::tokenizer<boost::char_separator<char>> tok(line, sep);

        auto word = tok.begin();
        if (word == tok.end()) {
            continue;
        }

        std::string key = stripWhitespace(*word);
        if (key == "") {
            continue;
        }

        if (++word == tok.end())
        {
            continue;
        }
        std::string value = stripWhitespace(*word);

        properties[key] = value;
    }

    return properties;
}

std::istream& safeGetline(std::istream& is, std::string& t)
{
    t.clear();

    // The characters in the stream are read one-by-one using a std::streambuf.
    // That is faster than reading them one-by-one using the std::istream.
    // Code that uses streambuf this way must be guarded by a sentry object.
    // The sentry object performs various tasks,
    // such as thread synchronization and updating the stream state.

    std::istream::sentry se(is, true);
    std::streambuf* sb = is.rdbuf();

    for(;;) {
        int c = sb->sbumpc();
        switch (c) {
        case '\n':
            return is;
        case '\r':
            if(sb->sgetc() == '\n')
                sb->sbumpc();
            return is;
        case EOF:
            // Also handle the case when the last line has no line ending
            if(t.empty())
                is.setstate(std::ios::eofbit);
            return is;
        default:
            t += (char)c;
        }
    }
}

}
