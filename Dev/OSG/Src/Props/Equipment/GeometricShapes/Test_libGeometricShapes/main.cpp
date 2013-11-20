#include <string>

#include <QApplication>

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osg/TextureRectangle>
#include <osg/TexMat>

#include "VRDatabaseMgr.h"

#include "VRUntransformedPlate2D.h"
#include "VRUntransformedPlate3D.h"
#include "VRUntransformedPolygon2D.h"
#include "VRUntransformedPolygon3D.h"
#include "VRPlate3D.h"
#include "VRCylinder.h"
#include "VRUntransformedSphere.h"


using namespace osg;
using namespace VR;
using namespace std;


//----------------------------------------------------------------------

void main_UntransformedPlate2D_Color(ref_ptr<Group> pScene)	{
	ref_ptr<UntransformedPlate2D> pUntransformedPlate2D = new UntransformedPlate2D();
	vector < float > arrflColor;
	arrflColor.push_back(1.0);
	arrflColor.push_back(0.0);
	arrflColor.push_back(0.0);
	arrflColor.push_back(1.0);
	pUntransformedPlate2D->setColor(arrflColor);
	pScene->addChild(pUntransformedPlate2D);
}

//----------------------------------------------------------------------

void main_UntransformedPlate3D(ref_ptr<Group> pScene)	{
	ref_ptr<UntransformedPlate3D> pUntransformedPlate3D = new UntransformedPlate3D();

	pScene->addChild(pUntransformedPlate3D);
}

//----------------------------------------------------------------------

void main_UntransformedPolygon2D(ref_ptr<Group> pScene)	{
	ref_ptr<UntransformedPolygon2D> pUntransformedPolygon2D = new UntransformedPolygon2D(5);
	pScene->addChild(pUntransformedPolygon2D);
}

//=====================================================================

void main_Plate3D(ref_ptr<Group> pScene)	{
	ref_ptr<Plate3D> pPlate3D = new Plate3D();

	Plate3DParams p3DP;
	p3DP.m_flLenX = 1.0;
	p3DP.m_flLenY = 2.0;
	p3DP.m_flLenZ = 4.0;
	p3DP.m_flPosX = 0.0;
	p3DP.m_flPosY = 0.0;
	p3DP.m_flPosZ = 8.0;
	pPlate3D->init(p3DP);

	pScene->addChild(pPlate3D);
}

//--------------------------------------------------------------------

void main_UntransformedPlate2D_Texture(ref_ptr<Group> pScene)
{
	ref_ptr<UntransformedPlate2D> pUntransformedPlate2D = new UntransformedPlate2D();
	
	pUntransformedPlate2D->setTexture("../../../../Resources/Textures/lz.rgb");

	pScene->addChild(pUntransformedPlate2D);
}

//--------------------------------------------------------------------

void main_UntransformedPlate3D_Color(ref_ptr<Group> pScene)
{
	ref_ptr<UntransformedPlate3D> pUntransformedPlate3D = new UntransformedPlate3D();
	vector < float > arrflColor;
	arrflColor.push_back(1.0);
	arrflColor.push_back(0.0);
	arrflColor.push_back(0.0);
	arrflColor.push_back(1.0);
	pUntransformedPlate3D->setColor(arrflColor);

	pScene->addChild(pUntransformedPlate3D);
}

//--------------------------------------------------------------------

void main_UntransformedPlate3D_Texture(ref_ptr<Group> pScene)
{
	ref_ptr<UntransformedPlate3D> pUntransformedPlate3D = new UntransformedPlate3D();
	
	pUntransformedPlate3D->setTexture("../../../../Resources/Textures/lz.rgb");

	pScene->addChild(pUntransformedPlate3D);
}

//--------------------------------------------------------------------

void main_UntransformedPolygon2D_Color(ref_ptr<Group> pScene)
{
	ref_ptr<UntransformedPolygon2D> pUntransformedPolygon2D = new UntransformedPolygon2D(10);
	vector < float > arrflColor;
	arrflColor.push_back(1.0);
	arrflColor.push_back(0.0);
	arrflColor.push_back(0.0);
	arrflColor.push_back(1.0);
	pUntransformedPolygon2D->setColor(arrflColor);

	pScene->addChild(pUntransformedPolygon2D);
}

