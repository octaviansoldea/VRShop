#include <iostream>
#include <fstream>

#include "VRQLabel.h"
#include <string>
#include "VRAppData.h"

#include "VRClient.h"

#include "VRShoppingPlace_GUI.h"
//#include "VRShopBuilder_GUI.h"

#include "VREmbeddedWidget.h"

#include "VREmbeddedWidget_GUI.h"

using namespace Ui;
using namespace std;
using namespace VR;

EmbeddedWidget_GUI::EmbeddedWidget_GUI(Client * apClient, string & astrPipeName, QObject * apParent)	{
	setupUi(this);

	m_pClient = apClient;
	string strPipeName = "\\\\.\\pipe\\VRShopPluginPipe";
	m_pPipe = new PipeClient(strPipeName);

	connect(m_pLabelHome,SIGNAL(hovered(bool)),this,SLOT(slotLinkHovered(bool)));
	connect(m_pLabelAbout,SIGNAL(hovered(bool)),this,SLOT(slotLinkHovered(bool)));
	connect(m_pLabelSelectShop,SIGNAL(hovered(bool)),this,SLOT(slotLinkHovered(bool)));
	connect(m_pLabelForDevs,SIGNAL(hovered(bool)),this,SLOT(slotLinkHovered(bool)));
	connect(m_pLabelContact,SIGNAL(hovered(bool)),this,SLOT(slotLinkHovered(bool)));

	connect(m_pLabelLogo,SIGNAL(clicked()),this,SLOT(slotHomeButtonClicked()));
	connect(m_pLabelHome,SIGNAL(clicked()),this,SLOT(slotHomeButtonClicked()));
	connect(m_pLabelSelectShop,SIGNAL(clicked()),this,SLOT(slotSelectShopClicked()));
	connect(m_pLabelAbout,SIGNAL(clicked()),this,SLOT(slotAboutClicked()));
	connect(m_pLabelForDevs,SIGNAL(clicked()),this,SLOT(slotForDevsClicked()));
	connect(m_pLabelContact,SIGNAL(clicked()),this,SLOT(slotContactClicked()));

	connect(m_pComboBoxShops,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(slotCurrentIndexChanged(const QString &)));
	
	m_pEmbeddedWidget = new EmbeddedWidget(m_pWidgetCentralContent, m_pClient);
}

//----------------------------------------------------------------------

EmbeddedWidget_GUI::~EmbeddedWidget_GUI()	{
	ofstream out;
	string strLog = AppData::getFPathLog() + "errors.txt";
	out.open(strLog,ios::app);
	out << "Destructor EmbeddedWidget" << endl;
	out.close();

	delete m_pPipe;
	delete m_pEmbeddedWidget;
}

//=========================================================================================

void EmbeddedWidget_GUI::checkIfParentExists()	{
	bool bRes = m_pPipe->isPipeAccessible();

	//If true, parent alive, else terminated
	if (bRes == false)	{
		qApp->quit();
	}
}

//----------------------------------------------------------------------

void EmbeddedWidget_GUI::slotLinkHovered(bool abHovered)	{
	VRQLabel * pEmitter = static_cast<VRQLabel *>(sender());

	if (abHovered == true)	{
		pEmitter->setStyleSheet("color:#acd5d4; \
			display: inline; \
			text-decoration: none; \
			font-size:15px; \
			font-family:FuturaBook;"
		);
	} else {
		pEmitter->setStyleSheet("color:white; \
			display: inline; \
			text-decoration: none; \
			font-size:15px; \
			font-family:FuturaBook;"
		);
	}
}

//----------------------------------------------------------------------

void EmbeddedWidget_GUI::slotHomeButtonClicked()	{
	m_pEmbeddedWidget->home();
}

//----------------------------------------------------------------------

void EmbeddedWidget_GUI::slotSelectShopClicked()	{
	slotCurrentIndexChanged("DemoShop");
}

//----------------------------------------------------------------------

void EmbeddedWidget_GUI::slotAboutClicked()	{
	m_pEmbeddedWidget->about();
}

//----------------------------------------------------------------------

void EmbeddedWidget_GUI::slotForDevsClicked()	{
	m_pEmbeddedWidget->forDevelopers();
}

//----------------------------------------------------------------------

void EmbeddedWidget_GUI::slotContactClicked()	{
	m_pEmbeddedWidget->contact();
}

//----------------------------------------------------------------------

void EmbeddedWidget_GUI::slotCurrentIndexChanged(const QString & aqstrShopName)	{
	m_pEmbeddedWidget->selectShop(aqstrShopName);
}

//----------------------------------------------------------------------