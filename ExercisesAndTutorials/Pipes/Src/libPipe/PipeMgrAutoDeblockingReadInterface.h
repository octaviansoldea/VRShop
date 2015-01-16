#ifndef PIPE_MGR_AUTO_DEBLOCKING_READ_INTERFACE_H
#define PIPE_MGR_AUTO_DEBLOCKING_READ_INTERFACE_H

#include <string>

#include "PipeMgrAutoDeblocking.h"

class PipeMgrAutoDeblockingReadInterface : public PipeMgrAutoDeblocking {
	PIDAndHandle m_PIDAndHandle;

	HANDLE m_hTerminatorPipe;
public:

	~PipeMgrAutoDeblockingReadInterface();

	bool openPipeAndReadPIDAndHandle();
	bool read(std::string & astrMessage);

	void autoDeblock();//no bool test need, becouse maybe the nFinishFlag is set
};

#endif //PIPE_MGR_AUTO_DEBLOCKING_READ_INTERFACE_H