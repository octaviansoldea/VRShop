#include <osgDB/ReadFile>

#include <string>
#include "BasicStringDefinitions.h"
#include "FileOperations.h"
#include "VRShopBuilderCommands.h"
#include "VRBasicQTOperations.h"

#include <QString>
#include <QVariant>
#include <QVBoxLayout>
#include <QMessageBox>

#include <QFileDialog>
#include "VRReadAndSaveFileCallback.h"

#include "VRNewProject_GUI.h"

#include "VROSGQT_Widget.h"
#include "VRGrid.h"
#include "VRScene.h"
#include "VRProductManager.h"

#include "VRAbstractGeomShape.h"

#include "VRSaveAs_GUI.h"

#include "VRPickAndDragHandlerShopEditor.h"
#include "VRKeyboardMouseManipulatorShopEditor.h"
#include "VRSceneObjectsSearchShopEditor.h"
#include "VRDataStructureModel.h"

#include "VRDatabaseInterfaceShopEditor.h"

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
		ssm->share(m_pScene);
	}

	//These are necessary parts of any file
	osg::ref_ptr<osg::Node> pAxes = osgDB::readNodeFile("../../../Resources/Models3D/axes.osgt");
	osg::ref_ptr<Grid> pGrid = new Grid;
	m_pScene->addChild(pAxes);
	m_pScene->addChild(pGrid);

	//A pointer to products sent to the scene
	m_pProductMgr = new ProductManager;
	osg::Node * pProductsRepresentation = m_pProductMgr->getProductsRepresentation();
	m_pScene->addChild(pProductsRepresentation);

	m_pPickAndDragHandlerShopEditor = new PickAndDragHandlerShopEditor;
	m_pKeyboardMouseManipulatorShopEditor = new KeyboardMouseManipulatorShopEditor();

	m_pOSGQTWidget->setSceneData(m_pScene);
	m_pOSGQTWidget->setCameraManipulator(m_pKeyboardMouseManipulatorShopEditor);
	m_pOSGQTWidget->addEventHandler(m_pPickAndDragHandlerShopEditor);
}

//----------------------------------------------------------------------

ShopBuilder::~ShopBuilder() {
	delete m_pProductMgr;

	//vector<Scene*>::iterator it = m_pvecScenes.begin();
	//for(it; it != m_pvecScenes.end(); ++it)	{
	//	Scene * pScene = (Scene*)(*it);
	//	delete pScene;
	//	pScene = 0;
	//}
}

//----------------------------------------------------------------------

void ShopBuilder::gridOnOff(bool abIndicator) {
	//ToolButton checked && Grid not already a child
	Grid * pGrid = (Grid *)m_pScene->getChild("Grid");

	if (pGrid == 0)	{
		return;
	}

	if (abIndicator) {
		pGrid->setNodeMask(0xFFFFFFFF);	// Visible
	} else {
		pGrid->setNodeMask(0x0);         // Hidden
	}
}

//----------------------------------------------------------------------

void ShopBuilder::newDB()	{
	//Before creating new file, check if any still opened.
	if (getCurrentFileName().c_str())	{
		QMessageBox msgBox;
		int nRes = BasicQtOperations::getMsgBox(VR::BasicQtOperations::OPEN_NEW_FILE, msgBox);

		if (nRes == QMessageBox::Ok)	{
			saveDB(m_strDBFileName.c_str());
		}
	}

	NewProject_GUI newProject;
	//To get a widget without a "TitleBar"
	newProject.setWindowFlags(Qt::FramelessWindowHint);
	newProject.exec();

	//Result == 1 indicates that path+name are valid
	if (newProject.result() == 1)	{
		std::string & strFileName = 
			adjustFileData(
				newProject.m_pLineEditDirectory->text().toStdString(),
				newProject.m_pLineEditFileName->text().toStdString()
			);

		QDir dir(strFileName.c_str());
		if(dir.exists(strFileName.c_str()))	{
			QMessageBox msgBox;
			int nRes = BasicQtOperations::getMsgBox(BasicQtOperations::FILE_ALREADY_EXISTS, msgBox);

			if (nRes == QMessageBox::No)	{
				newProject.show();
			}
		}

		m_strDBFileName = strFileName;
		bool bRes = BasicQtOperations::QtFileOperation(strFileName, BasicQtOperations::FILE_OPEN);
	}	//End "if (newProject.result())"

	m_pScene->clearScene();

	DatabaseInterfaceShopEditorParams dbInterfaceParams;
	dbInterfaceParams.m_qstrDBName = m_strDBFileName.c_str();
	DatabaseInterfaceShopEditor dbMgr(dbInterfaceParams);

	//These are necessary parts of any file
	osg::ref_ptr<osg::Node> pAxes = osgDB::readNodeFile("../../../Resources/Models3D/axes.osgt");
	osg::ref_ptr<Grid> pGrid = new Grid;
	m_pScene->addChild(pAxes);
	m_pScene->addChild(pGrid);

	
	//A pointer to products sent to the scene
	osg::Node * pProductsRepresentation = m_pProductMgr->getProductsRepresentation();
	m_pScene->addChild(pProductsRepresentation);
}

