#ifndef PIPE_MGR_H
#define PIPE_MGR_H

#include <windows.h>
#include <string>

//#include "PipeTimeConstants.h"

class PipeMgr {
protected:
	DWORD m_dwMode;
	
	bool m_bHandleInitialized;
	HANDLE m_hPipe;
	bool m_bSynchronizationInitialized;
	HANDLE m_hSynchronizationEvent;

	
	std::string m_str_Id_MediaType_Name;
	std::string m_strPipeName;
public:
	PipeMgr();
	virtual ~PipeMgr() = 0;

	virtual void initialize(const std::string & astrName, const std::string & astrMediaType, int anID);

	void ClosePipeHandle();

};

#endif //PIPE_MGR_H