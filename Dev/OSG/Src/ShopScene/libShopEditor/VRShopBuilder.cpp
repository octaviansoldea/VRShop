#include <string>

#include <QString>
#include <QVariant>
#include <QVBoxLayout>

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

ShopBuilder::ShopBuilder(OSGQT_Widget * apOSGQTWidget, QTreeView * apQTreeView)	{
	m_pScene = new Scene;
	m_pOSGQTWidget = apOSGQTWidget;
	m_pQTreeView = apQTreeView;

	m_pEventHandler = new PickAndDragHandlerShopEditor;

	m_pOSGQTWidget->setSceneData(m_pScene);
	m_pOSGQTWidget->setCameraManipulator(new KeyboardMouseManipulatorShopEditor);
	m_pOSGQTWidget->addEventHandler(m_pEventHandler);

	ref_ptr<Node> pAxes = osgDB::readNodeFile("../../../Resources/Models3D/axes.osgt");
	ref_ptr<Grid> pGrid = new Grid;
	m_pScene->addElement(pAxes);
	m_pScene->addElement(pGrid);

	setTreeStructure();
}

//----------------------------------------------------------------------

ShopBuilder::~ShopBuilder() {
	if (m_pSceneStructureModel)
		delete m_pSceneStructureModel;
}

//----------------------------------------------------------------------

void ShopBuilder::gridOnOff(bool abIndicator) {
	//ToolButton checked && Grid not already a child
	if (abIndicator) {
		ref_ptr<Grid> pGrid = new Grid;
		m_pScene->addElement(pGrid);
	} else {
		int nI;
		for (nI=0; nI < m_pScene->getNumChildren(); nI++)	{
			string strChild = m_pScene->getChild(nI)->className();
			if (strChild == "Grid")	{
				m_pScene->removeElement(m_pScene->getChild(nI));
				return;
			}
		}
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
		new SceneObjectsSearchShopEditor(strSearchTerm.c_str(), m_pScene);
	
	if (!pSceneObjectsSearchShopEditor->getModel())	{
		delete pSceneObjectsSearchShopEditor;
		return bRes;
	}

	*appSceneStructureModel = dynamic_cast<SceneStructureModel*>( pSceneObjectsSearchShopEditor->getModel());

	bRes = true;
	return bRes;
}

//----------------------------------------------------------------------

bool ShopBuilder::setTreeStructure()	{
	bool bRes = false;

	unsigned int nSize = m_pScene->getSceneHierarchy().size();
	if (nSize == 0)
		return bRes;

	SceneStructureModelParams params;
	QList<QString> d;
	int nI;
	for (nI=0; nI<nSize; nI++)	{
		d.push_back(m_pScene->getSceneHierarchy()[nI].c_str());
	}
	params.data = d;
	params.aqvarRootHeader = "Scene";
	m_pSceneStructureModel = new SceneStructureModel(params);

	m_pQTreeView->setModel(m_pSceneStructureModel);
	m_pQTreeView->show();

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

	setTreeStructure();
}

//----------------------------------------------------------------------
