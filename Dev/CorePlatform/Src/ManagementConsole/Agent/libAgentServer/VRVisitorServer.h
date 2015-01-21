#ifndef VR_VISITOR_SERVER_H
#define VR_VISITOR_SERVER_H

#include <list>
#include <string>

namespace VR	{
	class VisitorServer {
	public:
		VisitorServer();
		~VisitorServer();

		struct VisitorServerParams	{
			std::string m_strIP;
		};
	};
}
#endif //VR_VISITOR_SERVER_H