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
#include "VRUntransformedSphere.h"

using namespace osg;
using namespace std;
using namespace VR;


void createTable() {
	std::string strDatabase = "../../Databases/Products.db";
	DatabaseMgr & database = DatabaseMgr::Create(strDatabase.c_str(), DatabaseMgr::QSQLITE);
	database.createTable();
}

//--------------------------------------------------------------

void populateTable()	{
	std::string strDatabase = "../../Databases/Products.db";
	DatabaseMgr & database = DatabaseMgr::Create(strDatabase.c_str(), DatabaseMgr::QSQLITE);

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

void main_InsertIntoDatabase_Sphere()	{
	std::string strDatabase = "../../Databases/Products.db";
	DatabaseMgr & database = DatabaseMgr::Create(strDatabase.c_str(), DatabaseMgr::QSQLITE);

	ref_ptr < UntransformedSphere > pSphere =  new UntransformedSphere;
	string strCommand = pSphere->getSQLCommand();

	database.fillPrimitiveTable(strCommand);
}

//--------------------------------------------------------------

void main_InsertIntoDatabase_Cylinder()	{
	std::string strDatabase = "../../Databases/Products.db";
	DatabaseMgr & database = DatabaseMgr::Create(strDatabase.c_str(), DatabaseMgr::QSQLITE);

	ref_ptr < VR::Cylinder > pCylinder =  new VR::Cylinder;
	string strCommand = pCylinder->getSQLCommand();

	database.fillPrimitiveTable(strCommand);
}

//--------------------------------------------------------------

void main_InsertIntoDatabase_Parallelepiped()	{
	std::string strDatabase = "../../Databases/Products.db";
	DatabaseMgr & database = DatabaseMgr::Create(strDatabase.c_str(), DatabaseMgr::QSQLITE);

	ref_ptr < Plate3D > pPlate3D =  new Plate3D;
	string strCommand = pPlate3D->getSQLCommand();

	database.fillPrimitiveTable(strCommand);
}

//--------------------------------------------------------------


//====================================================

int main(int argc, char *argv[])	{
	QApplication app(argc,argv);

	int nSelection = 7;
	switch (nSelection)	{
	case 1: createTable();
		break;
	case 2: populateTable();
		break;
	case 3: main_InsertIntoDatabase_Sphere();
		break;
	case 4: main_InsertIntoDatabase_Cylinder();;
		break;
	case 5: main_InsertIntoDatabase_Parallelepiped();
		break;
	default:	{
		printError("Error Message: Wrong test number set.");
		exit(-1);
				}
	}
	return(0);
}