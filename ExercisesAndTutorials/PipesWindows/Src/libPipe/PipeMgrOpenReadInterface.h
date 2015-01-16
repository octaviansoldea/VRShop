#ifndef PIPE_MGR_OPEN_READ_INTERFACE_H
#define PIPE_MGR_OPEN_READ_INTERFACE_H

#include "PipeMgrOpen.h"
#include "PipeMgrReadInterface.h"

class PipeMgrOpenReadInterface : public PipeMgrOpen, public PipeMgrReadInterface {
public:
	bool openPipe();
};


#endif //PIPE_MGR_OPEN_READ_INTERFACE_H