#include <string>
#include "BasicStringDefinitions.h"

#include <QString>
#include <QVariant>
#include <QVBoxLayout>
#include <QMessageBox>

#include <osgDB/ReadFile>
#include <QFileDialog>
#include "VRReadAndSaveFileCallback.h"

#include "VRNewProject_GUI.h"

#include "VROSGQT_Widget.h"
#include "VRGrid.h"
#include "VRScene.h"
#include "VRProductManager.h"

#include "VRAbstractGeomShape.h"

#include "VRLighting.h"

#include "VRSaveAs_GUI.h"

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
	m_strDBFileName("")	{
		m_pScene = new Scene();
		addScene(m_pScene);	//Adds the Scene into the vector of scenes

		//Reuse of textures => memory optimization taken from "OSG Cookbook"
		osgDB::Registry::instance()->setReadFileCallback(new VR::ReadAndSaveFileCallback);
		osgDB::Registry::instance()->getOrCreateSharedStateManager();
		osgDB::SharedStateManager* ssm = osgDB::Registry::instance()->getSharedStateManager();
		if(ssm) {
			ssm->share(m_pScene.get());
		}

		//These are necessary parts of any file
		ref_ptr<Node> pAxes = osgDB::readNodeFile("../../../Resources/Models3D/axes.osgt");
		ref_ptr<Grid> pGrid = new Grid;
		m_pScene->addChild(pAxes);
		m_pScene->addChild(pGrid);

		//A pointer to products sent to the scene
		m_pProductMgr = new ProductManager;
		Node * pProductsRepresentation = m_pProductMgr->getProductsRepresentation();
		m_pScene->addChild(pProductsRepresentation);

		m_pEventHandler = new PickAndDragHandlerShopEditor;

		m_pOSGQTWidget->setSceneData(m_pScene);
		m_pOSGQTWidget->setCameraManipulator(new KeyboardMouseManipulatorShopEditor);
		m_pOSGQTWidget->addEventHandler(m_pEventHandler);

		//Insert lighting
		//ref_ptr<Light> pLight = new osg::Light();
		//pLight->setPosition(osg::Vec4(1,-10, 5, 1));
		//pLight->setAmbient(osg::Vec4(0.2, 0.2, 0.2, 1.0));
		//pLight->setDiffuse(osg::Vec4(0.7, 0.4, 0.6, 1.0));
		//pLight->setSpecular(osg::Vec4(1.0, 1.0, 1.0, 1.0));

		//ref_ptr<LightSource> pLightSource = new LightSource();
		//pLightSource->setLight(pLight);
		//pLightSource->setLocalStateSetModes(StateAttribute::ON);

		//StateSet * pLightStateSet = m_pScene->getOrCreateStateSet();
		//pLightSource->setStateSetModes(*pLightStateSet, StateAttribute::ON);
		//pLightStateSet->setMode(GL_LIGHTING,StateAttribute::OVERRIDE | StateAttribute::INHERIT); 

		//m_pScene->addChild(pLightSource);
}

//----------------------------------------------------------------------

