#ifndef STRING_MANIPULATION_H
#define STRING_MANIPULATION_H

#include <string>
#include <vector>

using namespace std;

bool isInString(const std::string & astrName, const std::string & astrField);

bool isAtEndOfString(const std::string & astrName, const std::string & astrField);

std::vector<std::string> splitString(std::string & astrName, const std::string & astrDelimiters);

#endif	//STRING_MANIPULATION_H