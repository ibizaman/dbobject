#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <istream>
#include <string>
#include <vector>

namespace File
{

class CSVParser
{
public:
    typedef std::vector<std::string> Line;
    typedef std::vector<Line> Lines;
    typedef Lines::iterator iterator;
    typedef Lines::const_iterator const_iterator;

    CSVParser(std::istream&);
    CSVParser(const std::string&);

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

private:
    void parse(std::istream&);

    Lines _file;
};

}

#endif
