#include "VRKeyboardMouseManipulatorShopEditor.h"

#include "VRAddProduct_GUI.h"

using namespace Ui;
using namespace VR;
using namespace osg;

//----------------------------------------------------------------------

AddProduct_GUI::AddProduct_GUI()	{
	setupUi(this);
	
	m_pScrollAreaNewProduct->setVisible(false);

	connect(m_pToolButtonClose, SIGNAL(pressed()),this,SLOT(close()));
	connect(m_pPushButtonCancel, SIGNAL(pressed()),this,SLOT(close()));
	connect(m_pPushButtonOK, SIGNAL(pressed()),this,SLOT(accept()));

	m_pToolButtonFromDB->setChecked(true);
	m_pToolButtonNew->setChecked(false);

	connect(m_pToolButtonFromDB, SIGNAL(pressed()),this,SLOT(slotSetActiveWidget()));
	connect(m_pToolButtonNew,SIGNAL(pressed()),this,SLOT(slotSetActiveWidget()));

	ref_ptr<KeyboardMouseManipulatorShopEditor> pCamera = new KeyboardMouseManipulatorShopEditor;
	m_pOSGQT_Widget->setCameraManipulator(pCamera);
}

//----------------------------------------------------------------------

void AddProduct_GUI::slotSetActiveWidget()	{
	QToolButton * pToolButton = dynamic_cast<QToolButton*>(sender());
	if(pToolButton == 0) {
		return;
	}

	if(pToolButton->isChecked()) {
		pToolButton->setChecked(true);
		return;
	}

	if(pToolButton == m_pToolButtonNew)	{
		m_pToolButtonFromDB->setChecked(false);

		m_pFrameFromDB->setVisible(false);
		m_pScrollAreaNewProduct->setVisible(false);
		m_pScrollAreaNewProduct->setVisible(true);
	} else if (pToolButton == m_pToolButtonFromDB)	{
		m_pToolButtonNew->setChecked(false);

		m_pScrollAreaNewProduct->setVisible(false);
		m_pFrameFromDB->setVisible(false);
		m_pFrameFromDB->setVisible(true);
	} else {
		return;
	}
}
