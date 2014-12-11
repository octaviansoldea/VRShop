#include <osgDB/ReadFile>

#include <string>
#include <list>
#include "BasicStringDefinitions.h"
#include "FileOperations.h"
#include "VRShopBuilderCommands.h"
#include "VRBasicQtOperations.h"

#include <QString>
#include <QVariant>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QObject>
#include <QStringListModel>


#include <QComboBox>
#include <QLineEdit>

#include <QFileDialog>
#include "VRReadAndSaveFileCallback.h"

#include "VRNewProject_GUI.h"

#include "VRDuplicateItem_GUI.h"
#include "VRRemoveSelection_GUI.h"
#include "VREditItem_GUI.h"
#include "VRInsertNewItem_GUI.h"


#include "VROSGQT_Widget.h"
#include "VRGrid.h"
#include "VRScene.h"
#include "VRProductManager.h"
#include "VRProductShopEditor.h"

#include "VRAbstractObjectFactory.h"

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
m_strDBFileName(""),
m_pSceneObjectsSearch(0)	{
}

//----------------------------------------------------------------------

ShopBuilder::ShopBuilder(OSGQT_Widget * apOSGQTWidget) :
m_pOSGQTWidget(apOSGQTWidget),
m_strDBFileName(""),
m_pSceneObjectsSearch(0)	{
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
	ref_ptr<osg::Node> pProductsRepresentation = m_pProductMgr->getProductsRepresentation();
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
	if (m_pSceneObjectsSearch != 0)	{
		delete m_pSceneObjectsSearch;
		m_pSceneObjectsSearch = 0;
	}
}

//----------------------------------------------------------------------

