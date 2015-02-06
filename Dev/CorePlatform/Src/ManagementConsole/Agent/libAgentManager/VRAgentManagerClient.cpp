#include <iostream>
#include "BasicStringDefinitions.h"

#include "VRClient.h"
#include "VRAbstractUser.h"
#include "VRVisitor.h"

#include "VRSignUp_GUI.h"

#include <fstream>

#include "VRAgentManagerClient.h"

using namespace VR;
using namespace std;


//==============================================================================

AgentManagerClient::AgentManagerClient(Client * apClient, QObject * apParent) :
m_pVisitor(0), AbstractManagerClient(apClient, apParent)	{
}

//------------------------------------------------------------------------------

AgentManagerClient::AgentManagerClient(Client * apClient, AbstractUser * apAbstractUser, QObject * apParent) : 
AbstractManagerClient(apClient, apParent)	{
	m_pVisitor = (Visitor*)apAbstractUser;
}

//------------------------------------------------------------------------------

AgentManagerClient::~AgentManagerClient()	{
}

//------------------------------------------------------------------------------

const char* AgentManagerClient::className() const	{
	return "AgentManagerClient";
}

//------------------------------------------------------------------------------

void AgentManagerClient::fillUserDetailsRequest(AgentManagerClient::AgentClientParams & aAgentClientParams, const std::string &astrUserID)	{
	aAgentClientParams.m_strUserID = astrUserID;

	requestToServer(ServerClientCommands::USER_PERSONAL_DATA, &aAgentClientParams);
}

//------------------------------------------------------------------------------

void AgentManagerClient::requestToServer(
	const ServerClientCommands::OperationType & aenumOperationType, 
	AbstractManagerClientParams * apAbstractManagerClientParams
)	{

	AgentClientParams * pAcp = static_cast<AgentClientParams*>(apAbstractManagerClientParams);

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);

	int nType = aenumOperationType;
	out << quint64(0) << quint8(nType);

	switch (nType)	{
	case ServerClientCommands::SIGN_IN_REQUEST:
		{
			QString qstrUser = pAcp->m_strUserName.c_str();
			QString qstrPsw = pAcp->m_strPassword.c_str();
			QString qstrUserID = pAcp->m_strUserID.c_str();
			out << qstrUser << qstrPsw << qstrUserID;

			break;
		}
	case ServerClientCommands::SIGN_OUT_REQUEST:
		{
			QString qstrUser = pAcp->m_strUserID.c_str();
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
			QString qstrUser = m_pVisitor->getUserIDName().c_str();

			out << qstrFirstName << qstrLastName << qstrEMail << qstrPsw << qstrUser;
			break;
		}
	case ServerClientCommands::USER_PERSONAL_DATA:
		{
			QString qstrFirstName = pAcp->m_strFirstName.c_str();
			QString qstrMiddleName = pAcp->m_strMiddleName.c_str();
			QString qstrLastName = pAcp->m_strLastName.c_str();
			QString qstrAddress = pAcp->m_strAddress.c_str();
			QString qstrCity = pAcp->m_strCity.c_str();
			QString qstrPostalCode = pAcp->m_strPostalCode.c_str();
			QString qstrState = pAcp->m_strState.c_str();
			QString qstrCountry = pAcp->m_strCountry.c_str();
			QString qstrUserID = pAcp->m_strUserID.c_str();

			out << qstrFirstName << qstrMiddleName << qstrLastName << qstrAddress << qstrCity << qstrPostalCode 
				<< qstrState << qstrCountry << qstrUserID;

			break;
		}
	default:
		return;
	}

	m_pClient->sendRequest(block);
}

//------------------------------------------------------------------------------

void AgentManagerClient::signInRequest(const string & astrUserName, const string & astrPassword, const string & astrUserID)	{
	AgentManagerClient::AgentClientParams acp;
	acp.m_strUserName = astrUserName;
	acp.m_strPassword = astrPassword;
	acp.m_strUserID = astrUserID;
	requestToServer(ServerClientCommands::SIGN_IN_REQUEST, &acp);
}

//------------------------------------------------------------------------------

void AgentManagerClient::signUpRequest()	{
	requestToServer(ServerClientCommands::SIGN_UP_REQUEST);
}

//------------------------------------------------------------------------------

void AgentManagerClient::signOutRequest(const std::string & astrUserName)	{
	AgentManagerClient::AgentClientParams acp;
	acp.m_strUserID = astrUserName;
	requestToServer(ServerClientCommands::SIGN_OUT_REQUEST, &acp);
}

//------------------------------------------------------------------------------

void AgentManagerClient::modifyAccountRequest()	{
	requestToServer(ServerClientCommands::MODIFY_USER_ACCOUNT_REQUEST);
}

//------------------------------------------------------------------------------

bool AgentManagerClient::signInRespond(QDataStream & aDataStreamProduct)	{
	int nSuccess;
	aDataStreamProduct >> nSuccess;

	if (nSuccess == ServerClientCommands::PASSED)	{
		m_pVisitor->userSignedIn();
//		emit done();

		return true;
	} else {
		requestToServer(ServerClientCommands::SIGN_UP_REQUEST);
		return false;
	}
}

//------------------------------------------------------------------------------

bool AgentManagerClient::signUpRespond(QDataStream & aDataStreamProduct)	{
	int nSuccess;
	aDataStreamProduct >> nSuccess;

	if (nSuccess == ServerClientCommands::PASSED)	{
		m_pVisitor->userSignedIn();
		emit done();

		return true;
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------

bool AgentManagerClient::signOutRespond(QDataStream & aDataStreamProduct)	{
	int nSuccess;
	aDataStreamProduct >> nSuccess;

	if (nSuccess == ServerClientCommands::PASSED)	{	//Successfully signed out
		m_pVisitor->userSignedOut();

		return true;
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------

bool AgentManagerClient::modifyAccountRespond(QDataStream & aDataStreamProduct)	{
	int nSuccess;
	aDataStreamProduct >> nSuccess;

	if (nSuccess == ServerClientCommands::PASSED)	{	//Successfully modified account settings
		return true;
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
