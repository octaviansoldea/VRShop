#include <string>

#include <QString>
#include <QVariant>
#include <QVBoxLayout>

#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>

#include "OSGQT_Widget.h"
#include "VRDatabaseMgr.h"

#include "VRSceneStructureModel.h"

#include "VRShopBuilder.h"

using namespace osg;
using namespace VR;
using namespace std;

//----------------------------------------------------------------------

ShopBuilder::ShopBuilder() : m_pSceneHierarchy(0) {	

	//Define a scene as a group
	m_pScene = new Group;

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
	m_pOSGQTWidget->setCameraManipulator(new osgGA::TrackballManipulator);
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
	}
	else {
		m_pScene->removeChild(m_pGridlines);
	}
}

//----------------------------------------------------------------------

void ShopBuilder::newDB(const std::string & astrDBFileName)	{
	DatabaseMgr & database = DatabaseMgr::Create(astrDBFileName.c_str(), DatabaseMgr::QSQLITE);

	//This function should be able to prepare all the infrastructure necessary for the work with the DB
}

//----------------------------------------------------------------------

void ShopBuilder::readDB(const std::string & astrDBFileName)	{
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

		m_pScene->addChild(pAbstractObject);
	}
	updateQTreeView();
}

//----------------------------------------------------------------------

void ShopBuilder::saveDB(const string & astrDBFileName)	{
}

//----------------------------------------------------------------------

void ShopBuilder::addNewItem(const std::string & astrObjectName, const std::string & astrDBFileName)	{
	ref_ptr < AbstractObject > pAbstractObject = static_cast<AbstractObject*>(AbstractObject::createInstance(astrObjectName));

	pAbstractObject->predefinedObject();
	DatabaseMgr & database = DatabaseMgr::Create(astrDBFileName.c_str(), DatabaseMgr::QSQLITE);

	string strSQLCommand = pAbstractObject->getSQLCommand();
	database.fillPrimitiveTable(strSQLCommand);
}

//----------------------------------------------------------------------

void ShopBuilder::updateQTreeView()	{
	if(m_pSceneHierarchy)
		delete m_pSceneHierarchy;
	
	m_pSceneHierarchy = new SceneHierarchy(m_pScene);
	QList<QString> lststrSceneData = m_pSceneHierarchy->getSceneHierarchy();

	SceneStructureModel * pModel = new SceneStructureModel(lststrSceneData);
	m_pTreeView->setModel(pModel);
	m_pTreeView->show();
}