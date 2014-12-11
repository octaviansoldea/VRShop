#include <iostream>
#include <string>

#include "BasicStringDefinitions.h"
#include "VRServerClientCommands.h"

#include <QByteArray>
#include <QDataStream>

#include "VRProductShopClient.h"

#include "VRClient.h"

#include "VRProductManagerClient.h"

using namespace VR;
using namespace std;

//-----------------------------------------------------------------------------

ProductManagerClient::ProductManagerClient(
Client * apClient,QObject * apParent) : 
AbstractManagerClient(apClient, apParent),m_pProduct(0)	{
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
	const ServerClientCommands::OperationType & aenumOperationType, 
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
			m_pProduct = pPp->m_pProduct;
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

//----------------------------------------------------------------------

void ProductManagerClient::addProduct2Basket(ProductManagerClientParams & aPMCP)	{
	requestToServer(ServerClientCommands::PRODUCT_TO_BASKET_REQUEST,&aPMCP);
}

//----------------------------------------------------------------------

void ProductManagerClient::initProductFromData(QDataStream & aDataStreamProduct, ProductShopClient * apProduct)	{
	QString qstrDataFromServer;
	aDataStreamProduct >> qstrDataFromServer;

	apProduct->initFromSQLData(qstrDataFromServer.toStdString());

	m_pProduct = apProduct;
}

//----------------------------------------------------------------------

bool ProductManagerClient::addProduct2Basket(QDataStream & aDataStreamProduct, ProductShopClient * apProduct)	{
	float flProductQuantity;
	aDataStreamProduct >> flProductQuantity;

	if (flProductQuantity == 0)	{
		return false;
	}

	ProductShopClientParams pP;
	getProduct()->getParams(pP);

	apProduct->setParams(pP);
	apProduct->setQuantity(flProductQuantity);

	return true;
}

//----------------------------------------------------------------------

ProductShopClient * ProductManagerClient::removeProductFromBasket(QDataStream & aDataStreamProduct)	{
	bool bRes;
	aDataStreamProduct >> bRes;

	if (bRes == 0)	{
		return 0;
	}

	return (getProduct());
}

//----------------------------------------------------------------------

float ProductManagerClient::modifyProductQuantityRequest(QDataStream & aDataStreamProduct)	{
	float flNewValue;
	aDataStreamProduct >> flNewValue;

	ProductShopClient * pProduct = getProduct();
	pProduct->setQuantity(flNewValue);

	return flNewValue;
}