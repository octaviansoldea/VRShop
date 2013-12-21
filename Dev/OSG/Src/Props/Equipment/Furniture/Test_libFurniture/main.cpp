#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>

#include <osg/DisplaySettings>

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
#include "VRUntransformedSphere.h"

#include "VRFurniture.h"
#include "VRCupboard.h"
#include "VRContainer.h"

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

	string strCreateTable = "CREATE TABLE IF NOT EXISTS Primitive "
			"(PrimitiveID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"PrimitiveName TEXT UNIQUE);";

	VR::Cylinder cylinder;
	strCreateTable += cylinder.getSQLFormat();

	Plate3D plate3D;
	strCreateTable += plate3D.getSQLFormat();

	Prism prism;
	strCreateTable += prism.getSQLFormat();

	UntransformedSphere sphere;
	strCreateTable += sphere.getSQLFormat();

	strCreateTable += "CREATE TABLE IF NOT EXISTS PrimitiveItemList "
			"(PrimitiveItemListID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"PrimitiveID INTEGER, "
			"ItemID INTEGER, "
			"EquipmentItemID INTEGER, "
			"FOREIGN KEY (PrimitiveID) REFERENCES Primitive(PrimitiveID));";

	strCreateTable += "CREATE TABLE IF NOT EXISTS Texture "
			"(TextureID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"TextureFile TEXT);";

	strCreateTable += "CREATE TABLE IF NOT EXISTS Equipment "
			"(EquipmentID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"EquipmentName TEXT);";

	strCreateTable += "CREATE TABLE IF NOT EXISTS EquipmentItem "
			"(EquipmentItemID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"EquipmentItemName TEXT, "
			"EquipmentID INTEGER,"
			"FOREIGN KEY (EquipmentID) REFERENCES Equipment(EquipmentID));";

	strCreateTable += "CREATE TABLE IF NOT EXISTS Scene "
			"(SceneID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"SceneName TEXT);";

	database.createTable(strCreateTable);
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
	string strSQLCommand = pSphere->getSQLCommand();

	database.fillPrimitiveTable(strSQLCommand);
}

//--------------------------------------------------------------

void insertIntoDatabase_Cylinder(const string & astrDBName)	{
	DatabaseMgr & database = DatabaseMgr::Create(astrDBName.c_str(), DatabaseMgr::QSQLITE);

	ref_ptr < VR::Cylinder > pCylinder =  new VR::Cylinder;
	CylinderParams aCylinderParams;
	pCylinder->init(aCylinderParams);
	string strSQLCommand = pCylinder->getSQLCommand();

	database.fillPrimitiveTable(strSQLCommand);
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
	string strSQLCommand = pPlate3D->getSQLCommand();
	database.fillPrimitiveTable(strSQLCommand);

	//Left plate
	aPlate3DParams = new Plate3DParams;
	aPlate3DParams->m_flLenX = 0.05;
	aPlate3DParams->m_flLenY = 1.0;
	aPlate3DParams->m_flLenZ = 1.0;
	pPlate3D->init(*aPlate3DParams);
	strSQLCommand = pPlate3D->getSQLCommand();
	database.fillPrimitiveTable(strSQLCommand);

	//Right plate
	aPlate3DParams = new Plate3DParams;
	aPlate3DParams->m_flLenX = 0.05;
	aPlate3DParams->m_flLenY = 1.0;
	aPlate3DParams->m_flLenZ = 1.0;
	pPlate3D->init(*aPlate3DParams);
	strSQLCommand = pPlate3D->getSQLCommand();
	database.fillPrimitiveTable(strSQLCommand);

	//Front plate
	aPlate3DParams = new Plate3DParams;
	aPlate3DParams->m_flLenX = 1.0;
	aPlate3DParams->m_flLenY = 0.05;
	aPlate3DParams->m_flLenZ = 1.0;
	pPlate3D->init(*aPlate3DParams);
	strSQLCommand = pPlate3D->getSQLCommand();
	database.fillPrimitiveTable(strSQLCommand);

	//Back plate
	aPlate3DParams = new Plate3DParams;
	aPlate3DParams->m_flLenX = 1.0;
	aPlate3DParams->m_flLenY = 0.05;
	aPlate3DParams->m_flLenZ = 1.0;
	pPlate3D->init(*aPlate3DParams);
	strSQLCommand = pPlate3D->getSQLCommand();
	database.fillPrimitiveTable(strSQLCommand);

	delete aPlate3DParams;
}

