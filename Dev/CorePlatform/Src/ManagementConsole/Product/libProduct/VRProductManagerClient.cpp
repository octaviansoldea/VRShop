#include <iostream>
#include <string>

#include "VRServerClientCommands.h"

#include <QByteArray>
#include <QDataStream>

#include "VRProductShopClient.h"

#include "VRClient.h"

#include "VRProductManagerClient.h"

using namespace VR;
using namespace std;
using namespace osg;

//-----------------------------------------------------------------------------

ProductManagerClient::ProductManagerClient()	{
	m_pClient = new Client;
	m_pProduct = new ProductShopClient;

	connect(m_pClient,SIGNAL(done()),this,SLOT(slotReceiveProductParams()));
}

//-----------------------------------------------------------------------------

ProductManagerClient::~ProductManagerClient()	{
	delete m_pClient;
	delete m_pProduct;
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

void ProductManagerClient::requestProductParams(const std::string & astrProductName)	{
	//Here establish client - server communication
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);
	QString aqstrProductName = astrProductName.c_str();

	char chType = ServerClientCommands::PRODUCT_REQUEST;

	out << quint64(0) << quint8(chType) << aqstrProductName;

	m_pClient->sendRequest(block);
}

//-----------------------------------------------------------------------------

void ProductManagerClient::slotReceiveProductParams()	{
	QByteArray & data = m_pClient->getTransmittedData();

	QDataStream out(&data,QIODevice::ReadOnly);
	out.setVersion(QDataStream::Qt_4_8);

	quint8 nType;	//Type of the data received
	QString qstrDataFromServer;

	out >> nType >> qstrDataFromServer;

	string strDataFromServer = qstrDataFromServer.toStdString(); //m_pClient->m_qstrAvatarsData.toStdString();

	m_pProduct->initFromSQLData(strDataFromServer);

	emit signalProductInitialized();
}

//-----------------------------------------------------------------------------

void ProductManagerClient::initProduct(const std::string & astrProductName)	{
	requestProductParams(astrProductName);
}
