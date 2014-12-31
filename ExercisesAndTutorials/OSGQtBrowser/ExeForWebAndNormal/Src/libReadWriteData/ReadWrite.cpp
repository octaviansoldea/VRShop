#include <fstream>
#include <iostream>

#include <string>

#include "ReadWrite.h"

using namespace std;
using namespace VR;

//--------------------------------------------------------------------

ReadWrite::ReadWrite() {
}

//--------------------------------------------------------------------

ReadWrite::~ReadWrite()	{
}

//--------------------------------------------------------------------

int ReadWrite::readFileData(std::string & astrFileName)	{
	ofstream myfile;
	myfile.open(astrFileName,std::ios::app | std::ios::out);
	if(myfile.is_open())	{
		myfile << "Writing this to a file.\n";
	} else {
		std::cout << "Not opened" << std::endl;
	}
	
	myfile.close();
	return 1;
}

//--------------------------------------------------------------------

void ReadWrite::writeFileData(std::string & astrFileName)	{
}
