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

AgentManagerClient::AgentManagerClient(AbstractUser * apAbstractUser, QObject * apParent) : AbstractManagerClient(apParent)	{
	m_pVisitor = (Visitor*)apAbstractUser;

	connect(m_pClient,SIGNAL(done()),this,SLOT(slotReceiveDataFromServer()));
}

//------------------------------------------------------------------------------

AgentManagerClient::~AgentManagerClient()	{
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
	int nSuccess;

	out >> nType >> nSuccess;

	switch (nType)	{
	case ServerClientCommands::SIGN_IN_REQUEST:
		{
			if (nSuccess == ServerClientCommands::PASSED)	{
				userApproved(tostr(nSuccess));
			} else {
				requestToServer(ServerClientCommands::SIGN_UP_REQUEST);
			}
			break;
		}

	case ServerClientCommands::SIGN_UP_REQUEST:
		{
			if (nSuccess == ServerClientCommands::PASSED)	{
				userApproved(tostr(nSuccess));
			} else {
				break;
			}
			break;
		}

	case ServerClientCommands::SIGN_OUT_REQUEST:
		{
			if (nSuccess == ServerClientCommands::PASSED)	{	//Successfully signed out
				m_pVisitor->setUserIDName(tostr(0));
			} else {
				break;
			}
			break;
		}

	case ServerClientCommands::MODIFY_USER_ACCOUNT_REQUEST:
		{
			if (nSuccess == ServerClientCommands::PASSED)	{	//Successfully modified account settings
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
	AbstractManagerClientParams * apAbstractManagerClientParams
)	{

	AgentClientParams * pAcp = (AgentClientParams*)apAbstractManagerClientParams;

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);

	int nType = aenumOperationType;
	out << quint64(0) << quint8(nType);

	switch (nType)	{
	case ServerClientCommands::SIGN_IN_REQUEST:
		{
			QString qstrUser = pAcp->strUserName.c_str();
			QString qstrPsw = pAcp->strPassword.c_str();
			out << qstrUser << qstrPsw;

			break;
		}
	case ServerClientCommands::SIGN_OUT_REQUEST:
		{
			QString qstrUser = m_pVisitor->getUserIDName().c_str();
			out << qstrUser;

			break;
		}
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

			if (nType == ServerClientCommands::MODIFY_USER_ACCOUNT_REQUEST)	{
				QString qstrUserIDName = m_pVisitor->getUserIDName().c_str();
				out << qstrUserIDName;
			}

			out << qstrFirstName << qstrLastName << qstrEMail << qstrPsw;
			break;
		}

	default:
		return;
	}

	m_pClient->sendRequest(block);
}

//------------------------------------------------------------------------------

void AgentManagerClient::userApproved(const std::string & astrUserName)	{
	m_pVisitor->setUserIDName(astrUserName);
	emit done();
}