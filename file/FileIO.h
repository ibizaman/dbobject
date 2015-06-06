#ifndef FILEIO_H
#define FILEIO_H

#include <map>
#include <string>
#include <sstream>
#include <memory>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

namespace File
{

typedef ::boost::filesystem::path path;
typedef std::map<std::string, std::string> Properties;

/*
 * Function accepting a string and optionaly an open mode (see openmode
 * below). The string is the path to the file. By default, the file is
 * erased. Specify File::append as second argument to append to
 * an existing file or to create an empty file if it doesn't exist.
 *
 * Returns an object having a operator<< function.
 *
 * Example:
 *   File::write out("/name/of/file")
 *   out << "text" << std::endl;
 */
using write = ::boost::filesystem::ofstream;
const auto append_mode = ::std::ios_base::app;

bool exists(const path&);
bool is_regular_file(const path&);
std::unique_ptr<std::ifstream> read(const path&);

std::string stripComments(const std::string&);
std::string stripWhitespace(const std::string&);

Properties parseToPropertiesMap(std::istream&);

/*
 * reads a line, independent of platform newline encoding
 * Credit to user763305
 * http://stackoverflow.com/a/6089413/1013628
 */
std::istream& safeGetline(std::istream&, std::string&);

}

#endif