//--------------------------------------------------------------


void insertIntoDatabase_Container(const string & astrDBName)	{
	DatabaseMgr & database = DatabaseMgr::Create(astrDBName.c_str(), DatabaseMgr::QSQLITE);

	float m_flWidth(3.0),
	m_flHeight(3.0),
	m_flDepth(2.5),
	m_flThickness(0.01);

	//Set the cupboard
	Container container;

	ref_ptr < Plate3D > pPlate3D =  new Plate3D;
	Plate3DParams aPlate3DParams;
	//Bottom plate
	aPlate3DParams.m_flLenX = m_flWidth;
	aPlate3DParams.m_flLenY = m_flDepth;
	aPlate3DParams.m_flLenZ = m_flThickness;

	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = - 0.5 + m_flThickness/2;

	aPlate3DParams.m_arrflRGBA[0] = 0.1;
	aPlate3DParams.m_arrflRGBA[1] = 0.81;
	aPlate3DParams.m_arrflRGBA[2] = 0.1;
	aPlate3DParams.m_arrflRGBA[3] = 1;
	pPlate3D->init(aPlate3DParams);
	container.addPart(pPlate3D);
	

	//Left plate
	aPlate3DParams.m_flLenX = m_flThickness;
	aPlate3DParams.m_flLenY = m_flDepth;
	aPlate3DParams.m_flLenZ = m_flHeight;
	aPlate3DParams.m_flPosX = (-m_flWidth+m_flThickness)/2;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = - 0.5 + m_flHeight/2;

	aPlate3DParams.m_arrflRGBA[0] = 1;
	aPlate3DParams.m_arrflRGBA[1] = 1;
	aPlate3DParams.m_arrflRGBA[2] = 0;
	aPlate3DParams.m_arrflRGBA[3] = 1;
	pPlate3D->init(aPlate3DParams);
	container.addPart(pPlate3D);

	//Right plate
	aPlate3DParams.m_flLenX = m_flThickness;
	aPlate3DParams.m_flLenY = m_flDepth;
	aPlate3DParams.m_flLenZ = m_flHeight;
	aPlate3DParams.m_flPosX = (m_flWidth-m_flThickness)/2;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = - 0.5 + m_flHeight/2;

	aPlate3DParams.m_arrflRGBA[0] = 0;
	aPlate3DParams.m_arrflRGBA[1] = 1;
	aPlate3DParams.m_arrflRGBA[2] = 1;
	aPlate3DParams.m_arrflRGBA[3] = 1;
	pPlate3D->init(aPlate3DParams);
	container.addPart(pPlate3D);

	//Front plate
	aPlate3DParams.m_flLenX = m_flWidth;
	aPlate3DParams.m_flLenY = m_flThickness;
	aPlate3DParams.m_flLenZ = m_flHeight;
	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = (-m_flDepth+m_flThickness)/2;
	aPlate3DParams.m_flPosZ = - 0.5 + m_flHeight/2;

	aPlate3DParams.m_arrflRGBA[0] = 1;
	aPlate3DParams.m_arrflRGBA[1] = 0;
	aPlate3DParams.m_arrflRGBA[2] = 1;
	aPlate3DParams.m_arrflRGBA[3] = 1;
	pPlate3D->init(aPlate3DParams);
	container.addPart(pPlate3D);

	//Back plate
	aPlate3DParams.m_flLenX = m_flWidth;
	aPlate3DParams.m_flLenY = m_flThickness;
	aPlate3DParams.m_flLenZ = m_flHeight;
	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = (m_flDepth-m_flThickness)/2;
	aPlate3DParams.m_flPosZ = - 0.5 + m_flHeight/2;

	aPlate3DParams.m_strFileNameTexture = "../../../../Resources/Textures/lz.rgb";
	pPlate3D->init(aPlate3DParams);
	container.addPart(pPlate3D);

	string strSQLCommand = container.getSQLCommand();

	database.fillPrimitiveTable(strSQLCommand);
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

	string strSQLCommand = cupboard.getSQLCommand();
	database.fillPrimitiveTable(strSQLCommand);
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

//	insertIntoDatabase_Container(strDBName);
	//insertIntoDatabase_Cupboard(strDBName);

	//Furniture::loadAllFurnitures(pScene, strDBName);

	osgViewer::Viewer viewer;
	viewer.setSceneData(pScene);

	return viewer.run();
}