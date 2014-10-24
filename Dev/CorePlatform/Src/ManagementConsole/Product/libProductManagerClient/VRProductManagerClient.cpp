#include <iostream>
#include <string>

#include "BasicStringDefinitions.h"
#include "VRServerClientCommands.h"

#include <QByteArray>
#include <QDataStream>

#include "VRProductShopClient.h"
#include "VRBasketClient.h"
#include "VRModelViewControllerClient.h"

#include "VRClient.h"

#include "VRProductManagerClient.h"

using namespace VR;
using namespace std;

//-----------------------------------------------------------------------------

ProductManagerClient::ProductManagerClient(
ModelViewControllerClient * apMVCClient, 
BasketClient * apBasketClient,
QObject * apParent) : 
m_pMVCClient(apMVCClient), m_pBasket(apBasketClient), AbstractManagerClient(apParent),
m_pProduct(0)	{
	connect(m_pClient,SIGNAL(done()),this,SLOT(slotReceiveDataFromServer()));
}

//-----------------------------------------------------------------------------

ProductManagerClient::~ProductManagerClient()	{
}

//==============================================================================

const char* ProductManagerClient::className() const	{
	return "ProductManagerClient";
}

//--------------------------------------------------------------------------

ProductShopClient * ProductManagerClient::getProduct()	{
	return m_pProduct;
}

//-----------------------------------------------------------------------------

void ProductManagerClient::requestToServer(
	const enum ServerClientCommands::OPERATION_TYPE & aenumOperationType, 
	AbstractManagerClientParams * apAbstractManagerClientParams
)	{

	ProductManagerClientParams * pPp = (ProductManagerClientParams*)apAbstractManagerClientParams;

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);

	int nType = aenumOperationType;
	out << quint64(0) << quint8(nType);

	switch (nType)	{
	case ServerClientCommands::PRODUCT_REQUEST:
		{
			QString qstrProductName = pPp->m_strProductName.c_str();
			out << qstrProductName;

			break;
		}

	case ServerClientCommands::PRODUCT_TO_BASKET_REQUEST:
		{
			QString qstrUserIDName = pPp->m_strUserIDName.c_str();
			QString qstrProductName = pPp->m_strProductName.c_str();
			float flProductQuantity = pPp->m_flProductQuantity;

			out << qstrUserIDName << qstrProductName << flProductQuantity;

			break;
		}
	case ServerClientCommands::REMOVE_PRODUCT_REQUEST:
		{
			QString qstrUserIDName = pPp->m_strUserIDName.c_str();
			QString qstrProductName = pPp->m_strProductName.c_str();
			float flProductQuantity = pPp->m_flProductQuantity;

			out << qstrUserIDName << qstrProductName << flProductQuantity;

			break;
		}
	case ServerClientCommands::MODIFY_PRODUCT_REQUEST:
		{
			QString qstrUserIDName = pPp->m_strUserIDName.c_str();
			QString qstrProductName = pPp->m_strProductName.c_str();
			float flProductQuantity = pPp->m_flProductQuantity;
			float flProductNewQuantity = pPp->m_flProductNewQuantity;

			out << qstrUserIDName << qstrProductName << flProductQuantity << flProductNewQuantity;

			break;
		}
	default:
		{
			return;
		}
	}

	m_pClient->sendRequest(block);
}

//-----------------------------------------------------------------------------

void ProductManagerClient::slotReceiveDataFromServer()	{
	QByteArray & data = m_pClient->getTransmittedData();

	QDataStream out(&data,QIODevice::ReadOnly);
	out.setVersion(QDataStream::Qt_4_8);

	quint8 nType;	//Type of the data received
	out >> nType;

	switch (nType)	{
	case ServerClientCommands::PRODUCT_REQUEST:
		{
			QString qstrDataFromServer;
			out >> qstrDataFromServer;

			ProductShopClient product;
			product.initFromSQLData(qstrDataFromServer.toStdString());

			emit m_pMVCClient->signalProductInitialized(&product);
			
			break;
		}		
	case ServerClientCommands::PRODUCT_TO_BASKET_REQUEST:
		{
			float flProductQuantity;
			out >> flProductQuantity;

			if (flProductQuantity == 0)	{
				break;
			}

			ProductShopClientParams pP;
			m_pProduct->getParams(pP);

			ProductShopClient * pProduct = new ProductShopClient(pP);
			pProduct->setQuantity(flProductQuantity);
			m_pBasket->addProduct(pProduct);

			break;
		}
	case ServerClientCommands::REMOVE_PRODUCT_REQUEST:
		{
			bool bRes;
			out >> bRes;

			if (bRes == 0)	{
				break;
			}

			ProductShopClient * pProduct = getProduct();
			m_pBasket->removeProduct(pProduct);

			break;
		}
	case ServerClientCommands::MODIFY_PRODUCT_REQUEST:
		{
			float flNewValue;
			out >> flNewValue;

			ProductShopClient * pProduct = getProduct();
			pProduct->setQuantity(flNewValue);

			emit m_pMVCClient->signalNewProductQuantity(flNewValue);

			break;
		}
	default:
		break;
	}
}

//-----------------------------------------------------------------------------

void ProductManagerClient::addProduct2Basket(const string & astrUserID, ProductShopClient * apProductShopClient)	{
	m_pProduct = apProductShopClient;

	ProductManagerClient::ProductManagerClientParams pmcp;
	pmcp.m_strUserIDName = astrUserID;
	pmcp.m_strProductName = apProductShopClient->getProductName();
	pmcp.m_flProductQuantity = apProductShopClient->getQuantity();

	requestToServer(ServerClientCommands::PRODUCT_TO_BASKET_REQUEST,&pmcp);
}

//----------------------------------------------------------------------

void ProductManagerClient::removeProductRequest(const string & astrUserID, ProductShopClient * apProduct)	{
	m_pProduct = apProduct;

	ProductManagerClient::ProductManagerClientParams pmcp;
	pmcp.m_strUserIDName = astrUserID;
	pmcp.m_strProductName = apProduct->getProductName();
	pmcp.m_flProductQuantity = apProduct->getQuantity();

	requestToServer(ServerClientCommands::REMOVE_PRODUCT_REQUEST,&pmcp);
}

//----------------------------------------------------------------------

void ProductManagerClient::productClicked(string & astrProductName)	{
	ProductManagerClient::ProductManagerClientParams pmcp;
	pmcp.m_strProductName = astrProductName;

	requestToServer(ServerClientCommands::PRODUCT_REQUEST,&pmcp);
}

//----------------------------------------------------------------------

void ProductManagerClient::modifyProductQuantityRequest(const string & astrUserID, ProductShopClient * apProduct, float aflNewQuantity)	{
	m_pProduct = apProduct;

	ProductManagerClient::ProductManagerClientParams pmcp;
	pmcp.m_strUserIDName = astrUserID;
	pmcp.m_strProductName = apProduct->getProductName();
	pmcp.m_flProductQuantity = apProduct->getQuantity();
	pmcp.m_flProductNewQuantity = aflNewQuantity;

	requestToServer(ServerClientCommands::MODIFY_PRODUCT_REQUEST,&pmcp);
}