#ifndef PIPE_MGR_WRITE_INTERFACE_H
#define PIPE_MGR_WRITE_INTERFACE_H

#include "PipeMgr.h"

class PipeMgrWriteInterface : virtual public PipeMgr {
public:
	bool write(const unsigned char * apuchMessage, int anLength);
};

#endif //PIPE_MGR_WRITE_INTERFACE_H