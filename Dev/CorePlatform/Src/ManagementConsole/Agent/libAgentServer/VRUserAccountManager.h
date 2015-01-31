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
		static void createDB();

		static std::string getUserAddress(const int & anUserID);
		static std::string getUserAccountID(const std::string & astrUserID);

		static DatabaseInterface * getDatabaseInterface();

	private:
		static DatabaseInterface * m_pDIUA;

	public:
		static void constructStatics();
		static void deleteStatics();
	};
}
#endif //VR_USER_ACCOUNT_MANAGER_H