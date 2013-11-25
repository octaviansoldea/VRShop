#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>

#include <iostream>
#include <string>

#include "VRDatabaseMgr.h"

#include "VRAbstractObject.h"
#include "VRAbstractGeomShape.h"


#include "VRUntransformedPlate2D.h"
#include "VRUntransformedPlate3D.h"
#include "VRUntransformedPolygon2D.h"
#include "VRUntransformedPolygon3D.h"
#include "VRPlate3D.h"
#include "VRCylinder.h"
#include "VRCupboard.h"
#include "VRUntransformedSphere.h"

using namespace osg;
using namespace std;
using namespace VR;


void createTable(const string & astrDBName) {
	QFile file(astrDBName.c_str());
    if (file.open(QIODevice::ReadWrite)) {
		file.remove();
    }
	file.close();
	DatabaseMgr & database = DatabaseMgr::Create(astrDBName.c_str(), DatabaseMgr::QSQLITE);
	database.createTable();
}

//--------------------------------------------------------------

void populateTable(const string & astrDBName)	{
	DatabaseMgr & database = DatabaseMgr::Create(astrDBName.c_str(), DatabaseMgr::QSQLITE);

	DatabaseMgrParams dMgrP;
	dMgrP.m_arrstrParams.resize(0);

	dMgrP.m_qstrObjectType = "Primitive";
	dMgrP.m_qstrObjectName = "Cylinder";
	database.insertIntoDatabase(dMgrP);

	dMgrP.m_qstrObjectName = "Plate3D";
	database.insertIntoDatabase(dMgrP);

	dMgrP.m_qstrObjectName = "Prism";
	database.insertIntoDatabase(dMgrP);

	dMgrP.m_qstrObjectName = "Sphere";
	database.insertIntoDatabase(dMgrP);

	dMgrP.m_qstrObjectType = "Equipment";
	dMgrP.m_qstrObjectName = "Furniture";
	database.insertIntoDatabase(dMgrP);

	dMgrP.m_qstrObjectName = "Decoration";
	database.insertIntoDatabase(dMgrP);

	dMgrP.m_qstrObjectName = "CollectingTools";
	database.insertIntoDatabase(dMgrP);
}

//--------------------------------------------------------------

void insertIntoDatabase_Sphere(const string & astrDBName)	{
	DatabaseMgr & database = DatabaseMgr::Create(astrDBName.c_str(), DatabaseMgr::QSQLITE);

	ref_ptr < UntransformedSphere > pSphere =  new UntransformedSphere;
	SphereParams aSphereParams;
	pSphere->init(aSphereParams);

	database.fillPrimitiveTable(*pSphere);
}

//--------------------------------------------------------------

void insertIntoDatabase_Cylinder(const string & astrDBName)	{
	DatabaseMgr & database = DatabaseMgr::Create(astrDBName.c_str(), DatabaseMgr::QSQLITE);

	ref_ptr < VR::Cylinder > pCylinder =  new VR::Cylinder;
	CylinderParams aCylinderParams;
	pCylinder->init(aCylinderParams);

	database.fillPrimitiveTable(*pCylinder);
}

//--------------------------------------------------------------

void insertIntoDatabase_Plate3D(const string & astrDBName)	{
	DatabaseMgr & database = DatabaseMgr::Create(astrDBName.c_str(), DatabaseMgr::QSQLITE);

	ref_ptr < Plate3D > pPlate3D =  new Plate3D;
	Plate3DParams * aPlate3DParams = new Plate3DParams;
	//Bottom plate
	aPlate3DParams->m_flLenX = 1.0;
	aPlate3DParams->m_flLenY = 1.0;
	aPlate3DParams->m_flLenZ = 0.05;
	pPlate3D->init(*aPlate3DParams);
	database.fillPrimitiveTable(*pPlate3D);

	//Left plate
	aPlate3DParams = new Plate3DParams;
	aPlate3DParams->m_flLenX = 0.05;
	aPlate3DParams->m_flLenY = 1.0;
	aPlate3DParams->m_flLenZ = 1.0;
	pPlate3D->init(*aPlate3DParams);
	database.fillPrimitiveTable(*pPlate3D);

	//Right plate
	aPlate3DParams = new Plate3DParams;
	aPlate3DParams->m_flLenX = 0.05;
	aPlate3DParams->m_flLenY = 1.0;
	aPlate3DParams->m_flLenZ = 1.0;
	pPlate3D->init(*aPlate3DParams);
	database.fillPrimitiveTable(*pPlate3D);

	//Front plate
	aPlate3DParams = new Plate3DParams;
	aPlate3DParams->m_flLenX = 1.0;
	aPlate3DParams->m_flLenY = 0.05;
	aPlate3DParams->m_flLenZ = 1.0;
	pPlate3D->init(*aPlate3DParams);
	database.fillPrimitiveTable(*pPlate3D);

	//Back plate
	aPlate3DParams = new Plate3DParams;
	aPlate3DParams->m_flLenX = 1.0;
	aPlate3DParams->m_flLenY = 0.05;
	aPlate3DParams->m_flLenZ = 1.0;
	pPlate3D->init(*aPlate3DParams);
	database.fillPrimitiveTable(*pPlate3D);

	delete aPlate3DParams;
}

