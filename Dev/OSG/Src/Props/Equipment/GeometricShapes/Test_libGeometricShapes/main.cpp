#include <string>

#include <QApplication>

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osg/TextureRectangle>
#include <osg/TexMat>
#include <osg/ArgumentParser>

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


//--------------------------------------------------------------

void main_SelectFromDatabase_Sphere(ref_ptr<Group> pScene)	{
	string strDatabase = "../../../../Databases/Products.db";
	DatabaseMgr & database = DatabaseMgr::Create(strDatabase.c_str(), DatabaseMgr::QSQLITE);

	string strSQLString = database.getSQLData(1);
	ref_ptr < UntransformedSphere > pSphere =  new UntransformedSphere();
	pSphere->initFromSQLData(strSQLString);

	pScene->addChild(pSphere);
}


//----------------------------------------------------------------------

void main_UntransformedPlate2D_Color(ref_ptr<Group> pScene)	{
	ref_ptr<UntransformedPlate2D> pUntransformedPlate2D = new UntransformedPlate2D();
	float arrflColor[4] = {1.0, 0.0, 0.0, 1.0};
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
	const float arrflColor[4] = {0.0, 1.0, 0.0, 1.0};
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
	const float arrflColor[4] = {0.0, 1.0, 1.0, 1.0};
	pUntransformedPolygon2D->setColor(arrflColor);

	pScene->addChild(pUntransformedPolygon2D);
}

//----------------------------------------------------------------------

void main_UntransformedPolygon3D_Color(ref_ptr<Group> pScene)	{
	ref_ptr<UntransformedPolygon3D> pUntransformedPolygon3D = new UntransformedPolygon3D();
	pUntransformedPolygon3D->setResolution(10);
	float arrflColor[4] = {0.0, 1.0, 0.0, 1.0};
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
	float arrflColor[4] = {0.0, 1.0, 0.0, 1.0};
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

//====================================================================


int main(int argc, char * argv[])	{
	QApplication app(argc,argv);
	if(argc<3)	{
		printError("Error Message: Using too few arguments.");
		exit(-1);
	}

	ref_ptr<Group> pScene = new Group;
	if(argc>1)	{
		ref_ptr<Node> pAxes = osgDB::readNodeFile(argv[1]);
		pScene->addChild(pAxes);
	}

	ArgumentParser arguments(&argc, argv);
	while (arguments.read("--Test_1")) main_UntransformedPlate2D_Color(pScene);
	while (arguments.read("--Test_2")) main_UntransformedPlate2D_Texture(pScene);
	while (arguments.read("--Test_3")) main_UntransformedPlate3D(pScene);
	while (arguments.read("--Test_4")) main_UntransformedPlate3D_Color(pScene);
	while (arguments.read("--Test_5")) main_UntransformedPlate3D_Texture(pScene);
	while (arguments.read("--Test_6")) main_Plate3D(pScene);
	while (arguments.read("--Test_7")) main_Plate3D_DB(pScene);
	while (arguments.read("--Test_8")) main_UntransformedPolygon2D(pScene);
	while (arguments.read("--Test_9")) main_UntransformedPolygon2D_Color(pScene);
	while (arguments.read("--Test_10")) main_UntransformedPolygon3D_Color(pScene);
	while (arguments.read("--Test_11")) main_UntransformedPolygon3D_Texture(pScene);
	while (arguments.read("--Test_12")) main_Cylinder(pScene);
	while (arguments.read("--Test_13")) main_UntransformedSphere_Color(pScene);
	while (arguments.read("--Test_14")) main_UntransformedSphere_Texture(pScene);

	while (arguments.read("--Test_15")) main_SelectFromDatabase_Sphere(pScene);

	
	osgViewer::Viewer viewer;
	viewer.setSceneData(pScene);

	return viewer.run();
}
// argv{1} = ../../../../Resources/Models3D/axes.osgt