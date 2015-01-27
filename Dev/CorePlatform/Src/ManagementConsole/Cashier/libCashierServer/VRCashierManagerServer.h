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

		struct CashierManagerServerParams	{
			std::string m_strUserIDName;
			std::string m_strProductName;
			float m_flProductQuantity;
		};

		enum ORDER_STATUS	{
			RESERVED = 1,
			CONFIRMED,
			DELIVERED
		};

		static DatabaseInterfaceParams getDBParams();
		static std::vector<std::pair<std::string,std::string>> getDBElements();
		static std::string getTableName();
		static std::string getDatabaseName();

		static void createDB();

		static DatabaseInterface * getDatabaseInterface();

	private:
		static DatabaseInterface m_DICashier;

	public:
		bool addProduct2OrdersReserved(const CashierManagerServerParams & aCMSP);
		bool removeProductFromOrdersReserved(const CashierManagerServerParams & aCMSP);
		bool modifyProductOrdersReserved(const CashierManagerServerParams & aCMSP);
		
		static void clearProductsReserved(const std::string & astrUserName);

		static std::list<std::string> getActiveOrdersList();

		static void orderConfirmed(const std::string & astrUserName);
	};
}
#endif //VR_CASHIER_MANAGER_SERVER_H