//--------------------------------------------------------------


void insertIntoDatabase_Container(const string & astrDBName)	{
	DatabaseMgr & database = DatabaseMgr::Create(astrDBName.c_str(), DatabaseMgr::QSQLITE);

	//Set the cupboard
	Cupboard cupboard;

	ref_ptr < Plate3D > pPlate3D =  new Plate3D;
	Plate3DParams aPlate3DParams;
	//Bottom plate
	aPlate3DParams.m_flLenX = 1.0;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 0.05;

	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = -0.475;
	aPlate3DParams.m_arrflRGBA[0] = 0.1;
	aPlate3DParams.m_arrflRGBA[1] = 0.81;
	aPlate3DParams.m_arrflRGBA[2] = 0.1;
	aPlate3DParams.m_arrflRGBA[3] = 1;
	pPlate3D->init(aPlate3DParams);
	cupboard.addPart(pPlate3D);
	

	//Left plate
	aPlate3DParams.m_flLenX = 0.05;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 1.0;
	aPlate3DParams.m_flPosX = -0.475;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = 0;
	aPlate3DParams.m_arrflRGBA[0] = 1;
	aPlate3DParams.m_arrflRGBA[1] = 1;
	aPlate3DParams.m_arrflRGBA[2] = 0;
	aPlate3DParams.m_arrflRGBA[3] = 1;
	pPlate3D->init(aPlate3DParams);
	cupboard.addPart(pPlate3D);

	//Right plate
	aPlate3DParams.m_flLenX = 0.05;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 1.0;
	aPlate3DParams.m_flPosX = 0.475;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = 0;
	aPlate3DParams.m_arrflRGBA[0] = 0;
	aPlate3DParams.m_arrflRGBA[1] = 1;
	aPlate3DParams.m_arrflRGBA[2] = 1;
	aPlate3DParams.m_arrflRGBA[3] = 1;
	pPlate3D->init(aPlate3DParams);
	cupboard.addPart(pPlate3D);

	//Front plate
	aPlate3DParams.m_flLenX = 1.0;
	aPlate3DParams.m_flLenY = 0.05;
	aPlate3DParams.m_flLenZ = 1.0;
	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = -0.475;
	aPlate3DParams.m_flPosZ = 0;
	aPlate3DParams.m_arrflRGBA[0] = 1;
	aPlate3DParams.m_arrflRGBA[1] = 0;
	aPlate3DParams.m_arrflRGBA[2] = 1;
	aPlate3DParams.m_arrflRGBA[3] = 1;
	pPlate3D->init(aPlate3DParams);
	cupboard.addPart(pPlate3D);

	//Back plate
	aPlate3DParams.m_flLenX = 1.0;
	aPlate3DParams.m_flLenY = 0.05;
	aPlate3DParams.m_flLenZ = 1.0;
	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = 0.475;
	aPlate3DParams.m_flPosZ = 0;
	aPlate3DParams.m_strFileNameTexture = "../../../../Resources/Textures/lz.rgb";

	pPlate3D->init(aPlate3DParams);
	cupboard.addPart(pPlate3D);

	database.fillPrimitiveTable(cupboard);
}

//--------------------------------------------------------------

