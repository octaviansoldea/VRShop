#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <iostream>
#include <exception>
#include <string>


#ifdef _WIN32
unsigned __int64 GetFileSizeFromName(const char * astrFileName);
#endif //_WIN32

void CheckedFileOpen(FILE ** appfp, const std::string & astrFileName, const char * apchMode);

class ExceptionSuffix: public std::exception
{
public:
  virtual const char* what() const throw();
};

std::string getSuffix(const std::string & astrFileName);

#endif //FILE_OPERATIONS_H