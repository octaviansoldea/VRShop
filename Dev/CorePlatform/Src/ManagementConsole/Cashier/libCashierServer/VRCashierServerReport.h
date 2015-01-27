#ifndef VR_CASHIER_SERVER_REPORT_H
#define VR_CASHIER_SERVER_REPORT_H

#include <string>
#include <list>

namespace VR	{
	class CashierServerReport	{
	public:
		CashierServerReport();

		static void createOrdersReportHeader(std::list<std::string> & alststrOrdersData, std::ofstream & aOutputFile);
		static void createOrdersReportCustomer(std::string & astrOrdersData, std::ofstream & aOutputFile);
		static void createOrdersReportListProducts(std::list<std::string> & alststrOrdersData, std::ofstream & aOutputFile);
	};
}
#endif //VR_CASHIER_SERVER_REPORT_H