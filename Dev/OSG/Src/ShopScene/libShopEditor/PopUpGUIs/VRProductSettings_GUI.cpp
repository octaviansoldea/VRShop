#include "VRProductController.h"

#include "VRProductSettings_GUI.h"

using namespace osg;
using namespace Ui;
using namespace VR;

//----------------------------------------------------------------------

ProductSettings_GUI::ProductSettings_GUI() {
	setupUi(this);

	m_pProductController = new ProductController();
}

ProductSettings_GUI::~ProductSettings_GUI()	{
	delete m_pProductController;
}

//=====================================================================

void ProductSettings_GUI::buildConnections() {
	connect(m_pPushButtonSave, SIGNAL(pressed()), this, SLOT(slotSaveProductChanges()));
}

//----------------------------------------------------------------------

void ProductSettings_GUI::slotSaveProductChanges()	{
}

//----------------------------------------------------------------------

void ProductSettings_GUI::slotInsertProduct()	{
}

//----------------------------------------------------------------------

void ProductSettings_GUI::slotModifyProduct()	{
}

//----------------------------------------------------------------------

void ProductSettings_GUI::slotRemoveProduct()	{
}
