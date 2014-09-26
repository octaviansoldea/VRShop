#include <string>
#include <iostream>

#include <QFrame>
#include <QToolButton>
#include <QLineEdit>
#include <QPushButton>

#include "VRSignUp_GUI.h"
#include "VRAbstractUser.h"

#include "VRAgentManager.h"

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
AbstractUser * apAbstractUser)	{
	m_pFrameSettings = apFrameSettings;
	m_pToolButtonUser = apToolButtonUser;
	m_pLineEditPassword = apLineEditPassword;
	m_pLineEditUserName = apLineEditUserName;
	m_pPushButtonSignIn = apPushButtonSignIn;
	m_pPushButtonSignOut = apPushButtonSignOut;
	m_pPushButtonRemoveAccount = apPushButtonRemoveAccount;
	m_pPushButtonChangeSettings = apPushButtonChangeSettings;
	m_pAbstractUser = apAbstractUser;

	m_pToolButtonUser->setVisible(false);
	m_pFrameSettings->setVisible(false);

	connect(m_pToolButtonUser,SIGNAL(toggled(bool)),this,SLOT(slotUserClicked(bool)));
	connect(m_pPushButtonSignIn,SIGNAL(clicked()),this,SLOT(slotSignIn()));
	connect(m_pLineEditPassword,SIGNAL(returnPressed()),this,SLOT(slotSignIn()));
	connect(m_pLineEditUserName,SIGNAL(returnPressed()),this,SLOT(slotSignIn()));
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

void AgentInterface::slotSignIn()	{
	string strUserName = m_pLineEditUserName->text().toStdString();
	string strPsw = m_pLineEditPassword->text().toStdString();

	bool bRes = true;
	if (strPsw.empty() || strUserName.empty())	{	//User doesn't seem to have an account yet
		SignUp_GUI signUp;
		
		signUp.setWindowFlags(Qt::FramelessWindowHint);
		bRes = signUp.exec();
		if (bRes == QDialog::Accepted)	{

			string strUserName = signUp.m_pLineEditEMail->text().toStdString();
			string strPsw = signUp.m_pLineEditPassword->text().toStdString();

			AgentManager agentMgr;
			agentMgr.trySigningIn(strUserName, strPsw);

			//try signing him up
		}
	} else {	//Check validity of user's data
		if (!bRes)	{
			//user's data doesn't match the DB
			m_pLineEditUserName->clear();
			m_pLineEditPassword->clear();
		}
	}

	if (bRes)	{	// User signed-in
		m_pToolButtonUser->setVisible(true);
		m_pPushButtonSignIn->close();
		m_pLineEditPassword->close();
		m_pLineEditUserName->close();
	}
}

//----------------------------------------------------------------------

void AgentInterface::slotSignOut()	{
	std::cout << "sign-out" << std::endl;
}

//----------------------------------------------------------------------

void AgentInterface::slotRemoveAccount()	{
	std::cout << "remove account" << std::endl;
}

//----------------------------------------------------------------------

void AgentInterface::slotChangeSettings()	{
	std::cout << "change settings" << std::endl;
}
