#include "StringManipulation.h"

#include <string>

#include <QString>
#include <QVariant>
#include <QVBoxLayout>

#include "VRFurniture.h"
#include "VRPlate3D.h"
#include "VRCylinder.h"
#include "VRUntransformedSphere.h"

#include "VRPickAndDragHandler.h"
#include "VRKeyboardMouseManipulator.h"

#include <osgDB/ReadFile>

#include "OSGQT_Widget.h"
#include "VRDatabaseMgr.h"

#include "VRSceneStructureModel.h"

#include "VRShopBuilder.h"

using namespace osg;
using namespace VR;
using namespace std;

//----------------------------------------------------------------------

ShopBuilder::ShopBuilder() : m_pSceneHierarchy(0) {	

	m_qstrFileName = "../../../Databases/Temp.db";

	//Define a scene as a group
	m_pScene = new Group;
	m_pObjects = new Group;

	ref_ptr<Node> pAxes = osgDB::readNodeFile("../../../Resources/Models3D/axes.osgt");
	m_pScene->addChild(pAxes);

	m_pGridlines = new Grid;
}

//----------------------------------------------------------------------

ShopBuilder::~ShopBuilder() {	
	delete m_pSceneHierarchy;
}

//----------------------------------------------------------------------

void ShopBuilder::init(OSGQT_Widget * apOSGQTWidget, QTreeView * apTreeView) {
	m_pOSGQTWidget = apOSGQTWidget;

	//Send scene to the Widget
	m_pOSGQTWidget->setSceneData(m_pScene);
	m_pOSGQTWidget->setCameraManipulator(new VR::KeyboardMouseManipulator);
	m_pOSGQTWidget->addEventHandler(new VR::PickAndDragHandler);
	
	m_pTreeView = apTreeView;
	updateQTreeView();

 	m_pScene->addChild(m_pGridlines);
}

//----------------------------------------------------------------------

void ShopBuilder::gridOnOff(bool abIndicator) {
	//ToolButton checked && Grid not already a child
	if (abIndicator) {
		m_pGridlines = new Grid;
		m_pScene->addChild(m_pGridlines);
	} else {
		m_pScene->removeChild(m_pGridlines);
	}
}

//----------------------------------------------------------------------

void ShopBuilder::newDB(const string & astrDBFileName)	{
	//If previous file not saved, warn
	int nNum = m_pScene->getChildIndex(m_pObjects);
	m_pScene->removeChild(nNum);
	m_pObjects = NULL;
	m_pObjects = new Group;

	m_qstrFileName = astrDBFileName.c_str();

	DatabaseMgr & database = DatabaseMgr::Create(m_qstrFileName, DatabaseMgr::QSQLITE);
	DatabaseMgrParams dMgrParams;
	{
		string strCreateTable = "CREATE TABLE IF NOT EXISTS Primitive "
			"(PrimitiveID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"PrimitiveName TEXT UNIQUE);";
		dMgrParams.m_arrstrParams.push_back(strCreateTable);

		VR::Cylinder cylinder;
		strCreateTable = cylinder.getSQLFormat();
		dMgrParams.m_arrstrParams.push_back(strCreateTable);

		Plate3D plate3D;
		strCreateTable = plate3D.getSQLFormat();
		dMgrParams.m_arrstrParams.push_back(strCreateTable);

		Prism prism;
		strCreateTable = prism.getSQLFormat();
		dMgrParams.m_arrstrParams.push_back(strCreateTable);

		UntransformedSphere sphere;
		strCreateTable = sphere.getSQLFormat();
		dMgrParams.m_arrstrParams.push_back(strCreateTable);

		strCreateTable = "CREATE TABLE IF NOT EXISTS PrimitiveItemList "
			"(PrimitiveItemListID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"PrimitiveID INTEGER, "
			"ItemID INTEGER, "
			"EquipmentItemID INTEGER, "
			"FOREIGN KEY (PrimitiveID) REFERENCES Primitive(PrimitiveID));";
		dMgrParams.m_arrstrParams.push_back(strCreateTable);

		strCreateTable = "CREATE TABLE IF NOT EXISTS Texture "
			"(TextureID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"TextureFile TEXT);";
		dMgrParams.m_arrstrParams.push_back(strCreateTable);

		strCreateTable = "CREATE TABLE IF NOT EXISTS Equipment "
			"(EquipmentID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"EquipmentName TEXT);";
		dMgrParams.m_arrstrParams.push_back(strCreateTable);

		strCreateTable = "CREATE TABLE IF NOT EXISTS EquipmentItem "
			"(EquipmentItemID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"EquipmentItemName TEXT, "
			"EquipmentID INTEGER,"
			"FOREIGN KEY (EquipmentID) REFERENCES Equipment(EquipmentID));";
		dMgrParams.m_arrstrParams.push_back(strCreateTable);

		strCreateTable = "CREATE TABLE IF NOT EXISTS Scene "
			"(SceneID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"SceneName TEXT);";
		dMgrParams.m_arrstrParams.push_back(strCreateTable);
	}
	{
		string strSQLCommand;
		strSQLCommand = "INSERT INTO Primitive(PrimitiveName) VALUES('Cylinder');";
		dMgrParams.m_arrstrParams.push_back(strSQLCommand);

		strSQLCommand = "INSERT INTO Primitive(PrimitiveName) VALUES('Plate3D');";
		dMgrParams.m_arrstrParams.push_back(strSQLCommand);

		strSQLCommand = "INSERT INTO Primitive(PrimitiveName) VALUES('Prism');";
		dMgrParams.m_arrstrParams.push_back(strSQLCommand);

		strSQLCommand = "INSERT INTO Primitive(PrimitiveName) VALUES('Sphere');";
		dMgrParams.m_arrstrParams.push_back(strSQLCommand);
	
		strSQLCommand = "INSERT INTO Equipment(EquipmentName) VALUES ('Furniture');";
		dMgrParams.m_arrstrParams.push_back(strSQLCommand);

		strSQLCommand = "INSERT INTO Equipment(EquipmentName) VALUES ('Decoration');";
		dMgrParams.m_arrstrParams.push_back(strSQLCommand);

		strSQLCommand = "INSERT INTO Equipment(EquipmentName) VALUES ('CollectingTools');";
		dMgrParams.m_arrstrParams.push_back(strSQLCommand);
	}
	database.executeQuery(dMgrParams);

	gridOnOff(true);
	//ref_ptr<Node> pAxes = osgDB::readNodeFile("../../../Resources/Models3D/axes.osgt");
	//m_pScene->addChild(pAxes);
	m_pScene->addChild(m_pObjects);
}

