#include <string>
#include <iostream>

#include "VRScene.h"
#include "VRShoppingPlace.h"
#include "VRSignUp_GUI.h"

#include "VRKeyboardMouseManipulatorShopClient.h"

#include "VRShoppingPlace_GUI.h"

using namespace osg;
using namespace Ui;
using namespace VR;
using namespace std;

//----------------------------------------------------------------------

ShoppingPlace_GUI::ShoppingPlace_GUI()	{	
	setupUi(this);
	setWindowTitle("Shop Client");

	m_pShoppingPlace = new ShoppingPlace(m_pOSGQTWidget);
	KeyboardMouseManipulatorShopClient * pCameraManipulator = 
		dynamic_cast<KeyboardMouseManipulatorShopClient *>(m_pOSGQTWidget->getCameraManipulator());

	Scene * pScene = m_pShoppingPlace->getScene();

	QGridLayout * pLayoutMap = dynamic_cast<QGridLayout *>(m_pOSGQTWidgetMap->layout());
	pLayoutMap->setMargin(1);

	m_pOSGQTWidgetMap->setCameraManipulator(pCameraManipulator);
	m_pOSGQTWidgetMap->setSceneData(pScene);
	m_pOSGQTWidgetMap->show();

	m_pOSGQTWidget->show();

	buildConnections();

}

//-----------------------------------------------------------------------------------------

ShoppingPlace_GUI::~ShoppingPlace_GUI()	{
	delete m_pShoppingPlace;
}

//=========================================================================================

void ShoppingPlace_GUI::buildConnections() {
	connect(m_pPushButtonSignIn,SIGNAL(clicked()),this,SLOT(slotSignUp()));
	connect(m_pToolButtonMyBasket,SIGNAL(toggled(bool)),m_pFrameItemsBasket,SLOT(setVisible(bool)));
	connect(m_pToolButtonMyBasket,SIGNAL(toggled(bool)),m_pLabelBasketCase,SLOT(setVisible(bool)));
}

//-----------------------------------------------------------------------------------------

void ShoppingPlace_GUI::updateGeometry()	{
	int x = centralWidget()->x();
	int y = centralWidget()->y();

	int width = centralWidget()->width();
	int height = centralWidget()->height();

//	m_pToolButtonMyBasket->setGeometry((x+width)/2,y+5,m_pToolButtonMyBasket->width(),m_pToolButtonMyBasket->height());

	m_pOSGQTWidgetMap->setGeometry(x+width-m_pOSGQTWidgetMap->width()-10,y+10,m_pOSGQTWidgetMap->width(),m_pOSGQTWidgetMap->height());

	m_pFrameItemsBasket->setGeometry((x+width-m_pFrameItemsBasket->width())/2,(y+height-m_pFrameItemsBasket->height()),m_pFrameItemsBasket->width(), m_pFrameItemsBasket->height());
	m_pLabelBasketCase->setGeometry(m_pFrameItemsBasket->x()+(m_pFrameItemsBasket->width()-m_pLabelBasketCase->width())/2,(m_pFrameItemsBasket->y()-20),m_pLabelBasketCase->width(), m_pLabelBasketCase->height());

	m_pLabelLegalNotice->setGeometry(5,(y+height-m_pLabelLegalNotice->height()),m_pLabelLegalNotice->width(), m_pLabelLegalNotice->height());
}

//=========================================================================================

void ShoppingPlace_GUI::slotSignUp()	{
	SignUp_GUI signUp;
		
	//To get a widget without a "TitleBar"
	signUp.setWindowFlags(Qt::FramelessWindowHint);
	bool bRes = signUp.exec();

	if (bRes = QDialog::Accepted)	{

	}
}

//-----------------------------------------------------------------------------------------

void ShoppingPlace_GUI::slotSignIn()	{
	string strUserName = m_pLineEditUserName->text().toStdString();
	string strPassword = m_pLineEditPassword->text().toStdString();

}

//-----------------------------------------------------------------------------------------

void ShoppingPlace_GUI::resizeEvent(QResizeEvent *event)	{
	QWidget::resizeEvent(event);

	updateGeometry();
}