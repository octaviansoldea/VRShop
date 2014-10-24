#ifndef VR_CASHIER_MANAGER_CLIENT_H
#define VR_CASHIER_MANAGER_CLIENT_H

#include <QObject>

#include "VRAbstractManagerClient.h"

#include "VRServerClientCommands.h"

namespace VR {
	class CashierManagerClient : public AbstractManagerClient	{
	public:
		CashierManagerClient(QObject *parent=0);
		virtual ~CashierManagerClient();

		const char* className() const;

		struct CashierManagerClientParams : public AbstractManagerClientParams {
			std::string m_strVisitorName;
			std::string m_strProductName;
			std::string m_strBasketProdQty;
		};

		virtual void requestToServer(
			const enum ServerClientCommands::OPERATION_TYPE & aenumOperationType, 
			AbstractManagerClientParams * apAbstractManagerClientParams=0
		);

		virtual void slotReceiveDataFromServer();
	};
}
#endif //VR_CASHIER_MANAGER_CLIENT_H