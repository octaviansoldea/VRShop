#ifndef VR_CASHIER_MANAGER_CLIENT_H
#define VR_CASHIER_MANAGER_CLIENT_H

#include <QObject>

#include "VRAbstractManagerClient.h"

namespace VR {
	class ServerClientCommands;
	class ModelViewControllerClient;

	class BasketClient;

	class CashierManagerClient : public AbstractManagerClient	{
	public:
		CashierManagerClient(ModelViewControllerClient * apMVCClient, QObject *parent=0);
		virtual ~CashierManagerClient();

		const char* className() const;

		struct CashierManagerClientParams : public AbstractManagerClientParams {
			std::string m_strVisitorName;
			std::string m_strProductName;
			std::string m_strBasketProdQty;
		};

	protected:
		virtual void requestToServer(
			const ServerClientCommands::OPERATION_TYPE & aenumOperationType, 
			AbstractManagerClientParams * apAbstractManagerClientParams=0
		);

		virtual void slotReceiveDataFromServer();

	public:
		void removeFromBasketClicked(const std::string & astrUserID, const std::string & astrProductName);
		void moreProductInfoClicked(const std::string & astrProductName);
		void proceedAndPayCashier(const std::string & astrUserID, BasketClient * apBasket);

	private:
		ModelViewControllerClient * m_pMVCClient;
	};
}
#endif //VR_CASHIER_MANAGER_CLIENT_H