#ifndef VR_VISITOR_MANAGER_SERVER_H
#define VR_VISITOR_MANAGER_SERVER_H

#include <vector>
#include <string>

namespace VR	{
	class DatabaseInterface;
	struct DatabaseInterfaceParams;

	class VisitorManagerServer {
	public:
		VisitorManagerServer();
		~VisitorManagerServer();

		void registerVisitor(const std::string & astrVisitorIP, const int anUserID);
		static void unregisterVisitor(const std::string & astrUserID);

		static DatabaseInterfaceParams getDBParams();
		static std::vector<std::pair<std::string,std::string>> getDBElements();
		static std::string getTableName();
		static std::string getDatabaseName();

		static void createDB();

		static DatabaseInterface * getDatabaseInterface();

	private:
		static DatabaseInterface m_DIVisitor;
	};
}
#endif //VR_VISITOR_MANAGER_SERVER_H