void ShopBuilder::gridOnOff(bool abIndicator) {
	//ToolButton checked && Grid not already a child
	ref_ptr<Grid> pGrid = (Grid *)m_pScene->getChild("Grid");

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
		std::string strFileName = 
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
	ref_ptr<osg::Node> pProductsRepresentation = m_pProductMgr->getProductsRepresentation();
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

	std::list<std::string>::iterator it = lststrSceneObjects.begin();
	for (it; it != lststrSceneObjects.end(); it++)	{
		//Find class and object names
		const int nFindPos1 = it->find_first_of(";");
		const int nFindPos2 = it->find_first_of(";", nFindPos1+1);
		std::string strClassName = it->substr(nFindPos1+1,nFindPos2-nFindPos1-1);

		if (strClassName == ShopBuilderCommands::getOperationType(VR::ShopBuilderCommands::PRODUCT_DISPLAY))	{
			std::vector<std::string> vecstrObjectData = dbMgr.getObjectData(*it);
			m_pProductMgr->initFromSQLData(vecstrObjectData);
			
			continue;
		}

		osg::ref_ptr<AbstractObject> pAO = AbstractObjectFactory::createAbstractObject(strClassName);
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

	ref_ptr<osg::Node> pProductsRepresentation = m_pProductMgr->getProductsRepresentation();
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
	const std::string strCurrentFile = getCurrentFileName();

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

	std::string strSceneName = m_pScene->getName();
	int nSize = m_pScene->getNumChildren();

	DatabaseInterfaceShopEditorParams dbParams;
	dbParams.m_qstrDBName = m_strDBFileName.c_str();
	DatabaseInterfaceShopEditor dbInterface(dbParams);

	//Insert scene into the DB
	dbInterface.insertScene(strSceneName);

	int nI;
	for (nI=0; nI<nSize; nI++)	{
		ref_ptr<AbstractObject> pAO = dynamic_cast<AbstractObject*>(m_pScene->getChild(nI));

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
}

//----------------------------------------------------------------------

void ShopBuilder::saveAsDB()	{
	SaveAs_GUI saveAs;
	int nRes = saveAs.exec();

	if (nRes == 1)	{
		std::string strFileName = 
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

bool ShopBuilder::searchScene(const std::string & astrSearchTerm)	{
	bool bRes = false;

	if (m_pSceneObjectsSearch != 0)	{
		delete m_pSceneObjectsSearch;
		m_pSceneObjectsSearch = 0;
	}

	m_pSceneObjectsSearch = new SceneObjectsSearchShopEditor(astrSearchTerm.c_str(), m_pScene);
	
	if (!m_pSceneObjectsSearch->getModel())	{
		delete m_pSceneObjectsSearch;
		m_pSceneObjectsSearch = 0;

		return bRes;
	}

	bRes = true;
	return bRes;
}

//----------------------------------------------------------------------

DataStructureModel * ShopBuilder::getSceneObjectsSearchModel()	{
	return m_pSceneObjectsSearch->getModel();
}

//----------------------------------------------------------------------

ref_ptr<Scene> ShopBuilder::getScene() const	{
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

void ShopBuilder::addNewItem()	{
	InsertNewItem_GUI insertNewItem_GUI;
	insertNewItem_GUI.setWindowFlags(Qt::FramelessWindowHint);
	int nRes = insertNewItem_GUI.exec();

	if (nRes == QDialog::Accepted)	{
		if(!insertNewItem_GUI.m_pListWidgetItem->currentItem())
			return;

		QString qstrSelectedItem = insertNewItem_GUI.m_pListWidgetItem->currentItem()->text();
		
		ref_ptr<AbstractObject> pAbstractObject = AbstractObjectFactory::createAbstractObject(qstrSelectedItem.toStdString());
		pAbstractObject->predefinedObject();

		//Put new item in the center of the viewport and not to (0,0,0)
		const Vec3d vec3dCenter = m_pKeyboardMouseManipulatorShopEditor->getCenter();
		pAbstractObject->setPosition(vec3dCenter.x(),vec3dCenter.y(),vec3dCenter.z());

		Matrix mtrxMatrix = pAbstractObject->calculateMatrix();
		pAbstractObject->setMatrix(mtrxMatrix);

		m_pScene->addChild(pAbstractObject);
	}
}

//-----------------------------------------------------------------------

osg::ref_ptr<Scene> ShopBuilder::getScene(const std::string & astrSceneName)	{
	if (astrSceneName.empty())	{
		return 0;
	}

	std::vector<ref_ptr<Scene>>::iterator it = m_pvecScenes.begin();
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
	ref_ptr<Scene> pScene = apScene;
	m_pvecScenes.push_back(pScene);
}

//-----------------------------------------------------------------------

void ShopBuilder::removeScene(Scene * apScene)	{
	ref_ptr<Scene> pScene = apScene;
	m_pvecScenes.erase(remove(m_pvecScenes.begin(), m_pvecScenes.end(), pScene),
		m_pvecScenes.end());
}

//-----------------------------------------------------------------------

void ShopBuilder::addNewProduct()	{
	m_pProductMgr->addNewProduct();
}

//-----------------------------------------------------------------------

void ShopBuilder::removeProductClicked(const string & astrProductCode)	{
	bool bRes = m_pProductMgr->removeProduct(astrProductCode);

	if (bRes == true)	{
		ref_ptr<AbstractObject> pAO = m_pPickAndDragHandlerShopEditor->m_pPickedObject;
		ProductShopEditor * pProductShopEditor = m_pProductMgr->getProduct(pAO);
		m_pProductMgr->removeProduct(pProductShopEditor);
	}

	m_pPickAndDragHandlerShopEditor->clearList();
}

//-----------------------------------------------------------------------

void ShopBuilder::productClicked(ProductClickedItems & aProductClickedItems)	{
	unsigned long ulProductCode = stol(aProductClickedItems.m_strProductName);
	
	//ProductQuantity,ProductPricePerUnit of the selected product
	vector<string> vecstrProductMgrParams;
	vecstrProductMgrParams.push_back(tostr(ulProductCode));

	list<string> lststrResult = m_pProductMgr->requestData(ProductManager::PRODUCT_QUANTITY_PRICE_REQUEST,vecstrProductMgrParams);

	vector<string> vecstrSplit = splitString(lststrResult.front(),";");

	aProductClickedItems.m_pComboBox_ProductSettings_ProductName->clear();

	aProductClickedItems.m_pComboBox_ProductSettings_ProductName->insertItem(0,aProductClickedItems.m_strProductName.c_str());
	aProductClickedItems.m_pLineEdit_ProductSettings_Quantity->setText(vecstrSplit[0].c_str());
	aProductClickedItems.m_pLineEdit_ProductSettings_Price->setText(vecstrSplit[1].c_str());
}

//-----------------------------------------------------------------------

void ShopBuilder::productMoreSettingsClicked(const string & astrProductCode)	{
	m_pProductMgr->productMoreSettings(astrProductCode);
	m_pPickAndDragHandlerShopEditor->clearList();
}

//-----------------------------------------------------------------------

void ShopBuilder::modifyProductClicked(ProductClickedItems & aProductClickedItems)	{
	string strProductName = aProductClickedItems.m_pComboBox_ProductSettings_ProductName->currentText().toStdString();
	QString qstrNewQuantity = aProductClickedItems.m_pLineEdit_ProductSettings_NewQuantity->text();
	QString qstrNewPrice = aProductClickedItems.m_pLineEdit_ProductSettings_NewPrice->text();

	float flNewQuantity = (qstrNewQuantity.isEmpty())
		? aProductClickedItems.m_pLineEdit_ProductSettings_Quantity->text().toFloat()
		: qstrNewQuantity.toFloat();

	float flNewPrice = (qstrNewPrice.isEmpty())
		? aProductClickedItems.m_pLineEdit_ProductSettings_Price->text().toFloat() 
		: qstrNewPrice.toFloat();

	vector<string> vecstrProductMgrParams;
	vecstrProductMgrParams.push_back(tostr(flNewQuantity));
	vecstrProductMgrParams.push_back(tostr(flNewPrice));
	vecstrProductMgrParams.push_back(strProductName);

	m_pProductMgr->requestData(ProductManager::MODIFY_QUANTITY_PRICE, vecstrProductMgrParams);

	aProductClickedItems.m_pLineEdit_ProductSettings_Price->setText(tostr(flNewPrice).c_str());
	aProductClickedItems.m_pLineEdit_ProductSettings_Quantity->setText(tostr(flNewQuantity).c_str());

	aProductClickedItems.m_pLineEdit_ProductSettings_NewPrice->clear();
	aProductClickedItems.m_pLineEdit_ProductSettings_NewQuantity->clear();
}

//-----------------------------------------------------------------------

void ShopBuilder::groupItems()	{
	vector<ref_ptr<AbstractObject>> & pickedObjects = m_pPickAndDragHandlerShopEditor->getPickedObjects();

	if(pickedObjects.size() < 2)	{
		cout << "Too few items selected for grouping" << endl;
		return;
	}

	vector<ref_ptr<VR::AbstractObject>>::iterator it = pickedObjects.begin();

	ref_ptr<VR::AbstractObject> pGroupedObject = (AbstractObjectFactory::createAbstractObject("CustomFurniture"));
	for (it; it != pickedObjects.end(); it++)	{
		it->get()->setIsTargetPick(false);
		pGroupedObject->addChild(*it);
		m_pScene->removeChild(*it);
	}
	pGroupedObject->setIsTargetPick(true);
	m_pScene->addChild(pGroupedObject.get());

	m_pPickAndDragHandlerShopEditor->clearList();
}

//-----------------------------------------------------------------------

void ShopBuilder::splitItem()	{
	vector<ref_ptr<AbstractObject>> & pickedObjects = m_pPickAndDragHandlerShopEditor->getPickedObjects();

	if (pickedObjects.size() == 0)	{
		cout << "No items selected" << endl;
		return;
	}

	vector<ref_ptr<AbstractObject>>::iterator it = pickedObjects.begin();

	for (it; it != pickedObjects.end(); it++)	{
		Vec3d vec3dPos(it->get()->getPosition());
		Vec3d vec3dRot(it->get()->getRotation());
		Vec3d vec3dLen(it->get()->getScaling());

		m_pScene->removeChild(*it);
		int nI;
		for (nI=0;nI<it->get()->getNumChildren(); nI++)	{
			ref_ptr< AbstractObject > pAbstractObject = dynamic_cast<AbstractObject *>(it->get()->getChild(nI));
			if(pAbstractObject == NULL) {
				continue;
			}

			Vec3d vec3dPosItem(pAbstractObject->getPosition());
			Vec3d vec3dRotItem(pAbstractObject->getRotation());
			Vec3d vec3dLenItem(pAbstractObject->getScaling());

			pAbstractObject->setPosition(vec3dPosItem[0]+vec3dPos[0], vec3dPosItem[1]+vec3dPos[1], vec3dPosItem[2]+vec3dPos[2]);
			pAbstractObject->setRotation(vec3dRotItem[0]+vec3dRot[0], vec3dRotItem[1]+vec3dRot[1], vec3dRotItem[2]+vec3dRot[2]);
			pAbstractObject->setScaling(vec3dLenItem[0]*vec3dLen[0], vec3dLenItem[1]*vec3dLen[1], vec3dLenItem[2]*vec3dLen[2]);

			Matrix mtrxItem = pAbstractObject->calculateMatrix();
			pAbstractObject->setMatrix(mtrxItem);

			pAbstractObject->setIsTargetPick(true);
			m_pScene->addChild(pAbstractObject);
		}
	}
	m_pPickAndDragHandlerShopEditor->clearList();
}

//-----------------------------------------------------------------------

void ShopBuilder::duplicateSelection()	{
	vector<ref_ptr<AbstractObject>> & pickedObjects = m_pPickAndDragHandlerShopEditor->getPickedObjects();

	if(pickedObjects.size() < 1)	{
		cout << "No items selected for removal" << endl;
		return;
	}

	//If selection not empty, open the dialog
	DuplicateItem_GUI itemGUI;

	itemGUI.setWindowFlags(Qt::FramelessWindowHint);
	bool bRes = itemGUI.exec();
	const int nNumberOfCopies = itemGUI.m_pSpinBoxCopies->text().toInt();

	if ((bRes == 0) || (nNumberOfCopies == 0))	{
		m_pPickAndDragHandlerShopEditor->clearList();
		return;
	}

	Vec3d vec3dPos(
		itemGUI.m_pLineEditLocationX->text().toFloat(),
		itemGUI.m_pLineEditLocationY->text().toFloat(),
		itemGUI.m_pLineEditLocationZ->text().toFloat());

	Vec3d vec3dRot(
		itemGUI.m_pLineEditRotationX->text().toFloat(),
		itemGUI.m_pLineEditRotationY->text().toFloat(),
		itemGUI.m_pLineEditRotationZ->text().toFloat());

	Vec3d vec3dLen(
		itemGUI.m_pLineEditScaleX->text().toFloat(),
		itemGUI.m_pLineEditScaleY->text().toFloat(),
		itemGUI.m_pLineEditScaleZ->text().toFloat());

	int nI;
	for (nI=0;nI<nNumberOfCopies;nI++)	{
		vector<osg::ref_ptr<AbstractObject>>::iterator it;
		for (it = pickedObjects.begin(); it != pickedObjects.end(); it++)	{
			ref_ptr<AbstractObject> pObject = dynamic_cast<AbstractObject*>((*it)->clone(CopyOp::DEEP_COPY_ALL));
			pObject->setIsTargetPick(true);
			m_pScene->addChild(pObject);
		}
	}
	m_pPickAndDragHandlerShopEditor->clearList();
}

//-----------------------------------------------------------------------

void ShopBuilder::removeSelection()	{
	vector<ref_ptr<AbstractObject>> & pickedObjects = m_pPickAndDragHandlerShopEditor->getPickedObjects();

	if(pickedObjects.size() < 1)	{
		cout << "No items selected for removal" << endl;
		return;
	}

	//If selection not empty, open the dialog
	RemoveSelection_GUI removeSelection_GUI;
	removeSelection_GUI.setWindowFlags(Qt::FramelessWindowHint);

	QStringListModel model;
	QStringList list;

	vector<ref_ptr<AbstractObject>>::iterator it;
	for (it = pickedObjects.begin(); it != pickedObjects.end(); it++)	{
		list.push_back(string("- " + it->get()->getName()).c_str());
	}

	model.setStringList(list);
	removeSelection_GUI.m_pListView->setModel(&model);

	bool bRes = removeSelection_GUI.exec();
	if (bRes == true)	{
		for (it = pickedObjects.begin(); it != pickedObjects.end(); it++)	{
			m_pScene->removeChild(*it);
		}
	}
	m_pPickAndDragHandlerShopEditor->clearList();
}

//-----------------------------------------------------------------------

void ShopBuilder::editItem()	{
	vector<ref_ptr<AbstractObject>> & pickedObjects = m_pPickAndDragHandlerShopEditor->getPickedObjects();

	if(pickedObjects.size() < 1)	{
		return;
	}

	ref_ptr<AbstractObject> pAbstractObject = pickedObjects[0];	//Only first item is edited

	ref_ptr<AbstractObject> pAbstractObjectClone = dynamic_cast<AbstractObject*>(pAbstractObject->clone(CopyOp::DEEP_COPY_ALL));

	Matrixd mtrxOriginalMatrix = pAbstractObject->getMatrix();

	EditItem_GUIBase * pEditItem_GUIBase = EditItem_GUIBase::createInstance(pAbstractObject);
	pEditItem_GUIBase->setWindowFlags(Qt::FramelessWindowHint);
	int nRes = pEditItem_GUIBase->exec();

	switch (nRes)	{
	case QDialog::Accepted:
		{
			pAbstractObject->setMatrix(mtrxOriginalMatrix);
			break;
		}
	case QDialog::Rejected:
		{
			pAbstractObject->setMatrix(mtrxOriginalMatrix);
			break;
		}
	}

	delete pEditItem_GUIBase;
	m_pPickAndDragHandlerShopEditor->clearList();
}

//-----------------------------------------------------------------------

void ShopBuilder::updateSearchList(string & astrSelectedItemName)	{
	ref_ptr<AbstractObject> pAbstractObject = 
		dynamic_cast<AbstractObject*>(m_pScene->getChild(astrSelectedItemName));

	if (pAbstractObject==0)
		return;

	m_pPickAndDragHandlerShopEditor->m_pPickedObject = pAbstractObject;
}

//-----------------------------------------------------------------------

void ShopBuilder::updateProductSettings(ProductClickedItems & aProductClickedItems)	{
}