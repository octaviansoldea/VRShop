#include <string>

#include <QString>
#include <QVariant>
#include <QVBoxLayout>

#include <QLineEdit>
#include <QWidget>
#include <QListView>
#include <QToolButton>


#include <osgDB/ReadFile>

#include "OSGQT_Widget.h"
#include "VRGrid.h"
#include "VRScene.h"

#include "VRPickAndDragHandlerShopEditor.h"
#include "VRKeyboardMouseManipulatorShopEditor.h"
#include "VRSceneObjectsSearchShopEditor.h"
#include "VRSceneStructureModel.h"


#include "VRShopBuilder.h"

using namespace osg;
using namespace VR;
using namespace std;


//----------------------------------------------------------------------

ShopBuilder::ShopBuilder()	{	
}

//----------------------------------------------------------------------

ShopBuilder::ShopBuilder(OSGQT_Widget * apOSGQTWidget)	{
	m_pScene = new Scene;
	m_pOSGQTWidget = apOSGQTWidget;

	m_pEventHandler = new PickAndDragHandlerShopEditor;

	m_pOSGQTWidget->setSceneData(m_pScene);
	m_pOSGQTWidget->setCameraManipulator(new VR::KeyboardMouseManipulatorShopEditor);
	m_pOSGQTWidget->addEventHandler(m_pEventHandler);

	ref_ptr<Node> pAxes = osgDB::readNodeFile("../../../Resources/Models3D/axes.osgt");
	m_pGridlines = new Grid;
	m_pScene->addElement(pAxes);
	m_pScene->addElement(m_pGridlines);
}

//----------------------------------------------------------------------

ShopBuilder::~ShopBuilder() {	
}

//----------------------------------------------------------------------

void ShopBuilder::gridOnOff(bool abIndicator) {
	//ToolButton checked && Grid not already a child
	if (abIndicator) {
		m_pGridlines = new Grid;
		m_pScene->addElement(m_pGridlines);
	} else {
		m_pScene->removeElement(m_pGridlines);
	}
}

//----------------------------------------------------------------------

void ShopBuilder::newDB(const string & astrDBFileName)	{
}

//----------------------------------------------------------------------

void ShopBuilder::readDB(const string & astrDBFileName)	{
}

//----------------------------------------------------------------------

void ShopBuilder::saveDB(const string & astrDBFileName)	{
}

//----------------------------------------------------------------------

bool ShopBuilder::searchScene(const string & astrSearchTerm, SceneStructureModel ** appSceneStructureModel)	{
	bool bRes = false;
	const string & strSearchTerm = astrSearchTerm;

	SceneObjectsSearchShopEditor * pSceneObjectsSearchShopEditor = 
		new SceneObjectsSearchShopEditor(strSearchTerm, m_pScene);
	
	if (!pSceneObjectsSearchShopEditor->getModel())	{
		delete pSceneObjectsSearchShopEditor;
		return bRes;
	}

	*appSceneStructureModel = dynamic_cast<SceneStructureModel*>( pSceneObjectsSearchShopEditor->getModel());

	bRes = true;
	return bRes;
}

//----------------------------------------------------------------------

ref_ptr<Scene> ShopBuilder::getScene() const	{
	return m_pScene;
}

//----------------------------------------------------------------------

void ShopBuilder::addNewItem(const string & astrObjectName)	{
	ref_ptr < AbstractObject > pAbstractObject = dynamic_cast<AbstractObject*>(AbstractObject::createInstance(astrObjectName).get());
	pAbstractObject->predefinedObject();

	m_pScene->addElement(pAbstractObject.get());
}

//----------------------------------------------------------------------

void ShopBuilder::updateQTreeView()	{
}

//==========================================================================