//----------------------------------------------------------------------

void ShopBuilder::readDB(const std::string & astrDBFileName)	{
	m_strDBFileName = astrDBFileName;

	//Before creating new file, check if any still opened.
	if (getCurrentFileName().c_str() == "" || m_pScene->getNumChildren() > 3)	{
		QMessageBox msgBox;
		int nRes = BasicQtOperations::getMsgBox(BasicQtOperations::OPEN_NEW_FILE,msgBox);

		if (nRes == QMessageBox::Ok)	{
			saveDB();
		}
	}

	m_pScene->clearScene();


	m_strDBFileName = astrDBFileName;

	DatabaseInterfaceShopEditorParams dbParams;
	dbParams.m_qstrDBName = m_strDBFileName.c_str();
	DatabaseInterfaceShopEditor dbMgr(dbParams);

	//Get list of objects in the scene
	std::list<std::string> lststrSceneObjects = dbMgr.getListOfObjects("Untitled");

	osg::ref_ptr<AbstractObject> pAO = 0;

	std::list<std::string>::iterator it = lststrSceneObjects.begin();
	for (it; it != lststrSceneObjects.end(); it++)	{
		//Find class and object names
		const int & nFindPos1 = it->find_first_of(";");
		const int & nFindPos2 = it->find_first_of(";", nFindPos1+1);
		std::string strClassName = it->substr(nFindPos1+1,nFindPos2-nFindPos1-1);

		if (strClassName == ShopBuilderCommands::getOperationType(VR::ShopBuilderCommands::PRODUCT_DISPLAY))	{
			std::vector<std::string> vecstrObjectData = dbMgr.getObjectData(*it);
			m_pProductMgr->initFromSQLData(vecstrObjectData);
			
			continue;
		}

		pAO = AbstractObject::createInstance(strClassName);
		std::vector<std::string> vecstrObjectData = dbMgr.getObjectData(*it);

		pAO->initFromSQLData(vecstrObjectData);

		m_pScene->addChild(pAO);
	}

	
	osg::ref_ptr<osg::Node> pAxes = osgDB::readNodeFile("../../../Resources/Models3D/axes.osgt");
	osg::ref_ptr<Grid> pGrid = new Grid;
	if(!m_pProductMgr)
		m_pProductMgr = new ProductManager;

	m_pScene->addChild(pAxes);
	m_pScene->addChild(pGrid);

	osg::Node * pProductsRepresentation = m_pProductMgr->getProductsRepresentation();
	m_pScene->addChild(pProductsRepresentation);
}

//----------------------------------------------------------------------

void ShopBuilder::closeDB(const std::string & astrDBFileName)	{
	//Before creating new file, check if any still opened.
	if (getCurrentFileName().c_str())	{
		QMessageBox msgBox;
		int nRes = BasicQtOperations::getMsgBox(BasicQtOperations::OPEN_NEW_FILE,msgBox);

		if (nRes == QMessageBox::Ok)	{
			saveDB(m_strDBFileName.c_str());
		}
		m_pScene->clearScene();
		m_strDBFileName = "";
	}
}

//----------------------------------------------------------------------

void ShopBuilder::saveDB()	{
	const std::string & strCurrentFile = getCurrentFileName();

	if (strCurrentFile == "")	{
		saveAsDB();
	} else {
		saveDB(strCurrentFile);
	}
}

//----------------------------------------------------------------------