ShopBuilder::~ShopBuilder() {
	delete m_pProductMgr;
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

void ShopBuilder::newDB()	{
	//Before creating new file, check if any still opened.
	if (getCurrentFileName().c_str())	{
		QMessageBox msgBox;
		string strText = "Changes to the current file will be lost if not saved. \n\nDo you want to save them?";
		msgBox.setText(strText.c_str());
		msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::No);
		msgBox.setWindowTitle("Warning window");
		int nRes = msgBox.exec();

		if (nRes == QMessageBox::Ok)	{
			saveDB(m_strDBFileName.c_str());
		}
	}

	m_pScene->clearScene();

	NewProject_GUI newProject;
	//To get a widget without a "TitleBar"
	newProject.setWindowFlags(Qt::FramelessWindowHint);
	newProject.exec();

	//Result == 1 indicates that path+name are valid
	if (newProject.result() == 1)	{
		string & strFileName = 
			(newProject.m_pLineEditDirectory->text() + "/" + newProject.m_pLineEditFileName->text()).toStdString();
		strFileName += (isAtEndOfString(strFileName, ".db")) ? "" : ".db";
		replace(strFileName.begin(), strFileName.end(), '/', '\\');

		QDir dir(strFileName.c_str());
		if(dir.exists(strFileName.c_str()))	{
			QMessageBox msgBox;
			string strText = "File " + strFileName + " already exists. \n Press OK to overwrite it, else press NO.";
			msgBox.setText(strText.c_str());
			msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::No);
			msgBox.setWindowTitle("Warning window");
			int nRes = msgBox.exec();

			if (nRes == QMessageBox::No)	{
				newProject.show();
			} else {
				dir.remove(strFileName.c_str());
				m_strDBFileName = strFileName;
			}
		}
		m_strDBFileName = strFileName;
		QFile file;
		file.setFileName(m_strDBFileName.c_str());
		file.open(QIODevice::ReadWrite | QIODevice::Text);
		file.close();
	}	//End "if (newProject.result())"

	DatabaseManagerShopEditorParams dbMgrParams;
	dbMgrParams.m_qstrDBName = m_strDBFileName.c_str();
	DatabaseManagerShopEditor dbMgr(dbMgrParams);

	//These are necessary parts of any file
	ref_ptr<Node> pAxes = osgDB::readNodeFile("../../../Resources/Models3D/axes.osgt");
	ref_ptr<Grid> pGrid = new Grid;
	m_pScene->addChild(pAxes);
	m_pScene->addChild(pGrid);


	//A pointer to products sent to the scene
	Node * pProductsRepresentation = m_pProductMgr->getProductsRepresentation();
	m_pScene->addChild(pProductsRepresentation);
}

//----------------------------------------------------------------------

void ShopBuilder::readDB()	{
}

//----------------------------------------------------------------------

void ShopBuilder::readDB(const string & astrDBFileName)	{
	m_strDBFileName = astrDBFileName;

	//Before creating new file, check if any still opened.
	if (getCurrentFileName().c_str() == "" || m_pScene->getNumChildren() > 3)	{
		QMessageBox msgBox;
		string strText = "Changes to the current file will be lost if not saved. \n\nDo you want to save them?";
		msgBox.setText(strText.c_str());
		msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::No);
		msgBox.setWindowTitle("Warning window");
		int nRes = msgBox.exec();

		if (nRes == QMessageBox::Ok)	{
			saveDB();
		}
	}

	m_pScene->clearScene();


	m_strDBFileName = astrDBFileName;

	DatabaseManagerShopEditorParams dbMgrParams;
	dbMgrParams.m_qstrDBName = m_strDBFileName.c_str();
	DatabaseManagerShopEditor dbMgr(dbMgrParams);

	//Get list of objects in the scene
	list<string> lststrSceneObjects = dbMgr.getListOfObjects("Untitled");

	ref_ptr<AbstractObject> pAO = 0;

	list<string>::iterator it = lststrSceneObjects.begin();
	for (it; it != lststrSceneObjects.end(); it++)	{
		//Find class and object names
		const int & nFindPos1 = it->find_first_of(";");
		const int & nFindPos2 = it->find_first_of(";", nFindPos1+1);
		string strClassName = it->substr(nFindPos1+1,nFindPos2-nFindPos1-1);

		if (strClassName == "ProductDisplay")	{
			vector<string> vecstrObjectData = dbMgr.getObjectData(*it);
			m_pProductMgr->initFromSQLData(vecstrObjectData);

			continue;
		}

		pAO = AbstractObject::createInstance(strClassName);
		vector<string> vecstrObjectData = dbMgr.getObjectData(*it);

		pAO->initFromSQLData(vecstrObjectData);

		m_pScene->addChild(pAO);
	}

	ref_ptr<Node> pAxes = osgDB::readNodeFile("../../../Resources/Models3D/axes.osgt");
	ref_ptr<Grid> pGrid = new Grid;
	if(!m_pProductMgr)
		m_pProductMgr = new ProductManager;

	m_pScene->addChild(pAxes);
	m_pScene->addChild(pGrid);

	Node * pProductsRepresentation = m_pProductMgr->getProductsRepresentation();
	m_pScene->addChild(pProductsRepresentation);
}

