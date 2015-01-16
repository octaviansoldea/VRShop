#ifndef PIPE_MGR_CREATE_CONNECT_WRITE_INTERFACE_H
#define PIPE_MGR_CREATE_CONNECT_WRITE_INTERFACE_H

#include "PipeMgrCreateConnect.h"
#include "PipeMgrWriteInterface.h"

class PipeMgrCreateConnectWriteInterface : public PipeMgrCreateConnect, public PipeMgrWriteInterface {
public:
	bool createAndConnect();
};

#endif //PIPE_MGR_CREATE_CONNECT_WRITE_INTERFACE_H