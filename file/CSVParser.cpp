#include "CSVParser.h"
#include "FileIO.h"

#include <sstream>
#include <boost/filesystem/fstream.hpp>
#include <boost/tokenizer.hpp>

namespace File
{

CSVParser::CSVParser(std::istream& stream)
{
    parse(stream);
}

CSVParser::CSVParser(const std::string& content)
{
    std::stringstream stream(content);
    parse(stream);
}

void CSVParser::parse(std::istream& content)
{
    std::string line;
    while (safeGetline(content, line)) {
        line = stripWhitespace(stripComments(line));
        if (line == "") {
            continue;
        }

        boost::tokenizer<boost::escaped_list_separator<char>> tok(line);

        Line csvLine;
        for (auto word : tok) {
            csvLine.push_back(stripWhitespace(word));
        }

        if (csvLine.size() == 0) {
            continue;
        }
        _file.push_back(csvLine);
    }
}

CSVParser::iterator CSVParser::begin()
{
    return _file.begin();
}

CSVParser::const_iterator CSVParser::begin() const
{
    return _file.begin();
}

CSVParser::iterator CSVParser::end()
{
    return _file.end();
}

CSVParser::const_iterator CSVParser::end() const
{
    return _file.end();
}

}
