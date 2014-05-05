#include <string>
#include "BasicStringDefinitions.h"

#include <QString>
#include <QVariant>
#include <QVBoxLayout>
#include <QMessageBox>

#include <osgDB/ReadFile>
#include <QFileDialog>
#include "VRNewProject_GUI.h"

#include "OSGQT_Widget.h"
#include "VRGrid.h"
#include "VRScene.h"
#include "VRProductManager.h"

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
m_strDBFileName("../../../Databases/SysTemp.db")	{
}

//----------------------------------------------------------------------

ShopBuilder::ShopBuilder(OSGQT_Widget * apOSGQTWidget) :
m_pOSGQTWidget(apOSGQTWidget),
m_strDBFileName("../../../Databases/SysTemp.db")	{

	m_pScene = new Scene();

	//These are necessary parts of any file
	ref_ptr<Node> pAxes = osgDB::readNodeFile("../../../Resources/Models3D/axes.osgt");
	ref_ptr<Grid> pGrid = new Grid;
	m_pScene->addChild(pAxes);
	m_pScene->addChild(pGrid);

	//A pointer to products sent to the scene
	m_pProductMgr = new ProductManager;
	m_pScene->addChild(m_pProductMgr);

	addScene(m_pScene);	//Adds the Scene into the vector of scenes
	string & strScene = m_pScene->SQLFieldValues();
//	m_pdbMgr->insertScene(strScene);

	m_pEventHandler = new PickAndDragHandlerShopEditor;

	m_pOSGQTWidget->setSceneData(m_pScene);
	m_pOSGQTWidget->setCameraManipulator(new KeyboardMouseManipulatorShopEditor);
	m_pOSGQTWidget->addEventHandler(m_pEventHandler);
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
//				newProject.close();
				newProject.show();
			} else {
				dir.remove(strFileName.c_str());
				m_strDBFileName = strFileName;
			}
		}
	}	//End "if (newProject.result())"
	DatabaseManagerShopEditorParams dbMgrParams;
	dbMgrParams.m_qstrDBName = m_strDBFileName.c_str();

	m_pdbMgr = new DatabaseManagerShopEditor(dbMgrParams);

	//These are necessary parts of any file
	ref_ptr<Node> pAxes = osgDB::readNodeFile("../../../Resources/Models3D/axes.osgt");
	ref_ptr<Grid> pGrid = new Grid;
	m_pScene->addChild(pAxes);
	m_pScene->addChild(pGrid);

	//A pointer to products sent to the scene
	m_pProductMgr = new ProductManager;
	m_pScene->addChild(m_pProductMgr);
}

//----------------------------------------------------------------------

void ShopBuilder::readDB(const string & astrDBFileName)	{
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


	m_strDBFileName = astrDBFileName;


	ref_ptr<Node> pAxes = osgDB::readNodeFile("../../../Resources/Models3D/axes.osgt");
	ref_ptr<Grid> pGrid = new Grid;
	if(!m_pProductMgr)
		m_pProductMgr = new ProductManager;

	m_pScene->addChild(pAxes);
	m_pScene->addChild(pGrid);
	m_pScene->addChild(m_pProductMgr);
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
	if (strCurrentFile == "../../../Databases/SysTemp.db")	{
		saveAsDB();
	} else {
		//Implement save method;
	}
}

void ShopBuilder::saveDB(const string & astrDBFileName)	{
}


void ShopBuilder::saveAsDB()	{
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

ref_ptr<ProductManager> ShopBuilder::getProducts() const	{
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

	string strSceneName = m_pScene->getName();
	//Call DB here
	vector<string> vecstrData;
	apAbstractObject->preparedObjectData(vecstrData,strSceneName);

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