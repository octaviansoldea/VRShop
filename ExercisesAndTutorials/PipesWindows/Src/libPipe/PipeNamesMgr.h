#ifndef PIPE_NAMES_MGR_H
#define PIPE_NAMES_MGR_H

#include <string>

#include "BasicDefinitions.h"

class PipeNamesMgr {
	static void compute_MediaType_Id_Name(std::string & astr_MediaType_Id_Name, const std::string & astrMediaType, int anID);
public:
	static void computePipeName(std::string & astrPipeName, const std::string & astrMediaType, int anID);
	static void computePipeNameEncodedStream(std::string & astrPipeName, const std::string & astrAVD, int anID);
	static void computePipeNameYUV(std::string & astrPipeName, int anID);
};

#endif //PIPE_NAMES_MGR_H