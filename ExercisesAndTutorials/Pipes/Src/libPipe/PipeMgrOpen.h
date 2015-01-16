#ifndef PIPE_MGR_OPEN_H
#define PIPE_MGR_OPEN_H

#include "PipeMgr.h"

class PipeMgrOpen : virtual public PipeMgr {
protected:
	bool openPipe(DWORD adwDesiredAccess);
};


#endif //PIPE_MGR_OPEN_H