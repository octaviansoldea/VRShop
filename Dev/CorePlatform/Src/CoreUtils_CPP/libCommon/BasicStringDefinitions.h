#ifndef BASIC_STRING_DEFINITIONS_H
#define BASIC_STRING_DEFINITIONS_H

#include <string>
#include <sstream>
#include <vector>

std::string GetLastErrorString();
bool isInString(const std::string & astrName, const std::string & astrField);
bool isAtEndOfString(const std::string & astrName, const std::string & astrField);
//std::vector<std::string> splitString(std::string & astrName, const std::string & astrDelimiters);
std::vector<std::string> splitString(std::string & astrName, char * astrDelimiters);
void splitString(std::string const& s, char const* d, std::vector<std::string> & avecstrResult);
std::string replaceAll(std::string astrText, const std::string& astrFrom, const std::string& astrTo);

void trimString(std::string * apstrSource, char * apchDelim, std::string & astrTarget);

template <class T>
std::string tostr(T aVal)	{
	std::stringstream ss;//create a stringstream
	ss << aVal;//add number to the stream
	return ss.str();//return a string with the contents of the stream
};

std::wstring string2WString(const std::string& astrString);
wchar_t * string2WChar(const std::string & astrString);


#endif //BASIC_STRING_DEFINITIONS_H