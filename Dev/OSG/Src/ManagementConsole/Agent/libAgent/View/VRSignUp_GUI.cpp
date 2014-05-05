#include "VRSignUp_GUI.h"

using namespace Ui;
using namespace VR;

//----------------------------------------------------------------------

SignUp_GUI::SignUp_GUI() {
	setupUi(this);

	connect(m_pToolButtonClose, SIGNAL(clicked()), this, SLOT(close()));
	connect(m_pPushButtonCancel, SIGNAL(clicked()), this, SLOT(close()));
	connect(m_pPushButtonSubmit, SIGNAL(clicked()), this, SLOT(accept()));
}

//----------------------------------------------------------------------

void SignUp_GUI::accept()	{
	//Check if all required cells are filled
	if (m_pLineEditFirstName->text().isEmpty()	||
		m_pLineEditLastName->text().isEmpty()	||
		m_pLineEditEMail->text().isEmpty()		||
		m_pLineEditPassword->text().isEmpty()	||
		m_pLineEditRetypePassword->text().isEmpty())	{
			return;
	}

	if (m_pLineEditPassword->text() != m_pLineEditRetypePassword->text())	{
		return;
	}

	QDialog::accept();
}