#include <iostream>
#include "BasicStringDefinitions.h"

#include "VRClient.h"
#include "VRAbstractUser.h"
#include "VRVisitor.h"

#include "VRSignUp_GUI.h"

#include "VRAgentManagerClient.h"

using namespace VR;
using namespace std;


//==============================================================================

AgentManagerClient::AgentManagerClient(AbstractUser * apAbstractUser)	{
	m_pClient = new Client;
	m_pAbstractUser = (Visitor*)apAbstractUser;

	connect(m_pClient,SIGNAL(done()),this,SLOT(slotReceiveDataFromServer()));
}

//------------------------------------------------------------------------------

AgentManagerClient::~AgentManagerClient()	{
	delete m_pClient;
}

//------------------------------------------------------------------------------

const char* AgentManagerClient::className() const	{
	return "AgentManagerClient";
}

//------------------------------------------------------------------------------

void AgentManagerClient::slotReceiveDataFromServer()	{
	QByteArray & data = m_pClient->getTransmittedData();

	QDataStream out(&data,QIODevice::ReadOnly);
	out.setVersion(QDataStream::Qt_4_8);

	quint8 nType;	//Type of the data received
	QString qstrDataFromServer;

	out >> nType >> qstrDataFromServer;

	switch (nType)	{
	case ServerClientCommands::SIGN_IN_REQUEST:
		{
			if (qstrDataFromServer.toInt() == ServerClientCommands::PASSED)	{
				userApproved(qstrDataFromServer.toStdString());
			} else {
				requestToServer(ServerClientCommands::SIGN_UP_REQUEST);
			}
			break;
		}

	case ServerClientCommands::SIGN_UP_REQUEST:
		{
			if (qstrDataFromServer.toInt() == ServerClientCommands::PASSED)	{
				userApproved(qstrDataFromServer.toStdString());
			} else {
				break;
			}
			break;
		}

	case ServerClientCommands::SIGN_OUT_REQUEST:
		{
			if (qstrDataFromServer.toInt() == ServerClientCommands::PASSED)	{	//Successfully signed out
				m_pAbstractUser->setUserIDName(tostr(0));
			} else {
				break;
			}
			break;
		}

	case ServerClientCommands::MODIFY_USER_ACCOUNT_REQUEST:
		{
			if (qstrDataFromServer.toInt() == ServerClientCommands::PASSED)	{	//Successfully modified account settings
			} else {
				break;
			}
			break;
		}
	}
}

//------------------------------------------------------------------------------

void AgentManagerClient::requestToServer(
	const enum ServerClientCommands::OPERATION_TYPE & aenumOperationType, 
	AgentClientParams * apAgentClientParams
)	{
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);

	QString aqstrInputData;

	int nType = aenumOperationType;

	switch (nType)	{
	case ServerClientCommands::SIGN_IN_REQUEST:
		aqstrInputData = (apAgentClientParams->strUserName + ";" + apAgentClientParams->strPassword).c_str();
		break;

	case ServerClientCommands::SIGN_OUT_REQUEST:
		aqstrInputData = m_pAbstractUser->getUserIDName().c_str();
		break;

	case ServerClientCommands::SIGN_UP_REQUEST:
	case ServerClientCommands::MODIFY_USER_ACCOUNT_REQUEST:
		{
			SignUp_GUI signUp;

			if (nType == ServerClientCommands::MODIFY_USER_ACCOUNT_REQUEST)	{
				signUp.m_pLineEditPassword->setPlaceholderText("Type old password");
				signUp.m_pLineEditRetypePassword->setPlaceholderText("Type new password");
			}

			signUp.setWindowFlags(Qt::FramelessWindowHint);
			bool bRes = signUp.exec();

			if (bRes != QDialog::Accepted)	{
				return;
			}

			QString qstrEMail = signUp.m_pLineEditEMail->text();
			QString qstrPsw = signUp.m_pLineEditPassword->text();
			QString qstrFirstName = signUp.m_pLineEditFirstName->text();
			QString qstrLastName = signUp.m_pLineEditLastName->text();

			aqstrInputData = "";

			if (nType == ServerClientCommands::MODIFY_USER_ACCOUNT_REQUEST)	{
				QString qstrUserIDName = (m_pAbstractUser->getUserIDName() + ";").c_str();
				aqstrInputData += qstrUserIDName;
			}

			aqstrInputData += (qstrFirstName + ";" + qstrLastName + ";" + qstrEMail + ";" + qstrPsw);
			break;
		}

	default:
		return;
	}

	out << quint64(0) << quint8(nType) << aqstrInputData;

	m_pClient->sendRequest(block);
}

//------------------------------------------------------------------------------

void AgentManagerClient::userApproved(const std::string & astrUserName)	{
	m_pAbstractUser->setUserIDName(astrUserName);
	emit done();
}