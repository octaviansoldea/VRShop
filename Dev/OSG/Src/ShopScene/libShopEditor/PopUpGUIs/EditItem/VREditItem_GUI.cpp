#include <osgDB/ReadFile>
#include "VRKeyboardMouseManipulatorShopEditor.h"

#include "VREditItem_GUI.h"

using namespace Ui;
using namespace VR;
using namespace osg;

//----------------------------------------------------------------------

//EditItem_GUI::EditItem_GUI()	{
//	setupUi(this);
//
//	connect(m_pToolButtonCancel, SIGNAL(clicked()), this, SLOT(close()));
//	connect(m_pPushButtonCancel, SIGNAL(clicked()), this, SLOT(close()));
////	connect(m_pToolButtonTexture, SIGNAL(pressed()), m_pLabelTexture, SLOT());
//
//	connect(m_pPushButtonApply, SIGNAL(clicked()), this, SLOT(slotApplyEditItem()));
//
//	m_pOSGQT_Widget->show();
//}

//----------------------------------------------------------------------

EditItem_GUI::EditItem_GUI(AbstractObject * apAbstractObject)	{
	setupUi(this);
	
	m_pAbstractObject = apAbstractObject;

	m_pOSGQT_Widget->setSceneData(m_pAbstractObject);
	m_pOSGQT_Widget->setCameraManipulator(new KeyboardMouseManipulatorShopEditor);

	connect(m_pToolButtonCancel, SIGNAL(clicked()), this, SLOT(close()));
	connect(m_pPushButtonCancel, SIGNAL(clicked()), this, SLOT(close()));
//	connect(m_pToolButtonTexture, SIGNAL(pressed()), m_pLabelTexture, SLOT());

	connect(m_pPushButtonApply, SIGNAL(clicked()), this, SLOT(slotApplyEditItem()));

	m_pOSGQT_Widget->show();
}

//----------------------------------------------------------------------

void EditItem_GUI::slotApplyEditItem()	{
	delete m_pAbstractObject;
	delete m_pOSGQT_Widget;
}

//----------------------------------------------------------------------

void EditItem_GUI::slotInsertImage()	{
}
