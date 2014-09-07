#ifndef BASIC_STRING_DEFINITIONS_H
#define BASIC_STRING_DEFINITIONS_H

#include <string>
#include <sstream>
#include <vector>

std::string GetLastErrorString();
bool isInString(const std::string & astrName, const std::string & astrField);
bool isAtEndOfString(const std::string & astrName, const std::string & astrField);
std::vector<std::string> splitString(std::string & astrName, const std::string & astrDelimiters);

template <class T>
std::string tostr(T aVal)	{
	std::stringstream ss;//create a stringstream
	ss << aVal;//add number to the stream
	return ss.str();//return a string with the contents of the stream
};

#endif //BASIC_STRING_DEFINITIONS_H