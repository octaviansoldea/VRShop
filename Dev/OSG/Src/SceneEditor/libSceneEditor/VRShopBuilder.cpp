#include <string>

#include <QString>
#include <QVariant>
#include <QVBoxLayout>

#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>

#include "OSGQT_Widget.h"
#include "VRDatabaseMgr.h"
#include "VRCupboard.h"
#include "VRContainer.h"

#include "VRSceneStructureModel.h"
#include "VRSceneHierarchy.h"

#include "VRShopBuilder.h"

using namespace osg;
using namespace VR;
using namespace std;

//----------------------------------------------------------------------

ShopBuilder::ShopBuilder() {	

	//Define a scene as a group
	m_pScene = new Group;

	ref_ptr<Node> pAxes = osgDB::readNodeFile("../../../Resources/Models3D/axes.osgt");
	m_pScene->addChild(pAxes);

	m_pGridlines = new Grid;

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

void ShopBuilder::readDB(const std::string & astrDBFileName)	{
	DatabaseMgr & database = DatabaseMgr::Create(astrDBFileName.c_str(), DatabaseMgr::QSQLITE);

	QString qstrCupboardsNr = "SELECT EquipmentItemName FROM EquipmentItem";
	QSqlQuery qQuery(qstrCupboardsNr);

	vector < string > strEquipment;
	while (qQuery.next())	{
		strEquipment.push_back(qQuery.value(0).toString().toStdString());
	}

	for (auto it = strEquipment.begin(); it != strEquipment.end(); it++)	{
		QString strSQLQuery = QString("SELECT * FROM EquipmentItem WHERE EquipmentItemName = '%1'").arg(it->c_str());
		string strSQLData = database.readFromDB(strSQLQuery.toStdString());

		ref_ptr < Furniture > pFurniture = Furniture::getInstance(*it);
		pFurniture->initFromSQLData(strSQLData);

		m_pScene->addChild(pFurniture);
	}
	updateQTreeView();
}

//----------------------------------------------------------------------

void ShopBuilder::updateQTreeView()	{
	SceneHierarchy * pSceneHierarchy = new SceneHierarchy(m_pScene);
	QList<QString> lststrSceneData = pSceneHierarchy->getSceneHierarchy();

	SceneStructureModel * pModel = new SceneStructureModel(lststrSceneData);
	m_pTreeView->setModel(pModel);
	m_pTreeView->show();
}