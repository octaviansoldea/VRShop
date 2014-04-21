#include "VRAbstractObject.h"
#include "VRProduct.h"
#include "VRProductController.h"

#include "VRKeyboardMouseManipulatorShopEditor.h"

#include "BasicStringDefinitions.h"

#include "VRRemoveProduct_GUI.h"

using namespace osg;
using namespace Ui;
using namespace VR;

//----------------------------------------------------------------------

RemoveProduct_GUI::RemoveProduct_GUI() {
	setupUi(this);

	buildConnections();
}

//----------------------------------------------------------------------

RemoveProduct_GUI::RemoveProduct_GUI(Product * apProduct) :
m_pProduct(apProduct)	{
	setupUi(this);

	buildConnections();

	m_pOSGQT_Widget->setSceneData(m_pProduct->getRepresentation());
	m_pOSGQT_Widget->setCameraManipulator(new KeyboardMouseManipulatorShopEditor);
	m_pOSGQT_Widget->show();

	ProductParams pParams;
	m_pProduct->getParams(pParams);
	m_pComboBoxCategory->insertItem(0,pParams.m_strProductCategory.c_str());
	m_pComboBoxProduct->insertItem(0,pParams.m_strProductName.c_str());
	m_pComboBoxID->insertItem(0,tostr(pParams.m_nProductCode).c_str());
}

//----------------------------------------------------------------------

RemoveProduct_GUI::~RemoveProduct_GUI()	{
	if (m_pOSGQT_Widget)
		delete m_pOSGQT_Widget;
}

//======================================================================

void RemoveProduct_GUI::buildConnections()	{
	connect(m_pPushButtonCancel, SIGNAL(clicked(bool)),this,SLOT(close()));
	connect(m_pToolButtonCancel, SIGNAL(clicked(bool)),this,SLOT(close()));

	connect(m_pPushButtonRemove, SIGNAL(clicked(bool)),this,SLOT(accept()));
}

//----------------------------------------------------------------------

void RemoveProduct_GUI::accept()	{
	QDialog::accept();
}

//----------------------------------------------------------------------

void RemoveProduct_GUI::close()	{
	QDialog::close();
}
