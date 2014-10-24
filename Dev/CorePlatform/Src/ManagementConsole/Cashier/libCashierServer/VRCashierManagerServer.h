#ifndef VR_CASHIER_MANAGER_SERVER_H
#define VR_CASHIER_MANAGER_SERVER_H

#include <vector>
#include <string>

namespace VR	{
	class DatabaseInterface;
	struct DatabaseInterfaceParams;

	class CashierManagerServer {
	public:
		CashierManagerServer();
		~CashierManagerServer();

		static DatabaseInterfaceParams getDBParams();
		static std::vector<std::pair<std::string,std::string>> getDBElements();
		static std::string getTableName();
		static std::string getDatabaseName();

		static void createDB();

		static DatabaseInterface * getDatabaseInterface();

	private:
		static DatabaseInterface m_DICashier;
	};
}
#endif //VR_CASHIER_MANAGER_SERVER_H