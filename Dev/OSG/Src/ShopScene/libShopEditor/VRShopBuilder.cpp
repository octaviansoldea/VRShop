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

#include "VRDatabaseManagerShopEditor.h"

#include "VRShopBuilder.h"

using namespace osg;
using namespace VR;
using namespace std;


//----------------------------------------------------------------------

ShopBuilder::ShopBuilder() :
m_strDBFileName("")	{
}

//----------------------------------------------------------------------

ShopBuilder::ShopBuilder(OSGQT_Widget * apOSGQTWidget) :
m_pOSGQTWidget(apOSGQTWidget),
m_strDBFileName("../../../Databases/Untitled.db")	{

	newDB(m_strDBFileName);

	m_pScene = new Scene();
	addScene(m_pScene);	//Adds the Scene into the vector of scenes
	string & strScene = m_pScene->SQLFieldValues();
	m_pdbMgr->insertScene(strScene);

	m_pEventHandler = new PickAndDragHandlerShopEditor;

	m_pOSGQTWidget->setSceneData(m_pScene);
	m_pOSGQTWidget->setCameraManipulator(new KeyboardMouseManipulatorShopEditor);
	m_pOSGQTWidget->addEventHandler(m_pEventHandler);

	ref_ptr<Node> pAxes = osgDB::readNodeFile("../../../Resources/Models3D/axes.osgt");
	ref_ptr<Grid> pGrid = new Grid;
	m_pScene->addChild(pAxes);
	m_pScene->addChild(pGrid);
}

//----------------------------------------------------------------------

ShopBuilder::~ShopBuilder() {
	if (m_pdbMgr)
		delete m_pdbMgr;
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
	//Calling this function creates new file
	m_strDBFileName = astrDBFileName;

	DatabaseManagerShopEditorParams dbMgrParams;
	dbMgrParams.m_qstrDBName = m_strDBFileName.c_str();

	m_pdbMgr = new DatabaseManagerShopEditor(dbMgrParams);
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

ref_ptr<Scene> ShopBuilder::getScene() const	{
	return m_pScene;
}

//----------------------------------------------------------------------

void ShopBuilder::addNewItem(const string & astrObjectName)	{
	ref_ptr < AbstractObject > pAbstractObject = 
		dynamic_cast<AbstractObject*>(AbstractObject::createInstance(astrObjectName).get());
	pAbstractObject->predefinedObject();

	m_pScene->addChild(pAbstractObject);

	string strSceneName = m_pScene->getName();
	//Call DB here
	vector<string> vecstrData;
	pAbstractObject->preparedObjectData(vecstrData,strSceneName);

	m_pdbMgr->insertObject(strSceneName,vecstrData);
}

//-----------------------------------------------------------------------

ref_ptr<Scene> ShopBuilder::getScene(const string & astrSceneName)	{
	if (astrSceneName.empty())	{
		return 0;
	}
	int nI;
	Scene * pScene = 0;
	for (nI=0; nI < m_pvecScenes.size(); nI++)	{
		pScene = m_pvecScenes[nI];
		if (pScene->getName() == astrSceneName)	{
			return m_pvecScenes[nI];
		}
	}
	return 0;
}

//-----------------------------------------------------------------------

const string ShopBuilder::getSceneName(Scene * apScene)	{
	return apScene->getName();
}

//-----------------------------------------------------------------------

const string ShopBuilder::getSceneName(unsigned int i)	{
	return (i<m_pvecScenes.size()) ? m_pvecScenes[i]->getName() : "";
}

//-----------------------------------------------------------------------

void ShopBuilder::addScene(Scene * apScene)	{
	m_pvecScenes.push_back(apScene);
}

//-----------------------------------------------------------------------

void ShopBuilder::removeScene(Scene * apScene)	{
	Scene * pScene = apScene;
	m_pvecScenes.erase(remove(m_pvecScenes.begin(), m_pvecScenes.end(), pScene),
		m_pvecScenes.end());
}