void ShopBuilder::saveDB(const std::string & astrDBFileName)	{
	m_strDBFileName = astrDBFileName;

	//This will open, clear and close the file
	bool bRes = BasicQtOperations::QtFileOperation(m_strDBFileName, BasicQtOperations::FILE_OPEN_TRUNCATE);

	AbstractObject * pAO = 0;
	std::string strSceneName = m_pScene->getName();
	int nSize = m_pScene->getNumChildren();

	DatabaseInterfaceShopEditorParams dbParams;
	dbParams.m_qstrDBName = m_strDBFileName.c_str();
	DatabaseInterfaceShopEditor dbInterface(dbParams);

	//Insert scene into the DB
	dbInterface.insertScene(strSceneName);

	int nI;
	for (nI=0; nI<nSize; nI++)	{
		pAO = dynamic_cast<AbstractObject*>(m_pScene->getChild(nI));

		if (pAO == 0 || pAO->className() == ShopBuilderCommands::getOperationType(ShopBuilderCommands::GRID))
			continue;

		//Call DB here
		std::vector<std::string> vecstrData;
		vecstrData.push_back(strSceneName);
		pAO->preparedObjectData(vecstrData,strSceneName);

		dbInterface.insertObject(strSceneName,vecstrData);
	}


	//Here add products into the scene DB
	std::vector<std::string> vecstrData;
	vecstrData.push_back(strSceneName);
	m_pProductMgr->preparedObjectData(vecstrData,strSceneName);	
	dbInterface.insertObject(strSceneName,vecstrData);


	//Add products into the product DB
	std::vector<std::string> vecstrProducts;
	std::string strProductsDB = "../../../Databases/Products.db";
	m_pProductMgr->prepareProductsData(vecstrProducts);

	dbParams.m_qstrDBName = strProductsDB.c_str();
	DatabaseInterfaceShopEditor dbProducts(dbParams);
	dbProducts.insertProduct(vecstrProducts);
}

//----------------------------------------------------------------------

void ShopBuilder::saveAsDB()	{
	SaveAs_GUI saveAs;
	int nRes = saveAs.exec();

	if (nRes == 1)	{
		std::string & strFileName = 
			adjustFileData(
				saveAs.m_pLineEditDirectory->text().toStdString(),
				saveAs.m_pLineEditFileName->text().toStdString()
			);


		//Create file
		bool bRes = BasicQtOperations::QtFileOperation(strFileName, VR::BasicQtOperations::FILE_OPEN);

		//Create necessary DB tables
		DatabaseInterfaceShopEditorParams dbParams;
		dbParams.m_qstrDBName = strFileName.c_str();
		DatabaseInterfaceShopEditor dbMgr(dbParams);

		saveDB(strFileName);
	}
}

//----------------------------------------------------------------------

bool ShopBuilder::searchScene(const std::string & astrSearchTerm, DataStructureModel ** appDataStructureModel)	{
	bool bRes = false;
	const std::string & strSearchTerm = astrSearchTerm;

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

Scene * ShopBuilder::getScene() const	{
	return m_pScene;
}

//----------------------------------------------------------------------

PickAndDragHandlerShopEditor * ShopBuilder::getPicker() const	{
	return m_pPickAndDragHandlerShopEditor;
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

void ShopBuilder::addNewItem(const std::string & astrObjectName)	{
	osg::ref_ptr < AbstractObject > pAbstractObject = 
		dynamic_cast<AbstractObject*>(AbstractObject::createInstance(astrObjectName).get());
	pAbstractObject->predefinedObject();
	addNewItem(pAbstractObject);
}

//-----------------------------------------------------------------------

void ShopBuilder::addNewItem(osg::ref_ptr<VR::AbstractObject> apAbstractObject)	{
	if (apAbstractObject == 0)
		return;

	//Put new item in the center of the viewport and not to (0,0,0)
	osg::Vec3d vec3dEye, vec3dCenter, vec3dUp;

	m_pKeyboardMouseManipulatorShopEditor->getTransformation(vec3dEye, vec3dCenter, vec3dUp);

	apAbstractObject->setPosition(vec3dCenter.x(),vec3dCenter.y(),vec3dCenter.z());
	osg::Matrix & mtrxMatrix = apAbstractObject->calculateMatrix();
	apAbstractObject->setMatrix(mtrxMatrix);

	m_pScene->addChild(apAbstractObject);
}

//-----------------------------------------------------------------------

Scene * ShopBuilder::getScene(const std::string & astrSceneName)	{
	if (astrSceneName.empty())	{
		return 0;
	}

	std::vector<Scene*>::iterator it = m_pvecScenes.begin();
	for (it; it != m_pvecScenes.end(); it++)	{
		if ((*it)->getName() == astrSceneName)	{
			return *it;
		}
	}

	return 0;
}

//-----------------------------------------------------------------------

const std::string ShopBuilder::getSceneName(Scene * apScene)	{
	return apScene->getName();
}

//-----------------------------------------------------------------------

const std::string ShopBuilder::getSceneName(unsigned int i)	{
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