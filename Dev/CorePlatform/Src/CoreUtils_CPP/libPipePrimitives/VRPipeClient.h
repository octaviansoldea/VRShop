#ifndef VR_PIPE_CLIENT_H
#define VR_PIPE_CLIENT_H

#include <string>

#include <Windows.h>

namespace VR	{
	class PipeClient {
	public:
		PipeClient(std::string & astrPipeName);
		~PipeClient();

		bool isPipeAccessible();

	private:
		HANDLE m_hPipe;
		std::string m_strPipeName;
	};
}
#endif //VR_PIPE_CLIENT_H