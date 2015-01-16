#include <string>

#include "BasicStringDefinitions.h"

#include "PipeNamesMgr.h"

using namespace std;

void PipeNamesMgr::compute_MediaType_Id_Name(string & astr_MediaType_Id_Name, const string & astrMediaType, int anID) {
	string strID = itostr(anID);
	astr_MediaType_Id_Name = astrMediaType + strID;
}

void PipeNamesMgr::computePipeName(string & astrPipeName, const string & astrMediaType, int anID) {
	std::string str_MediaType_Id_Name;
	compute_MediaType_Id_Name(str_MediaType_Id_Name, astrMediaType, anID);
	astrPipeName = std::string("\\\\.\\pipe\\pipeName") + str_MediaType_Id_Name;
}

void PipeNamesMgr::computePipeNameEncodedStream(string & astrPipeName, const string & astrAVD, int anID) {
	computePipeName(astrPipeName, astrAVD, anID);
}

void PipeNamesMgr::computePipeNameYUV(string & astrPipeName, int anID) {
	computePipeName(astrPipeName, "YUV", anID);
}
