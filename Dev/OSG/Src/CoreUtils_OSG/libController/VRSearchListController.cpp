#include "VRAbstractObject.h"
#include "VRScene.h"

#include "VRPickAndDragHandlerShopEditor.h"

#include "VRSearchListController.h"

using namespace VR;
using namespace osg;

//--------------------------------------------------------------------------------------

SearchListController::SearchListController(
QString & astrSelectedItemName,
PickAndDragHandlerShopEditor * a_pPickAndDragHandlerShopEditor,
ref_ptr<Scene> a_pScene)	{

	m_strSelectedItemName = astrSelectedItemName;
	mpPickAndDragHandlerShopEditor = dynamic_cast<PickAndDragHandlerShopEditor*>(a_pPickAndDragHandlerShopEditor);
	mp_Scene = a_pScene;
}

//======================================================================================

void SearchListController::updateSearchListGUI() {

	AbstractObject * pAbstractObject = dynamic_cast<AbstractObject*>(
		mp_Scene->getChild(m_strSelectedItemName.toStdString()));

	if (pAbstractObject==0)
		return;

	mpPickAndDragHandlerShopEditor->m_pPickedObject = pAbstractObject;
	emit mpPickAndDragHandlerShopEditor->signalPropertiesSettingsChanged();
}

//--------------------------------------------------------------------------------------

