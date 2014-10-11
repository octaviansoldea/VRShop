#ifndef VR_USER_ACCOUNT_MANAGER_H
#define VR_USER_ACCOUNT_MANAGER_H

#include <vector>
#include <string>

namespace VR	{
	class DatabaseInterface;
	struct DatabaseInterfaceParams;

	class UserAccountManager {
	public:
		UserAccountManager();
		~UserAccountManager();

		static DatabaseInterfaceParams getDBParams();
		static std::vector<std::pair<std::string,std::string>> getAccountElements();
		static std::string getTableName();
		static std::string getDatabaseName();

		static void createUserAccountDB();

		static DatabaseInterface * getDatabaseInterface();

	private:
		static DatabaseInterface m_DIUA;
	};
}
#endif //VR_USER_ACCOUNT_MANAGER_H