#include <iostream>

#include <string>
#include <ctime>

#include "BasicStringDefinitions.h"

#include "VRAppData.h"

#include "VRClient.h"

#include "VRShoppingPlace_GUI.h"

#include "VREmbeddedWidget.h"

using namespace std;
using namespace VR;

EmbeddedWidget::EmbeddedWidget(QWidget * apWidgetCentralContent, Client * apClient)	{
	m_pWidgetCentralContent = apWidgetCentralContent;
	m_pWidget = 0;

	m_pClient = apClient;
}

//----------------------------------------------------------------------

EmbeddedWidget::~EmbeddedWidget()	{
	if (m_pWidget != 0)	{
		delete m_pWidget;
		m_pWidget = 0;
	}
}

//=========================================================================================

void EmbeddedWidget::home()	{
	if (m_pWidget != 0)	{
		delete m_pWidget;
		m_pWidget = 0;
	}
}

//----------------------------------------------------------------------

void EmbeddedWidget::selectShop(const QString & aqstrShopName)	{
	if (m_pWidget != 0)	{
		delete m_pWidget;
		m_pWidget = 0;
	}

	string strClientName = tostr(m_pClient->getUserID());
	string strDBFileName = AppData::get_FPath_Databases() + "ShopDemo.db";

	QRect qrectCentralContent = m_pWidgetCentralContent->geometry();

	m_pWidget = new ShoppingPlace_GUI(m_pClient, strDBFileName,strClientName);
	m_pWidget->setParent(m_pWidgetCentralContent);
	m_pWidget->setStyleSheet("position: absolute; width: 100%; padding: 1px;");
	m_pWidget->setGeometry(0,0,qrectCentralContent.width(),qrectCentralContent.height());
	
	m_pWidget->show();
}

//----------------------------------------------------------------------

void EmbeddedWidget::about()	{
}

//----------------------------------------------------------------------

void EmbeddedWidget::forDevelopers()	{
}

//----------------------------------------------------------------------

void EmbeddedWidget::contact()	{
}