//----------------------------------------------------------------------

void main_UntransformedPolygon3D_Color(ref_ptr<Group> pScene)	{
	ref_ptr<UntransformedPolygon3D> pUntransformedPolygon3D = new UntransformedPolygon3D();
	pUntransformedPolygon3D->setResolution(10);
	vector < float > arrflColor;
	arrflColor.push_back(1.0);
	arrflColor.push_back(0.0);
	arrflColor.push_back(0.0);
	arrflColor.push_back(1.0);
	pUntransformedPolygon3D->setColor(arrflColor);
	pScene->addChild(pUntransformedPolygon3D);
}

//----------------------------------------------------------------------

void main_UntransformedPolygon3D_Texture(ref_ptr<Group> pScene)	{
	ref_ptr<UntransformedPolygon3D> pUntransformedPolygon3D = new UntransformedPolygon3D();

	pUntransformedPolygon3D->setTexture("../../../../Resources/Textures/lz.rgb");

	pScene->addChild(pUntransformedPolygon3D);
}

//----------------------------------------------------------------------

void main_Cylinder(ref_ptr<Group> pScene)	{
	CylinderParams cylinderP;
	cylinderP.m_flRadius = 1.0;
	cylinderP.m_flHeight = 3.0;
	cylinderP.m_nRes = 50;
	cylinderP.m_flPosX = 0.0;
	cylinderP.m_flPosY = 0.0;
	cylinderP.m_flPosZ = 0.0;
	cylinderP.m_arrflRGBA[0] = 0.85;
	cylinderP.m_arrflRGBA[1] = 0.25;
	cylinderP.m_arrflRGBA[2] = 0.15;
	cylinderP.m_arrflRGBA[3] = 1.0;

	ref_ptr<VR::Cylinder> pCylinder = new VR::Cylinder(cylinderP);

	pScene->addChild(pCylinder);
}

//----------------------------------------------------------------------

void main_UntransformedSphere_Color(ref_ptr<Group> pScene)	{
	SphereParams sP;
	ref_ptr<UntransformedSphere> pUntransformedSphere = new UntransformedSphere;
	vector < float > arrflColor;
	arrflColor.push_back(1.0);
	arrflColor.push_back(0.0);
	arrflColor.push_back(0.0);
	arrflColor.push_back(1.0);
	pUntransformedSphere->setColor(arrflColor);
	sP.m_nResPhi = sP.m_nResTheta = 50;
	pUntransformedSphere = new UntransformedSphere(sP);
	pScene->addChild(pUntransformedSphere);
}

//----------------------------------------------------------------------

void main_UntransformedSphere_Texture(ref_ptr<Group> pScene)	{
	ref_ptr<UntransformedSphere> pUntransformedSphere = new UntransformedSphere();
	pUntransformedSphere->setTexture("../../../../Resources/Textures/lz.rgb");
	pScene->addChild(pUntransformedSphere);
}

//====================================================================

void main_Plate3D_DB(ref_ptr<Group> pScene)	{
	string strDatabase = "../../../../Databases/Products.db";
	DatabaseMgr & database = DatabaseMgr::Create(strDatabase.c_str(), DatabaseMgr::QSQLITE);

	vector < float > arrdbParameters = database.selectFromDatabase(2);

	ref_ptr<Plate3D> pPlate3D = new Plate3D();

	Plate3DParams p3DP;
	p3DP.m_flLenX = arrdbParameters[0];
	p3DP.m_flLenY = arrdbParameters[1];
	p3DP.m_flLenZ = arrdbParameters[2];

	pPlate3D->init(p3DP);

	pScene->addChild(pPlate3D);
}

//--------------------------------------------------------------

