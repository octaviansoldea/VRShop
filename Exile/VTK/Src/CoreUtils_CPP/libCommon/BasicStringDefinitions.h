#ifndef BASIC_STRING_DEFINITIONS_H
#define BASIC_STRING_DEFINITIONS_H

#include <string>

std::string itostr(int anVal);
std::string GetLastErrorString();
bool isInString(const std::string & astrName, const std::string & astrField);

#endif //BASIC_STRING_DEFINITIONS_H