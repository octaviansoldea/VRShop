#include "VRKeyboardMouseManipulatorShopEditor.h"

#include "VRRemoveProduct_GUI.h"

using namespace osg;
using namespace Ui;
using namespace VR;

//----------------------------------------------------------------------

RemoveProduct_GUI::RemoveProduct_GUI() {
	setupUi(this);

	m_pOSGQT_Widget->setCameraManipulator(new KeyboardMouseManipulatorShopEditor);

	connect(m_pPushButtonCancel, SIGNAL(clicked(bool)),this,SLOT(close()));
	connect(m_pToolButtonCancel, SIGNAL(clicked(bool)),this,SLOT(close()));

	connect(m_pPushButtonRemove, SIGNAL(clicked(bool)),this,SLOT(accept()));
}

//======================================================================
