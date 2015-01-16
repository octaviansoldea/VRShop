#ifndef PIPE_MGR_CREATE_CONNECT_H
#define PIPE_MGR_CREATE_CONNECT_H

#include "PipeMgr.h"

class PipeMgrCreateConnect : virtual public PipeMgr {
	bool createPipe(DWORD adwOpenMode);
	bool connectPipe();
protected:
	bool createAndConnect(DWORD adwOpenMode);
};

#endif //PIPE_MGR_CREATE_CONNECT_H