#include <iostream>
#include <string>

#include <QByteArray>
#include <QDataStream>

#include "VRProductShopClient.h"

#include "VRClient.h"

#include "VRProductManagerClient.h"

using namespace VR;
using namespace std;
using namespace osg;

//-----------------------------------------------------------------------------

ProductManagerClient::ProductManagerClient() : m_pClient(0), m_Product(0)	{
	m_pClient = new Client;

	connect(m_pClient,SIGNAL(done()),this,SLOT(slotReceiveProductParams()));
}

//-----------------------------------------------------------------------------

ProductManagerClient::~ProductManagerClient()	{
	delete m_pClient;
	delete m_Product;
}

//==============================================================================

const char* ProductManagerClient::className() const	{
	return "ProductManagerClient";
}

//--------------------------------------------------------------------------

ProductShopClient * ProductManagerClient::getProduct()	{
	return m_Product;
}

//-----------------------------------------------------------------------------

void ProductManagerClient::requestProductParams(const std::string & astrProductName)	{
	//Here establish client - server communication
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);
	QString aqstrProductName = astrProductName.c_str();
	
	out << quint64(0) << quint8('P') << aqstrProductName;

	/*
		SHEMA:	quint64(0) - size
				quint8('P') - product
				request
	*/

	m_pClient->sendRequest(block);
}

//-----------------------------------------------------------------------------

void ProductManagerClient::slotReceiveProductParams()	{

	QByteArray & data = m_pClient->getData();

	QDataStream in(&data,QIODevice::ReadOnly);
	in.setVersion(QDataStream::Qt_4_8);

	quint64 nSize;
	quint8 nType;

	in >> nSize >> nType;

	string strSqlData(data.begin(),data.end());

	m_Product = new ProductShopClient;
	m_Product->initFromSQLData(strSqlData);

	emit signalProductInitialized();
}

//-----------------------------------------------------------------------------

void ProductManagerClient::initProduct(const std::string & astrProductName)	{
	requestProductParams(astrProductName);
}
