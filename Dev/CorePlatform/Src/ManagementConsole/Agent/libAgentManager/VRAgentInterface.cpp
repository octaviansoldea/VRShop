#include <string>
#include <iostream>

#include <QFrame>
#include <QToolButton>
#include <QLineEdit>
#include <QPushButton>

#include "VRAbstractUser.h"

#include "VRServerClientCommands.h"

#include "VRAgentManagerClient.h"

#include "VRAgentInterface.h"

using namespace VR;
using namespace std;

//----------------------------------------------------------------------

AgentInterface::AgentInterface(
QFrame * apFrameSettings,
QToolButton * apToolButtonUser,
QLineEdit * apLineEditPassword,
QLineEdit * apLineEditUserName,
QPushButton * apPushButtonSignIn,
QPushButton * apPushButtonSignOut,
QPushButton * apPushButtonRemoveAccount,
QPushButton * apPushButtonChangeSettings,
AbstractUser * apAbstractUser,
AgentManagerClient * apAgentMgr)	{
	m_pFrameSettings = apFrameSettings;
	m_pToolButtonUser = apToolButtonUser;
	m_pLineEditPassword = apLineEditPassword;
	m_pLineEditUserName = apLineEditUserName;
	m_pPushButtonSignIn = apPushButtonSignIn;
	m_pPushButtonSignOut = apPushButtonSignOut;
	m_pPushButtonRemoveAccount = apPushButtonRemoveAccount;
	m_pPushButtonChangeSettings = apPushButtonChangeSettings;
	m_pAbstractUser = apAbstractUser;

	m_pAgentMgr = apAgentMgr;

	m_pToolButtonUser->setVisible(false);
	m_pFrameSettings->setVisible(false);

	connect(m_pToolButtonUser,SIGNAL(toggled(bool)),this,SLOT(slotUserClicked(bool)));
	connect(m_pPushButtonSignIn,SIGNAL(clicked()),this,SLOT(slotSignUp()));
	connect(m_pLineEditPassword,SIGNAL(returnPressed()),this,SLOT(slotSignIn()));
	connect(m_pLineEditUserName,SIGNAL(returnPressed()),this,SLOT(slotSignIn()));

	connect(m_pAgentMgr,SIGNAL(done()),this,SLOT(slotSignedIn()));
}

//----------------------------------------------------------------------

AgentInterface::~AgentInterface()	{
}

//=======================================================================

void AgentInterface::slotUserClicked(bool abIsProfileVisible)	{
	int x = m_pToolButtonUser->x() + m_pToolButtonUser->width() - m_pFrameSettings->width();
	int y = m_pToolButtonUser->y() + m_pToolButtonUser->height();

	m_pFrameSettings->setGeometry(x,y,m_pFrameSettings->width(),m_pFrameSettings->height());

	m_pFrameSettings->setVisible(abIsProfileVisible);

	if (abIsProfileVisible)	{
		connect(m_pPushButtonSignOut,SIGNAL(clicked()),this,SLOT(slotSignOut()));
		connect(m_pPushButtonRemoveAccount,SIGNAL(clicked()),this,SLOT(slotRemoveAccount()));
		connect(m_pPushButtonChangeSettings,SIGNAL(clicked()),this,SLOT(slotChangeSettings()));
	} else {
		disconnect(m_pPushButtonSignOut,SIGNAL(clicked()),this,SLOT(slotSignOut()));
		disconnect(m_pPushButtonRemoveAccount,SIGNAL(clicked()),this,SLOT(slotRemoveAccount()));
		disconnect(m_pPushButtonChangeSettings,SIGNAL(clicked()),this,SLOT(slotChangeSettings()));
	}
}

//----------------------------------------------------------------------

void AgentInterface::slotSignUp()	{
	m_pAgentMgr->signUpRequest();
}

//----------------------------------------------------------------------

void AgentInterface::slotSignIn()	{
	string strUserName = m_pLineEditUserName->text().toStdString();
	string strPsw = m_pLineEditPassword->text().toStdString();

	if (strPsw.empty() || strUserName.empty())	{	//User doesn't seem to have an account yet
		m_pLineEditUserName->clear();
		m_pLineEditPassword->clear();

		slotSignUp();
	} else {	//Check validity of user's data
		m_pAgentMgr->signInRequest(strUserName,strPsw);
	}
}

//----------------------------------------------------------------------

void AgentInterface::slotSignOut()	{
	m_pAgentMgr->signOutRequest(m_pAbstractUser->getUserIDName());

	m_pFrameSettings->close();
	m_pToolButtonUser->setVisible(false);

	m_pPushButtonSignIn->show();
	m_pLineEditPassword->show();
	m_pLineEditUserName->show();
}

//----------------------------------------------------------------------

void AgentInterface::slotRemoveAccount()	{
	std::cout << "remove account" << std::endl;

	m_pFrameSettings->close();
}

//----------------------------------------------------------------------

void AgentInterface::slotChangeSettings()	{
	m_pFrameSettings->close();

	m_pAgentMgr->modifyAccountRequest();
}

//----------------------------------------------------------------------

void AgentInterface::slotSignedIn()	{
	m_pPushButtonSignIn->close();
	m_pLineEditPassword->close();
	m_pLineEditUserName->close();

	m_pToolButtonUser->setVisible(true);

	m_pLineEditPassword->clear();
	m_pLineEditUserName->clear();
}