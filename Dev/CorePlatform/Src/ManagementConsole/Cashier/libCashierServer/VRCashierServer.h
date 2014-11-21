#ifndef VR_CASHIER_SERVER_H
#define VR_CASHIER_SERVER_H

#include <vector>

namespace VR	{
	class CashierServer	{
	public:
		CashierServer();

		const char* className() const;

		void prepareReceipt();
		const bool getIsTransactionApproved() const;


		void finalizeTransaction();

	private:
		bool canFirmExecuteOrder();
		bool canUserSettleReceipt();

		void transactionFinished(std::string & astrRequest);

		bool m_bIsTransactionApproved;
	};
}
#endif //VR_CASHIER_SERVER_H