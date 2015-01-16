#ifndef PIPE_MGR_AUTO_DEBLOCKING_H
#define PIPE_MGR_AUTO_DEBLOCKING_H

#include <windows.h>
#include <string>

#include "PipeMgr.h"
//#include "PipeTimeConstants.h"

class PipeMgrAutoDeblocking : public PipeMgr {
protected:
	struct PIDAndHandle {
		DWORD m_PID;
		HANDLE m_HANDLE;
	};
	HANDLE m_Mutex;
	bool m_bMutexInitialized;

public:
	PipeMgrAutoDeblocking();
	virtual ~PipeMgrAutoDeblocking() = 0;

	virtual void initialize(const std::string & astrName, const std::string & astrMediaType, int anID);
};

#endif //PIPE_MGR_AUTO_DEBLOCKING_H