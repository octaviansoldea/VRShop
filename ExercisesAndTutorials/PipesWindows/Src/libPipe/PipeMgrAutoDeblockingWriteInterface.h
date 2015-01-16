#ifndef PIPE_MGR_AUTO_DEBLOCKING_WRITE_INTERFACE_H
#define PIPE_MGR_AUTO_DEBLOCKING_WRITE_INTERFACE_H

#include "PipeMgrAutoDeblocking.h"

class PipeMgrAutoDeblockingWriteInterface : public PipeMgrAutoDeblocking {
	bool createPipe();
	bool connectPipe();
public:

	bool createAndConnectAndTransmitPIDAndHandle();
	bool write(const unsigned char * apuchMessage, int anLength);
};

#endif //PIPE_MGR_AUTO_DEBLOCKING_WRITE_INTERFACE_H