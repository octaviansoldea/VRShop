#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H
#include <windows.h>

#include <iostream>
#include <exception>
#include <string>



unsigned __int64 GetFileSizeFromName(const char * astrFileName);

void CheckedFileOpen(FILE ** appfp, const std::string & astrFileName, const char * apchMode);

class ExceptionSuffix: public std::exception
{
public:
  virtual const char* what() const throw();
};

std::string getSuffix(const std::string & astrFileName);

#endif //FILE_OPERATIONS_H