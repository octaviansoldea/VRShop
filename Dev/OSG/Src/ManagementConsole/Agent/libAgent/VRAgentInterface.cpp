#include <string>

#include <QFrame>
#include <QToolButton>
#include <QLineEdit>
#include <QPushButton>

#include "VRSignUp_GUI.h"

#include "VRAgentInterface.h"

using namespace VR;
using namespace std;

//----------------------------------------------------------------------

AgentInterface::AgentInterface(
QFrame * apFrameSettings,
QToolButton * apToolButtonUser,
QLineEdit * apLineEditPassword,
QLineEdit * apLineEditUserName,
QPushButton * apPushButtonSignIn)	{
	m_pFrameSettings = apFrameSettings;
	m_pToolButtonUser = apToolButtonUser;
	m_pLineEditPassword = apLineEditPassword;
	m_pLineEditUserName = apLineEditUserName;
	m_pPushButtonSignIn = apPushButtonSignIn;

	m_pToolButtonUser->setVisible(false);
	m_pFrameSettings->setVisible(false);

	connect(m_pToolButtonUser,SIGNAL(toggled(bool)),this,SLOT(slotUserClicked(bool)));
	connect(m_pPushButtonSignIn,SIGNAL(clicked()),this,SLOT(slotSignUp()));
	connect(m_pLineEditPassword,SIGNAL(returnPressed()),this,SLOT(slotSignUp()));
}

//----------------------------------------------------------------------

AgentInterface::~AgentInterface()	{

}

//=======================================================================

void AgentInterface::slotUserClicked(bool abIndicator)	{
	int x = m_pToolButtonUser->x() + m_pToolButtonUser->width() - m_pFrameSettings->width();
	int y = m_pToolButtonUser->y() + m_pToolButtonUser->height();

	m_pFrameSettings->setGeometry(x,y,m_pFrameSettings->width(),m_pFrameSettings->height());

	m_pFrameSettings->setVisible(abIndicator);
}

//----------------------------------------------------------------------

void AgentInterface::slotSignUp()	{
	string & strUserName = m_pLineEditUserName->text().toStdString();
	string & strPsw = m_pLineEditPassword->text().toStdString();

	bool bRes = true;
	if (strPsw.empty() || strUserName.empty())	{
		SignUp_GUI signUp;
		
		//To get a widget without a "TitleBar"
		signUp.setWindowFlags(Qt::FramelessWindowHint);
		bool bRes = signUp.exec();

		if (bRes = QDialog::Accepted)	{

		}

		//instantiate SIGN UP class
	} else {
		//First check DB of accounts
	}

	if (bRes)	{
		m_pToolButtonUser->setVisible(true);
	}
}