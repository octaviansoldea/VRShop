#include <string>

#include "VRSignUp_GUI.h"

#include "VRShoppingPlace_GUI.h"

using namespace osg;
using namespace Ui;
using namespace VR;
using namespace std;

//----------------------------------------------------------------------

ShoppingPlace_GUI::ShoppingPlace_GUI()	{	
	setupUi(this);

	setWindowTitle("Shopping Place");
	
	m_ShoppingPlace.init(m_pOSGQTWidget);

	m_pOSGQTWidget->show();

	buildConnections();
}


//=========================================================================================

void ShoppingPlace_GUI::buildConnections() {
	connect(m_pPushButtonSignUp,SIGNAL(clicked()),this,SLOT(slotSignUp()));
	connect(m_pPushButtonSignIn,SIGNAL(clicked()),this,SLOT(slotSignIn()));
}

//=========================================================================================

void ShoppingPlace_GUI::slotSignUp()	{
	SignUp_GUI signUp;
		
	//To get a widget without a "TitleBar"
	signUp.setWindowFlags(Qt::FramelessWindowHint);
	signUp.exec();
}

//-----------------------------------------------------------------------------------------

void ShoppingPlace_GUI::slotSignIn()	{
	string strUserName = m_pLineEditUserName->text().toStdString();
	string strPassword = m_pLineEditPassword->text().toStdString();

}