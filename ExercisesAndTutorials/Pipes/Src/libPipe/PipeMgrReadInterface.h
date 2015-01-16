#ifndef PIPE_MGR_READ_INTERFACE_H
#define PIPE_MGR_READ_INTERFACE_H

#include <string>

#include "PipeMgr.h"

class PipeMgrReadInterface : virtual public PipeMgr {
public:
	bool read(std::string & astrMessage);
};


#endif //PIPE_MGR_READ_INTERFACE_H