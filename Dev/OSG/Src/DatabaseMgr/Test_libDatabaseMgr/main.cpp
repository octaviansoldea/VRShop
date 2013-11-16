#include <QApplication>
#include <QMessageBox>

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

	dMgrP.m_qstrObjectName = "Parallelepiped";
	database.insertIntoDatabase(dMgrP);

	dMgrP.m_qstrObjectName = "Prism";
	database.insertIntoDatabase(dMgrP);

	dMgrP.m_qstrObjectName = "Sphere";
	database.insertIntoDatabase(dMgrP);
}

//--------------------------------------------------------------

void insertIntoDatabase_Sphere(const string & astrDBName)	{
	DatabaseMgr & database = DatabaseMgr::Create(astrDBName.c_str(), DatabaseMgr::QSQLITE);

	ref_ptr < UntransformedSphere > pSphere =  new UntransformedSphere;
	SphereParams aSphereParams;

	string strCommand = pSphere->getSQLCommand(aSphereParams);
	database.fillPrimitiveTable(strCommand);
}

//--------------------------------------------------------------

void insertIntoDatabase_Cylinder(const string & astrDBName)	{
	DatabaseMgr & database = DatabaseMgr::Create(astrDBName.c_str(), DatabaseMgr::QSQLITE);

	ref_ptr < VR::Cylinder > pCylinder =  new VR::Cylinder;
	CylinderParams aCylinderParams;

	string strCommand = pCylinder->getSQLCommand(aCylinderParams);
	database.fillPrimitiveTable(strCommand);
}

//--------------------------------------------------------------

void insertIntoDatabase_Parallelepiped(const string & astrDBName)	{
	DatabaseMgr & database = DatabaseMgr::Create(astrDBName.c_str(), DatabaseMgr::QSQLITE);

	ref_ptr < Plate3D > pPlate3D =  new Plate3D;
	Plate3DParams * aPlate3DParams = new Plate3DParams;
	//Bottom plate
	aPlate3DParams->m_flLenX = 1.0;
	aPlate3DParams->m_flLenY = 1.0;
	aPlate3DParams->m_flLenZ = 0.05;
	string strCommand = pPlate3D->getSQLCommand(*aPlate3DParams);
	database.fillPrimitiveTable(strCommand);

	//Left plate
	aPlate3DParams = new Plate3DParams;
	aPlate3DParams->m_flLenX = 0.05;
	aPlate3DParams->m_flLenY = 1.0;
	aPlate3DParams->m_flLenZ = 1.0;
	strCommand = pPlate3D->getSQLCommand(*aPlate3DParams);
	database.fillPrimitiveTable(strCommand);

	//Right plate
	aPlate3DParams = new Plate3DParams;
	aPlate3DParams->m_flLenX = 0.05;
	aPlate3DParams->m_flLenY = 1.0;
	aPlate3DParams->m_flLenZ = 1.0;
	strCommand = pPlate3D->getSQLCommand(*aPlate3DParams);
	database.fillPrimitiveTable(strCommand);

	//Front plate
	aPlate3DParams = new Plate3DParams;
	aPlate3DParams->m_flLenX = 1.0;
	aPlate3DParams->m_flLenY = 0.05;
	aPlate3DParams->m_flLenZ = 1.0;
	strCommand = pPlate3D->getSQLCommand(*aPlate3DParams);
	database.fillPrimitiveTable(strCommand);

	//Back plate
	aPlate3DParams = new Plate3DParams;
	aPlate3DParams->m_flLenX = 1.0;
	aPlate3DParams->m_flLenY = 0.05;
	aPlate3DParams->m_flLenZ = 1.0;
	strCommand = pPlate3D->getSQLCommand(*aPlate3DParams);
	database.fillPrimitiveTable(strCommand);

	delete aPlate3DParams;
}

//--------------------------------------------------------------


void insertIntoDatabase_Furniture(const string & astrDBName)	{
	DatabaseMgr & database = DatabaseMgr::Create(astrDBName.c_str(), DatabaseMgr::QSQLITE);

	Cupboard cupboard;

	//Set the cupboard


	ref_ptr < Plate3D > pPlate3D =  new Plate3D;
	Plate3DParams * aPlate3DParams = new Plate3DParams;
	//Bottom plate
	aPlate3DParams->m_flLenX = 1.0;
	aPlate3DParams->m_flLenY = 1.0;
	aPlate3DParams->m_flLenZ = 0.05;
	string strCommand = pPlate3D->getSQLCommand(*aPlate3DParams);
	database.fillPrimitiveTable(strCommand);

	//Left plate
	aPlate3DParams = new Plate3DParams;
	aPlate3DParams->m_flLenX = 0.05;
	aPlate3DParams->m_flLenY = 1.0;
	aPlate3DParams->m_flLenZ = 1.0;
	strCommand = pPlate3D->getSQLCommand(*aPlate3DParams);
	database.fillPrimitiveTable(strCommand);

	//Right plate
	aPlate3DParams = new Plate3DParams;
	aPlate3DParams->m_flLenX = 0.05;
	aPlate3DParams->m_flLenY = 1.0;
	aPlate3DParams->m_flLenZ = 1.0;
	strCommand = pPlate3D->getSQLCommand(*aPlate3DParams);
	database.fillPrimitiveTable(strCommand);

	//Front plate
	aPlate3DParams = new Plate3DParams;
	aPlate3DParams->m_flLenX = 1.0;
	aPlate3DParams->m_flLenY = 0.05;
	aPlate3DParams->m_flLenZ = 1.0;
	strCommand = pPlate3D->getSQLCommand(*aPlate3DParams);
	database.fillPrimitiveTable(strCommand);

	//Back plate
	aPlate3DParams = new Plate3DParams;
	aPlate3DParams->m_flLenX = 1.0;
	aPlate3DParams->m_flLenY = 0.05;
	aPlate3DParams->m_flLenZ = 1.0;
	strCommand = pPlate3D->getSQLCommand(*aPlate3DParams);
	database.fillPrimitiveTable(strCommand);

	//A line in the SQL database of furniture will be as follows:
	// PrimitiveID1 transformMatrix1 PrimitiveID2 transformMatrix2 ... GeneralTransformMatrix
	
	QString qstrCommand = cupboard.getSQLPrintCommand().c_str();
	QSqlQuery qry(qstrCommand);

	delete aPlate3DParams;
}

//====================================================

int main(int argc, char *argv[])	{
	QApplication app(argc,argv);

	string strDBName;
	
	strDBName = "../../Databases/Furniture.db";
	createTable(strDBName);
	populateTable(strDBName);
	//insertIntoDatabase_Sphere(strDBName);
	//insertIntoDatabase_Cylinder(strDBName);
	insertIntoDatabase_Parallelepiped(strDBName);
	insertIntoDatabase_Furniture(strDBName);



	return(0);
}