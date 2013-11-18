#include <QApplication>
#include <QMessageBox>

#include <osgViewer/Viewer>

#include <iostream>
#include <string>

#include <BasicStringDefinitions.h>

#include "VRDatabaseMgr.h"

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
	DatabaseMgr & database = DatabaseMgr::Create(astrDBName.c_str(), DatabaseMgr::QSQLITE);
	database.createTable();
}

//--------------------------------------------------------------

void populateTable(const string & astrDBName)	{
	DatabaseMgr & database = DatabaseMgr::Create(astrDBName.c_str(), DatabaseMgr::QSQLITE);

	DatabaseMgrParams dMgrP;
	dMgrP.m_arrflParams.resize(0);

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
	dMgrP.m_qstrObjectName = "Decoration";
	database.insertIntoDatabase(dMgrP);

	dMgrP.m_qstrObjectName = "CollectingTools";
	database.insertIntoDatabase(dMgrP);

	dMgrP.m_qstrObjectName = "Furniture";
	database.insertIntoDatabase(dMgrP);
}

//--------------------------------------------------------------

void insertIntoDatabase_Sphere(const string & astrDBName)	{
	DatabaseMgr & database = DatabaseMgr::Create(astrDBName.c_str(), DatabaseMgr::QSQLITE);

	ref_ptr < UntransformedSphere > pSphere =  new UntransformedSphere;
	SphereParams aSphereParams;
	pSphere->init(aSphereParams);

	string strCommand = pSphere->getSQLCommand();
	database.fillPrimitiveTable(strCommand);
}

//--------------------------------------------------------------

void insertIntoDatabase_Cylinder(const string & astrDBName)	{
	DatabaseMgr & database = DatabaseMgr::Create(astrDBName.c_str(), DatabaseMgr::QSQLITE);

	ref_ptr < VR::Cylinder > pCylinder =  new VR::Cylinder;
	CylinderParams aCylinderParams;
	pCylinder->init(aCylinderParams);

	string strCommand = pCylinder->getSQLCommand();
	database.fillPrimitiveTable(strCommand);
}

//--------------------------------------------------------------

void insertIntoDatabase_Plate3D(const string & astrDBName)	{
	DatabaseMgr & database = DatabaseMgr::Create(astrDBName.c_str(), DatabaseMgr::QSQLITE);

	ref_ptr < Plate3D > pPlate3D =  new Plate3D;
	Plate3DParams aPlate3DParams;
	//Bottom plate
	aPlate3DParams.m_flLenX = 1.0;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 0.05;
	pPlate3D->init(aPlate3DParams);
	string strCommand = pPlate3D->getSQLCommand();
	database.fillPrimitiveTable(strCommand);

	//Left plate
	aPlate3DParams.m_flLenX = 0.05;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 1.0;
	pPlate3D->init(aPlate3DParams);
	strCommand = pPlate3D->getSQLCommand();
	database.fillPrimitiveTable(strCommand);

	//Right plate
	aPlate3DParams.m_flLenX = 0.05;
	aPlate3DParams.m_flLenY = 1.0;
	aPlate3DParams.m_flLenZ = 1.0;
	pPlate3D->init(aPlate3DParams);
	strCommand = pPlate3D->getSQLCommand();
	database.fillPrimitiveTable(strCommand);

	//Front plate
	aPlate3DParams.m_flLenX = 1.0;
	aPlate3DParams.m_flLenY = 0.05;
	aPlate3DParams.m_flLenZ = 1.0;
	pPlate3D->init(aPlate3DParams);
	strCommand = pPlate3D->getSQLCommand();
	database.fillPrimitiveTable(strCommand);

	//Back plate
	aPlate3DParams.m_flLenX = 1.0;
	aPlate3DParams.m_flLenY = 0.05;
	aPlate3DParams.m_flLenZ = 1.0;
	pPlate3D->init(aPlate3DParams);
	strCommand = pPlate3D->getSQLCommand();
	database.fillPrimitiveTable(strCommand);
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

	string strCommand = cupboard.getSQLPrintCommand();
	database.fillPrimitiveTable(strCommand);
}

//====================================================

int main(int argc, char *argv[])	{
	QApplication app(argc,argv);

	string strDBName;
	
	strDBName = "../../Databases/Equipment.db";
	createTable(strDBName);
	populateTable(strDBName);
	//insertIntoDatabase_Sphere(strDBName);
	//insertIntoDatabase_Cylinder(strDBName);
	//insertIntoDatabase_Plate3D(strDBName);
	insertIntoDatabase_Furniture(strDBName);


	return 0;
}