void initFromDB_Plate(ref_ptr<Group> pScene)	{
	string strDatabase = "../../../../Databases/Equipment.db";
	DatabaseMgr & database = DatabaseMgr::Create(strDatabase.c_str(), DatabaseMgr::QSQLITE);

	ref_ptr < Plate3D > pPlate3D;
	string strSQLQuery = "SELECT * FROM Plate3D WHERE Plate3DID = 1";
	string strSQLData = database.readFromDB(strSQLQuery);
	pPlate3D = new Plate3D();
	pPlate3D->initFromSQLData(strSQLData);

	pScene->addChild(pPlate3D);
}

//--------------------------------------------------------------

void initFromDB_Sphere(ref_ptr<Group> pScene)	{
	string strDatabase = "../../../../Databases/Equipment.db";
	DatabaseMgr & database = DatabaseMgr::Create(strDatabase.c_str(), DatabaseMgr::QSQLITE);

	ref_ptr < UntransformedSphere > pSphere;
	string strSQLQuery = "SELECT * FROM Sphere WHERE SphereID = 1";
	string strSQLData = database.readFromDB(strSQLQuery);
	pSphere = new UntransformedSphere();
	pSphere->initFromSQLData(strSQLData);

	pScene->addChild(pSphere);
}

//--------------------------------------------------------------

void initFromDB_Prism(ref_ptr<Group> pScene)	{
	string strDatabase = "../../../../Databases/Equipment.db";
	DatabaseMgr & database = DatabaseMgr::Create(strDatabase.c_str(), DatabaseMgr::QSQLITE);

	ref_ptr < Prism > pPrism;
	string strSQLQuery = "SELECT * FROM Prism WHERE PrismID = 1";
	string strSQLData = database.readFromDB(strSQLQuery);
	pPrism = new Prism();
	pPrism->initFromSQLData(strSQLData);

	pScene->addChild(pPrism);
}

//--------------------------------------------------------------

void initFromDB_Cylinder(ref_ptr<Group> pScene)	{
	string strDatabase = "../../../../Databases/Equipment.db";
	DatabaseMgr & database = DatabaseMgr::Create(strDatabase.c_str(), DatabaseMgr::QSQLITE);

	ref_ptr < VR::Cylinder > pCylinder;
	string strSQLQuery = "SELECT * FROM Cylinder WHERE CylinderID = 1";
	string strSQLData = database.readFromDB(strSQLQuery);
	pCylinder = new VR::Cylinder();
	pCylinder->initFromSQLData(strSQLData);

	pScene->addChild(pCylinder);
}


//====================================================================


int main(int argc, char * argv[])	{
	QApplication app(argc,argv);

	ref_ptr<Group> pScene = new Group;
	ref_ptr<Node> pAxes = osgDB::readNodeFile("../../../../Resources/Models3D/axes.osgt");
	pScene->addChild(pAxes);

	int nSelection = 18;
	switch (nSelection)	{
	case 1: main_UntransformedPlate2D_Color(pScene); break;
	case 2: main_UntransformedPlate2D_Texture(pScene); break;
	case 3: main_UntransformedPlate3D(pScene); break;
	case 4: main_UntransformedPlate3D_Color(pScene); break;
	case 5: main_UntransformedPlate3D_Texture(pScene); break;
	case 6: main_Plate3D(pScene); break;
	case 7: main_Plate3D_DB(pScene); break;
	case 8: main_UntransformedPolygon2D(pScene); break;
	case 9: main_UntransformedPolygon2D_Color(pScene); break;
	case 10: main_UntransformedPolygon3D_Color(pScene); break;
	case 11: main_UntransformedPolygon3D_Texture(pScene); break;
	case 12: main_Cylinder(pScene); break;
	case 13: main_UntransformedSphere_Color(pScene); break;
	case 14: main_UntransformedSphere_Texture(pScene); break;

	case 15: initFromDB_Plate(pScene); break;
	case 16: initFromDB_Sphere(pScene); break;
	case 17: initFromDB_Prism(pScene); break;
	case 18: initFromDB_Cylinder(pScene); break;
	
	default:	{
		printError("Error Message: Wrong test number set.");
		exit(-1);
				}
	}
	osgViewer::Viewer viewer;
	viewer.setSceneData(pScene);

	return viewer.run();
}