//----------------------------------------------------------------------

void ShopBuilder::closeDB(const std::string & astrDBFileName)	{
	//Before creating new file, check if any still opened.
	if (getCurrentFileName().c_str())	{
		QMessageBox msgBox;
		string strText = "Changes to the current file will be lost if not saved. \n\nDo you want to save them?";
		msgBox.setText(strText.c_str());
		msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::No);
		msgBox.setWindowTitle("Warning window");
		int nRes = msgBox.exec();

		if (nRes == QMessageBox::Ok)	{
			saveDB(m_strDBFileName.c_str());
		}
		m_pScene->clearScene();
		m_strDBFileName = "";
	}
}

//----------------------------------------------------------------------

void ShopBuilder::saveDB()	{
	const string & strCurrentFile = getCurrentFileName();

	if (strCurrentFile == "")	{
		saveAsDB();
	} else {
		saveDB(strCurrentFile);
	}
}

//----------------------------------------------------------------------

void ShopBuilder::saveDB(const string & astrDBFileName)	{
	m_strDBFileName = astrDBFileName;

	AbstractObject * pAO = 0;
	string strSceneName = m_pScene->getName();
	int nSize = m_pScene->getNumChildren();

	DatabaseManagerShopEditorParams dbMgrParams;
	dbMgrParams.m_qstrDBName = m_strDBFileName.c_str();
	DatabaseManagerShopEditor dbMgr(dbMgrParams);

	//Insert scene into the DB
	dbMgr.insertScene(strSceneName);

	int nI;
	for (nI=0; nI<nSize; nI++)	{
		pAO = dynamic_cast<AbstractObject*>(m_pScene->getChild(nI));

		if (pAO == 0 || pAO->className() == "Grid")
			continue;

		//Call DB here
		vector<string> vecstrData;
		vecstrData.push_back(strSceneName);
		pAO->preparedObjectData(vecstrData,strSceneName);

		dbMgr.insertObject(strSceneName,vecstrData);
	}
	//Here add products into the DB
	vector<string> vecstrData;
	vecstrData.push_back(strSceneName);
	m_pProductMgr->preparedObjectData(vecstrData,strSceneName);

	dbMgr.insertObject(strSceneName,vecstrData);
}

//----------------------------------------------------------------------

void ShopBuilder::saveAsDB()	{
	SaveAs_GUI saveAs;
	int nRes = saveAs.exec();

	if (nRes == 1)	{
		string strFileName = 
			(saveAs.m_pLineEditDirectory->text() + "/" + saveAs.m_pLineEditFileName->text()).toStdString();
		strFileName += (isAtEndOfString(strFileName, ".db")) ? "" : ".db";
		replace(strFileName.begin(), strFileName.end(), '/', '\\');

		//Create file
		QFile file;
		file.setFileName(strFileName.c_str());
		file.open(QIODevice::ReadWrite | QIODevice::Text);
		file.close();

		//Create necessary DB tables
		DatabaseManagerShopEditorParams dbMgrParams;
		dbMgrParams.m_qstrDBName = strFileName.c_str();
		DatabaseManagerShopEditor dbMgr(dbMgrParams);

		saveDB(strFileName);
	}
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

ProductManager * ShopBuilder::getProducts()	{
	return m_pProductMgr;
}

//----------------------------------------------------------------------

std::string ShopBuilder::getCurrentFileName() const	{
	return m_strDBFileName;
}

//----------------------------------------------------------------------

void ShopBuilder::addNewItem(const string & astrObjectName)	{
	ref_ptr < AbstractObject > pAbstractObject = 
		dynamic_cast<AbstractObject*>(AbstractObject::createInstance(astrObjectName).get());
	pAbstractObject->predefinedObject();
	addNewItem(pAbstractObject);
}

//-----------------------------------------------------------------------

void ShopBuilder::addNewItem(ref_ptr<VR::AbstractObject> apAbstractObject)	{
	if (apAbstractObject == 0)
		return;

	m_pScene->addChild(apAbstractObject);
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
