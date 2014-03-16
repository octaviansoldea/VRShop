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
#include "VRDataStructureModel.h"


#include "VRShopBuilder.h"

using namespace osg;
using namespace VR;
using namespace std;


//----------------------------------------------------------------------

ShopBuilder::ShopBuilder()	{	
}

//----------------------------------------------------------------------

ShopBuilder::ShopBuilder(OSGQT_Widget * apOSGQTWidget, QTreeView * apQTreeView) :
m_pOSGQTWidget(apOSGQTWidget),
m_pQTreeView(apQTreeView),
m_pDataStructureModel(0)	{
	m_pScene = new Scene;

	m_pEventHandler = new PickAndDragHandlerShopEditor;

	m_pOSGQTWidget->setSceneData(m_pScene);
	m_pOSGQTWidget->setCameraManipulator(new KeyboardMouseManipulatorShopEditor);
	m_pOSGQTWidget->addEventHandler(m_pEventHandler);

	ref_ptr<Node> pAxes = osgDB::readNodeFile("../../../Resources/Models3D/axes.osgt");
	ref_ptr<Grid> pGrid = new Grid;
	m_pScene->addChild(pAxes);
	m_pScene->addChild(pGrid);

	m_pScene->setSceneHierarchy();
}

//----------------------------------------------------------------------

ShopBuilder::~ShopBuilder() {
	delete m_pQTreeView;

	if (m_pDataStructureModel)
		delete m_pDataStructureModel;
}

//----------------------------------------------------------------------

void ShopBuilder::gridOnOff(bool abIndicator) {
	//ToolButton checked && Grid not already a child
	if (abIndicator) {
		ref_ptr<Grid> pGrid = new Grid;
		m_pScene->addChild(pGrid);
	} else {
		int nI;
		for (nI=0; nI < m_pScene->getNumChildren(); nI++)	{
			string strChild = m_pScene->getChild(nI)->className();
			if (strChild == "Grid")	{
				m_pScene->removeChild(m_pScene->getChild(nI));
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

bool ShopBuilder::searchScene(const string & astrSearchTerm, DataStructureModel ** appDataStructureModel)	{
	bool bRes = false;
	const string & strSearchTerm = astrSearchTerm;

	SceneObjectsSearchShopEditor * pSceneObjectsSearchShopEditor = 
		new SceneObjectsSearchShopEditor(strSearchTerm.c_str(), m_pScene);
	
	if (!pSceneObjectsSearchShopEditor->getModel())	{
		delete pSceneObjectsSearchShopEditor;
		return bRes;
	}

	*appDataStructureModel = dynamic_cast<DataStructureModel*>( pSceneObjectsSearchShopEditor->getModel());

	bRes = true;
	return bRes;
}

//----------------------------------------------------------------------

bool ShopBuilder::setTreeStructure()	{
	bool bRes = false;

	unsigned int nSize = m_pScene->getSceneHierarchy().size();
	if (nSize == 0)
		return bRes;

	DataStructureModelParams params;
	QList<QString> data;
	int nI;
	for (nI=0; nI<nSize; nI++)	{
		data.push_back(m_pScene->getSceneHierarchy()[nI].c_str());
	}
	params.data = data;
//	params.aqvarRootHeader = "Scene";

	m_pDataStructureModel = new DataStructureModel(params);

	m_pQTreeView->setModel(m_pDataStructureModel);
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

	m_pScene->addChild(pAbstractObject);
	setTreeStructure();
}

//----------------------------------------------------------------------
