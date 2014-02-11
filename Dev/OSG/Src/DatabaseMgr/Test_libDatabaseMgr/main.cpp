#include <QApplication>
#include <QMessageBox>
#include <QFile>

#include <iostream>
#include <string>

#include <BasicStringDefinitions.h>

#include "VRDatabaseMgr.h"

#include "VRAbstractGeomShape.h"


#include "VRUntransformedPlate2D.h"
#include "VRUntransformedPlate3D.h"
#include "VRUntransformedPolygon2D.h"
#include "VRUntransformedPolygon3D.h"
#include "VRUntransformedSphere.h"
#include "VRPlate3D.h"
#include "VRSphere.h"
#include "VRCylinder.h"
#include "VRCupboard.h"

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

	DatabaseMgrParams dMgrParams;

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

	VR::Sphere sphere;
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
			"EquipmentItemMatrix TEXT, "
			"EquipmentID INTEGER,"
			"FOREIGN KEY (EquipmentID) REFERENCES Equipment(EquipmentID));";
	dMgrParams.m_arrstrParams.push_back(strCreateTable);

	strCreateTable = "CREATE TABLE IF NOT EXISTS Scene "
			"(SceneID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"SceneName TEXT);";
	dMgrParams.m_arrstrParams.push_back(strCreateTable);

	database.executeQuery(dMgrParams);
}

//--------------------------------------------------------------

void populateTable(const string & astrDBName)	{
	DatabaseMgr & database = DatabaseMgr::Create(astrDBName.c_str(), DatabaseMgr::QSQLITE);

	DatabaseMgrParams dMgrParams;
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

	database.executeQuery(dMgrParams);
}

//--------------------------------------------------------------

void insertIntoDatabase_Sphere(const string & astrDBName)	{
	DatabaseMgr & database = DatabaseMgr::Create(astrDBName.c_str(), DatabaseMgr::QSQLITE);

	VR::SphereParams aSphereParams;
	aSphereParams.m_nResPhi = 35;
	aSphereParams.m_arrflRGBA.push_back(0.85);
	aSphereParams.m_arrflRGBA.push_back(0.15);
	aSphereParams.m_arrflRGBA.push_back(0.15);
	aSphereParams.m_arrflRGBA.push_back(1.0);

	ref_ptr < VR::Sphere > pSphere =  new VR::Sphere(aSphereParams);
	string strSQLCommand = pSphere->getSQLCommand();

	DatabaseMgrParams dMgrParams;
	dMgrParams.m_arrstrParams.push_back(strSQLCommand);

	database.executeQuery(dMgrParams);
}

//--------------------------------------------------------------

void insertIntoDatabase_Cylinder(const string & astrDBName)	{
	DatabaseMgr & database = DatabaseMgr::Create(astrDBName.c_str(), DatabaseMgr::QSQLITE);

	ref_ptr < VR::Cylinder > pCylinder =  new VR::Cylinder;
	CylinderParams aCylinderParams;
	pCylinder->init(aCylinderParams);
	string strSQLCommand = pCylinder->getSQLCommand();

	DatabaseMgrParams dMgrParams;
	dMgrParams.m_arrstrParams.push_back(strSQLCommand);

	database.executeQuery(dMgrParams);
}

//--------------------------------------------------------------

void insertIntoDatabase_Plate3D(const string & astrDBName)	{
	DatabaseMgr & database = DatabaseMgr::Create(astrDBName.c_str(), DatabaseMgr::QSQLITE);

	DatabaseMgrParams dMgrParams;

	Plate3D plate3D;
	Plate3DParams aPlate3DParams;
	//Bottom plate
	aPlate3DParams.m_flLenX = 1.0;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 0.05;
	plate3D.init(aPlate3DParams);
	string strSQLCommand = plate3D.getSQLCommand();
	dMgrParams.m_arrstrParams.push_back(strSQLCommand);

	//Left plate
	aPlate3DParams.m_flLenX = 0.05;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 1.0;
	plate3D.init(aPlate3DParams);
	strSQLCommand = plate3D.getSQLCommand();
	dMgrParams.m_arrstrParams.push_back(strSQLCommand);

	//Right plate
	aPlate3DParams.m_flLenX = 0.05;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 1.0;
	plate3D.init(aPlate3DParams);
	strSQLCommand = plate3D.getSQLCommand();
	dMgrParams.m_arrstrParams.push_back(strSQLCommand);

	//Front plate
	aPlate3DParams.m_flLenX = 1.0;
	aPlate3DParams.m_flLenY = 0.05;
	aPlate3DParams.m_flLenZ = 1.0;
	plate3D.init(aPlate3DParams);
	strSQLCommand = plate3D.getSQLCommand();
	dMgrParams.m_arrstrParams.push_back(strSQLCommand);

	//Back plate
	aPlate3DParams.m_flLenX = 1.0;
	aPlate3DParams.m_flLenY = 0.05;
	aPlate3DParams.m_flLenZ = 1.0;
	plate3D.init(aPlate3DParams);
	strSQLCommand = plate3D.getSQLCommand();
	dMgrParams.m_arrstrParams.push_back(strSQLCommand);

	database.executeQuery(dMgrParams);
}

//--------------------------------------------------------------

void insertIntoDatabase_Furniture(const string & astrDBName)	{
	DatabaseMgr & database = DatabaseMgr::Create(astrDBName.c_str(), DatabaseMgr::QSQLITE);

	//Set the cupboard
	Cupboard cupboard;

	ref_ptr < Plate3D > pPlate3D =  new Plate3D;
	Plate3DParams aPlate3DParams;
	//Bottom plate
	aPlate3DParams.m_flLenX = 1.0;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 0.05;
	pPlate3D->init(aPlate3DParams);
	cupboard.addPart(pPlate3D);
	

	//Left plate
	aPlate3DParams.m_flLenX = 0.05;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 1.0;
	pPlate3D->init(aPlate3DParams);
	cupboard.addPart(pPlate3D);

	//Right plate
	aPlate3DParams.m_flLenX = 0.05;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 1.0;
	pPlate3D->init(aPlate3DParams);
	cupboard.addPart(pPlate3D);

	//Front plate
	aPlate3DParams.m_flLenX = 1.0;
	aPlate3DParams.m_flLenY = 0.05;
	aPlate3DParams.m_flLenZ = 1.0;
	pPlate3D->init(aPlate3DParams);
	cupboard.addPart(pPlate3D);

	//Back plate
	aPlate3DParams.m_flLenX = 1.0;
	aPlate3DParams.m_flLenY = 0.05;
	aPlate3DParams.m_flLenZ = 1.0;
	pPlate3D->init(aPlate3DParams);
	cupboard.addPart(pPlate3D);

	string strSQLCommand = cupboard.getSQLCommand();

	vector<string> arrstrCommands = splitString(strSQLCommand,";");
	DatabaseMgrParams dMgrP;
	dMgrP.m_arrstrParams = arrstrCommands;

	database.fillPrimitiveTable(dMgrP);
}

//====================================================

int main(int argc, char *argv[])	{
	QApplication app(argc,argv);

	string strDBName;
	
	strDBName = "../../Databases/Equipment.db";
	createTable(strDBName);
	populateTable(strDBName);
	insertIntoDatabase_Sphere(strDBName);
	insertIntoDatabase_Cylinder(strDBName);
	insertIntoDatabase_Plate3D(strDBName);
	insertIntoDatabase_Furniture(strDBName);
	insertIntoDatabase_Furniture(strDBName);


	return 0;
}