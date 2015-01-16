#ifndef VR_PIPE_SERVER_H
#define VR_PIPE_SERVER_H

#include <string>

#include <Windows.h>

namespace VR	{
	class PipeServer {
	public:
		PipeServer();
		~PipeServer();

		bool initializeAndRunServer(std::string & astrPipeName);
		void closeServer();

	private:
		//HANDLE m_hEvents;
		LPCTSTR m_lpszPipeName;
	};
}
#endif //VR_PIPE_SERVER_H