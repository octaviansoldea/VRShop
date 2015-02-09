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
	string strDBFileName = AppData::getFPathDatabases() + "ShopDemo.db";

	m_pWidget = new ShoppingPlace_GUI(m_pClient, strDBFileName,strClientName);
	m_pWidget->setParent(m_pWidgetCentralContent);

	m_pWidget->setStyleSheet("m_pWidget#QWidget {content: 2px; border-width: 1px; \
							 border-style: solid; border-radius: 5px;}");

	QRect qrectCentralContent = m_pWidgetCentralContent->geometry();
	m_pWidget->setGeometry(2,2,qrectCentralContent.width()-4,qrectCentralContent.height()-4);
	
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

//----------------------------------------------------------------------

void EmbeddedWidget::resize()	{
	if (m_pWidget == 0)	{
		return;
	}
	m_pWidget->setStyleSheet("m_pWidget#QWidget {content: 2px; border-width: 1px; \
							 border-style: solid; border-radius: 5px;}");
	QRect qrectCentralContent = m_pWidgetCentralContent->geometry();
	m_pWidget->setGeometry(2,2,qrectCentralContent.width()-4,qrectCentralContent.height()-4);
}