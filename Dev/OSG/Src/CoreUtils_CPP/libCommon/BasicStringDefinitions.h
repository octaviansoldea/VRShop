#ifndef BASIC_STRING_DEFINITIONS_H
#define BASIC_STRING_DEFINITIONS_H

#include <string>
#include <vector>

std::string itostr(int anVal);
std::string GetLastErrorString();
bool isInString(const std::string & astrName, const std::string & astrField);
bool isAtEndOfString(const std::string & astrName, const std::string & astrField);
std::vector<std::string> splitString(std::string & astrName, const std::string & astrDelimiters);

#endif //BASIC_STRING_DEFINITIONS_H