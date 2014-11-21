#include "VRAbstractObject.h"
#include "VRScene.h"

#include <QTreeView>
#include "VRPickAndDragHandlerShopEditor.h"

#include "VRSceneHierarchyController.h"

using namespace VR;
using namespace osg;
using namespace std;

//--------------------------------------------------------------------------------------

SceneHierarchyController::SceneHierarchyController(
QTreeView * a_pQTreeView,
PickAndDragHandlerShopEditor * a_pPickAndDragHandlerShopEditor,
Scene * a_pScene)	{

	m_pQTreeView = a_pQTreeView;
	mpPickAndDragHandlerShopEditor = a_pPickAndDragHandlerShopEditor;
	m_pScene = a_pScene;

	connect(m_pQTreeView,SIGNAL(clicked(const QModelIndex &)), this, SLOT(slotItemClicked(const QModelIndex &)));
}

//======================================================================================

void SceneHierarchyController::updateSceneHierarchyGUI() {
}

//--------------------------------------------------------------------------------------

void SceneHierarchyController::slotItemClicked(const QModelIndex & anItemIndex)	{
	const string strSelectedItem = anItemIndex.data().toString().toStdString();

	ref_ptr<AbstractObject> pAbstractObject = dynamic_cast<AbstractObject*>(m_pScene->getChild(strSelectedItem));

	if (pAbstractObject==0)
		return;

	mpPickAndDragHandlerShopEditor->m_pPickedObject = pAbstractObject;
	emit mpPickAndDragHandlerShopEditor->signalPropertiesSettingsChanged();
}

//--------------------------------------------------------------------------------------

void SceneHierarchyController::slotItemDeleted(const QModelIndex & anItemIndex)	{
	string strItemName = anItemIndex.data().toString().toStdString();

	ref_ptr<AbstractObject> pAbstractObject = dynamic_cast<AbstractObject*>(m_pScene->getChild(strItemName));

	if (pAbstractObject==0)
		return;

	mpPickAndDragHandlerShopEditor->m_pPickedObject = pAbstractObject;

}