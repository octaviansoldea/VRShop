#ifndef PIPE_MGR_PEEK_H
#define PIPE_MGR_PEEK_H

#include <string>

#include "PipeMgr.h"

class PipeMgrPeek : virtual public PipeMgr {
public:
	bool peek(std::string & astrMessage);
};


#endif //PIPE_MGR_PEEK_H