void insertIntoDatabase_Cupboard(const string & astrDBName)	{
	DatabaseMgr & database = DatabaseMgr::Create(astrDBName.c_str(), DatabaseMgr::QSQLITE);

	//Set the cupboard
	Cupboard cupboard;

	ref_ptr < Plate3D > pPlate3D =  new Plate3D;
	Plate3DParams aPlate3DParams;
	//Bottom plate
	aPlate3DParams.m_flLenX = 5.0;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 0.05;

	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = -1.0;
	aPlate3DParams.m_arrflRGBA[0] = 1;
	aPlate3DParams.m_arrflRGBA[1] = 1;
	aPlate3DParams.m_arrflRGBA[2] = 0;
	aPlate3DParams.m_arrflRGBA[3] = 1;
	aPlate3DParams.m_strFileNameTexture = "../../../../Resources/Textures/lz.rgb";
	pPlate3D->init(aPlate3DParams);
	cupboard.addPart(pPlate3D);
	

	//Left side
	aPlate3DParams.m_flLenX = 0.05;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 2.0;
	aPlate3DParams.m_flPosX = -2.475;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = 0;
	aPlate3DParams.m_arrflRGBA[0] = 1;
	aPlate3DParams.m_arrflRGBA[1] = 1;
	aPlate3DParams.m_arrflRGBA[2] = 0;
	aPlate3DParams.m_arrflRGBA[3] = 1;
	aPlate3DParams.m_strFileNameTexture = "../../../../Resources/Textures/lz.rgb";
	pPlate3D->init(aPlate3DParams);
	cupboard.addPart(pPlate3D);

	//Right side
	aPlate3DParams.m_flLenX = 0.05;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 2.0;
	aPlate3DParams.m_flPosX = 2.475;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = 0;
	aPlate3DParams.m_arrflRGBA[0] = 0;
	aPlate3DParams.m_arrflRGBA[1] = 1;
	aPlate3DParams.m_arrflRGBA[2] = 1;
	aPlate3DParams.m_arrflRGBA[3] = 1;
	aPlate3DParams.m_strFileNameTexture = "../../../../Resources/Textures/lz.rgb";
	pPlate3D->init(aPlate3DParams);
	cupboard.addPart(pPlate3D);

	//Back side
	aPlate3DParams.m_flLenX = 5.0;
	aPlate3DParams.m_flLenY = 0.05;
	aPlate3DParams.m_flLenZ = 2.0;
	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = 0.475;
	aPlate3DParams.m_flPosZ = 0;
	aPlate3DParams.m_arrflRGBA[0] = 1;
	aPlate3DParams.m_arrflRGBA[1] = 0;
	aPlate3DParams.m_arrflRGBA[2] = 1;
	aPlate3DParams.m_arrflRGBA[3] = 1;
	aPlate3DParams.m_strFileNameTexture = "../../../../Resources/Textures/lz.rgb";
	pPlate3D->init(aPlate3DParams);
	cupboard.addPart(pPlate3D);

	//shelf 1
	aPlate3DParams.m_flLenX = 5.0;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 0.05;

	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = -0.375;
	aPlate3DParams.m_strFileNameTexture = "../../../../Resources/Textures/lz.rgb";
	pPlate3D->init(aPlate3DParams);
	cupboard.addPart(pPlate3D);


	//shelf 2
	aPlate3DParams.m_flLenX = 5.0;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 0.05;

	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = 0.375;
	aPlate3DParams.m_strFileNameTexture = "../../../../Resources/Textures/lz.rgb";
	pPlate3D->init(aPlate3DParams);
	cupboard.addPart(pPlate3D);

	//shelf 3
	aPlate3DParams.m_flLenX = 5.0;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 0.05;

	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = 1;
	aPlate3DParams.m_strFileNameTexture = "../../../../Resources/Textures/lz.rgb";
	pPlate3D->init(aPlate3DParams);
	cupboard.addPart(pPlate3D);

	database.fillPrimitiveTable(cupboard);
}

//--------------------------------------------------------------

void loadAllFurnitures(ref_ptr<Group> pScene) {
	string strDatabase = "../../../../Databases/Equipment.db";
	DatabaseMgr & database = DatabaseMgr::Create(strDatabase.c_str(), DatabaseMgr::QSQLITE);

	// get the number of equipment to be added to the scene
	QString qstrCupboardsNr = "SELECT COUNT(EquipmentItemID) FROM EquipmentItem";
	QSqlQuery qQuery(qstrCupboardsNr);

	int nCupboardsNr;
	while (qQuery.next())	{
		nCupboardsNr = qQuery.value(0).toInt();
	}

	for(int nI = 1; nI <= nCupboardsNr; nI++) {
		ref_ptr <Cupboard> cupboard = new Cupboard;

		QString strSQLQuery = QString("SELECT * FROM EquipmentItem WHERE EquipmentItemID = %1").arg(nI);
		string strSQLData = database.readFromDB(strSQLQuery.toStdString());
		cupboard->initFromSQLData(strSQLData);

		pScene->addChild(cupboard->m_pCupboard);
	}
}

//====================================================

int main(int argc, char *argv[])	{
	QApplication app(argc,argv);

	ref_ptr<Group> pScene = new Group;
	ref_ptr<Node> pAxes = osgDB::readNodeFile("../../../../Resources/Models3D/axes.osgt");
	pScene->addChild(pAxes);

	string strDBName;
	
	strDBName = "../../../../Databases/Equipment.db";
	createTable(strDBName);
	populateTable(strDBName);

	//insertIntoDatabase_Sphere(strDBName);
	//insertIntoDatabase_Cylinder(strDBName);
	//insertIntoDatabase_Plate3D(strDBName);

	insertIntoDatabase_Container(strDBName);
//	insertIntoDatabase_Cupboard(strDBName);
	loadAllFurnitures(pScene);

	osgViewer::Viewer viewer;
	viewer.setSceneData(pScene);

	return viewer.run();
}