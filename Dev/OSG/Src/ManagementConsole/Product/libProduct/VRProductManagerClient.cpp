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

ProductManagerClient::ProductManagerClient() : m_pClient(0), m_pProduct(0)	{
	m_pClient = new Client;
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
	
	out << quint64(0) << quint8('P') << aqstrProductName;

	/*
		PATTERN:	quint64(0) - size
					quint8('P') - product
					request
	*/

	m_pClient->sendRequest(block);
}

//-----------------------------------------------------------------------------

void ProductManagerClient::slotReceiveProductParams()	{
	QDataStream out(&m_pClient->getTcpSocket());
	out.setVersion(QDataStream::Qt_4_8);
	QTcpSocket * pSocket = static_cast<QTcpSocket*>(out.device());

	int nBytesAvaliable = pSocket->bytesAvailable();

	QString qstrTest;
	out >> qstrTest;

	string strTest = qstrTest.toStdString();
	std::cout << "strTest: " << strTest << endl;

	m_pProduct = new ProductShopClient;
	m_pProduct->initFromSQLData(strTest);

	emit signalProductInitialized();
}

//-----------------------------------------------------------------------------

void ProductManagerClient::initProduct(const std::string & astrProductName)	{
	requestProductParams(astrProductName);
}