//----------------------------------------------------------------------

void ShopBuilder::readDB(const string & astrDBFileName)	{
	int nNum = m_pScene->getChildIndex(m_pObjects);
	m_pScene->removeChild(nNum);
	m_pObjects = NULL;
	m_pObjects = new Group;

	m_qstrFileName = astrDBFileName.c_str();

	DatabaseMgr & database = DatabaseMgr::Create(astrDBFileName.c_str(), DatabaseMgr::QSQLITE);
	
	QString qstrCupboardsNr = "SELECT EquipmentItemName FROM EquipmentItem";
	QSqlQuery qQuery(qstrCupboardsNr);

	vector < string > strEquipment;
	while (qQuery.next())	{
		strEquipment.push_back(qQuery.value(0).toString().toStdString());
	}

	ref_ptr < AbstractObject> pAbstractObject;
	for (auto it = strEquipment.begin(); it != strEquipment.end(); it++)	{
		QString strSQLQuery = QString("SELECT * FROM EquipmentItem WHERE EquipmentItemName = '%1'").arg(it->c_str());
		string strSQLData = database.readFromDB(strSQLQuery.toStdString());

		pAbstractObject = static_cast<AbstractObject*>(AbstractObject::createInstance(*it));

		pAbstractObject->initFromSQLData(strSQLData);
		pAbstractObject->setIsTargetPick(true);

		m_pObjects->addChild(pAbstractObject);
	}
	m_pScene->addChild(m_pObjects);
	updateQTreeView();
}

//----------------------------------------------------------------------

void ShopBuilder::saveDB(const string & astrDBFileName)	{
}

//----------------------------------------------------------------------

void ShopBuilder::addNewItem(const string & astrObjectName)	{
	ref_ptr < AbstractObject > pAbstractObject = static_cast<AbstractObject*>(AbstractObject::createInstance(astrObjectName).get());

	pAbstractObject->predefinedObject();
	string strSQLCommand = pAbstractObject->getSQLCommand();
	vector<string> arrstrCommands = splitString(strSQLCommand,";");
	DatabaseMgrParams dMgrP;
	dMgrP.m_arrstrParams = arrstrCommands;

	DatabaseMgr & database = DatabaseMgr::Create(m_qstrFileName, DatabaseMgr::QSQLITE);
	database.fillPrimitiveTable(dMgrP);

	m_pObjects->addChild(pAbstractObject);
	m_pScene->addChild(m_pObjects);

	updateQTreeView();
}

//----------------------------------------------------------------------

void ShopBuilder::updateQTreeView()	{
	if(m_pSceneHierarchy)
		delete m_pSceneHierarchy;
	
	m_pSceneHierarchy = new SceneHierarchy(m_pObjects);
	QList<QString> lststrSceneData = m_pSceneHierarchy->getSceneHierarchy();

	SceneStructureModel * pModel = new SceneStructureModel(lststrSceneData);
	m_pTreeView->setModel(pModel);
	m_pTreeView->show();
}