#include <iostream>
#include "BasicStringDefinitions.h"

#include "VRClient.h"
#include "VRCashierManagerClient.h"

using namespace VR;
using namespace std;


//==============================================================================

CashierManagerClient::CashierManagerClient(QObject *parent) : AbstractManagerClient(parent)	{
	connect(m_pClient,SIGNAL(done()),this,SLOT(slotReceiveDataFromServer()));
}

//------------------------------------------------------------------------------

CashierManagerClient::~CashierManagerClient()	{
}

//------------------------------------------------------------------------------

const char* CashierManagerClient::className() const	{
	return "CashierManagerClient";
}

//------------------------------------------------------------------------------

void CashierManagerClient::slotReceiveDataFromServer()	{
	QByteArray & data = m_pClient->getTransmittedData();

	QDataStream out(&data,QIODevice::ReadOnly);
	out.setVersion(QDataStream::Qt_4_8);

	quint8 nType;	//Type of the data received
	out >> nType;

	switch (nType)	{
	case ServerClientCommands::PURCHASE_REQUEST:
		{
			int nOperationResult;
			out >> nOperationResult;
			switch (nOperationResult)	{
			case ServerClientCommands::PASSED:
				{
					
					break;
				}
			case ServerClientCommands::AUTHENTICATION_FAILED:
				{
					//Report to the user that his authentication failed
					break;
				}
			}
			break;
		}	//END PURCHASE_REQUEST
	case ServerClientCommands::USER_CONFIRMS_PURCHASE:
		{
			break;
		}
	default:
		break;
	}
}

//------------------------------------------------------------------------------

void CashierManagerClient::requestToServer(
const ServerClientCommands::OPERATION_TYPE & aenumOperationType, 
AbstractManagerClientParams * apAbstractManagerClientParams)	{

	CashierManagerClientParams * pParams = (CashierManagerClientParams*)apAbstractManagerClientParams;

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);

	QString qstrInputData;

	int nType = aenumOperationType;

	out << quint64(0) << quint8(nType);

	switch (nType)	{
	case ServerClientCommands::PURCHASE_REQUEST:
		{
			QString qstrVisitorName = pParams->m_strVisitorName.c_str();
			QString qstrBasketProdQty = pParams->m_strBasketProdQty.c_str();

			out << qstrVisitorName << qstrBasketProdQty;
			break;
		}
	case ServerClientCommands::USER_CONFIRMS_PURCHASE:
		{
			break;
		}
	case ServerClientCommands::PRODUCT_INFO_REQUEST:
		{
			break;
		}

	default:
		return;
	}
	
	m_pClient->sendRequest(block);
}

//------------------------------------------------------------------------------
