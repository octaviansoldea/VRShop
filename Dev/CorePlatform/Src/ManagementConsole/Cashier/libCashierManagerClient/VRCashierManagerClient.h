#ifndef VR_CASHIER_MANAGER_CLIENT_H
#define VR_CASHIER_MANAGER_CLIENT_H

#include <QObject>

#include "VRAbstractManagerClient.h"

namespace VR {
	class ServerClientCommands;
	class Client;

	class BasketClient;

	class CashierManagerClient : public AbstractManagerClient	{
	public:
		CashierManagerClient(Client * apClient, QObject *parent=0);
		virtual ~CashierManagerClient();

		const char* className() const;

		struct CashierManagerClientParams : public AbstractManagerClientParams {
			std::string m_strVisitorName;
			std::string m_strProductName;
			std::string m_strBasketProdQty;
		};

	protected:
		virtual void requestToServer(
			const ServerClientCommands::OperationType & aenumOperationType, 
			AbstractManagerClientParams * apAbstractManagerClientParams=0
		);

	public:
		void removeFromBasketClicked(const std::string & astrUserID, const std::string & astrProductName);
		void moreProductInfoClicked(const std::string & astrProductName);
		void proceedAndPayCashier(const std::string & astrUserID, BasketClient * apBasket);

		void productInfoData(QDataStream & aDataStreamCashier);
		void basketPurchaseData(QDataStream & aDataStreamCashier);
	};
}
#endif //VR_CASHIER_MANAGER_CLIENT_H