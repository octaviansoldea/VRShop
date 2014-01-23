#include "VRUserAccount.h"

#include <string>

#include "VRSignUp_GUI.h"

using namespace Ui;
using namespace VR;
using namespace std;

//----------------------------------------------------------------------

SignUp_GUI::SignUp_GUI() {
	setupUi(this);

	connect(m_pToolButtonClose, SIGNAL(clicked()), this, SLOT(close()));
	connect(m_pPushButtonCancel, SIGNAL(clicked()), this, SLOT(close()));
	connect(m_pPushButtonSubmit, SIGNAL(clicked()), this, SLOT(slotSignUpUser()));
}

//----------------------------------------------------------------------

void SignUp_GUI::slotSignUpUser()	{
	string strUserName = m_pLineEditFirstName->text().toStdString();
	string strPassword = m_pLineEditPassword->text().toStdString();

	UserAccount userAccount(strUserName,strPassword);

	userAccount.addUserAccount();
}