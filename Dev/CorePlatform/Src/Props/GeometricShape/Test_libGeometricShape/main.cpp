#include <string>

#include <QApplication>

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osg/TextureRectangle>
#include <osg/TexMat>


#include "VRUntransformedPlate2D.h"
#include "VRUntransformedPlate3D.h"
#include "VRUntransformedPolygon2D.h"
#include "VRUntransformedPolyhedron.h"
#include "VRUntransformedSphere.h"

#include "VRPlate3D.h"
#include "VRCylinder.h"
#include "VRSphere.h"


using namespace osg;
using namespace VR;
using namespace std;


//----------------------------------------------------------------------

void main_UntransformedPlate2D_Color(ref_ptr<Group> pScene)	{
	ref_ptr<UntransformedPlate2D> pUntransformedPlate2D = new UntransformedPlate2D();
	vector < float > arrflColor;
	arrflColor.push_back(0.80);
	arrflColor.push_back(0.80);
	arrflColor.push_back(0.10);
	arrflColor.push_back(1.0);
	pUntransformedPlate2D->setColor(arrflColor);
	pScene->addChild(pUntransformedPlate2D);
}

//----------------------------------------------------------------------

void main_UntransformedPlate3D(ref_ptr<Group> pScene)	{
	ref_ptr<UntransformedPlate3D> pUntransformedPlate3D = new UntransformedPlate3D();
	vector < float > arrflColor;
	arrflColor.push_back(0.80);
	arrflColor.push_back(0.80);
	arrflColor.push_back(0.10);
	arrflColor.push_back(1.0);

	pUntransformedPlate3D->setColor(arrflColor);
	pScene->addChild(pUntransformedPlate3D);
}

//----------------------------------------------------------------------

void main_UntransformedPolygon2D(ref_ptr<Group> pScene)	{
	ref_ptr<UntransformedPolygon2D> pUntransformedPolygon2D = new UntransformedPolygon2D(5);
	pScene->addChild(pUntransformedPolygon2D);
}

//=====================================================================

void main_Plate3D(ref_ptr<Group> pScene)	{
	Plate3DParams p3DP;
	p3DP.m_flLenX = 1.0;
	p3DP.m_flLenY = 2.0;
	p3DP.m_flLenZ = 4.0;
	p3DP.m_flPosX = 0.0;
	p3DP.m_flPosY = 0.0;
	p3DP.m_flPosZ = 0.0;

	p3DP.m_arrflRGBA[0] = 0.85;
	p3DP.m_arrflRGBA[1] = 0.85;
	p3DP.m_arrflRGBA[2] = 0.85;
	p3DP.m_arrflRGBA[3] = 1;

	ref_ptr<Plate3D> pPlate3D = new Plate3D(p3DP);
	
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
	arrflColor.push_back(0.80);
	arrflColor.push_back(0.80);
	arrflColor.push_back(0.10);
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

void main_UntransformedPolyhedron_Color(ref_ptr<Group> pScene)	{
	ref_ptr<UntransformedPolyhedron> pUntransformedPolyhedron = new UntransformedPolyhedron();
	pUntransformedPolyhedron->setResolution(10);
	vector < float > arrflColor;
	arrflColor.push_back(1.0);
	arrflColor.push_back(0.0);
	arrflColor.push_back(0.0);
	arrflColor.push_back(1.0);
	pUntransformedPolyhedron->setColor(arrflColor);
	pScene->addChild(pUntransformedPolyhedron);
}

//----------------------------------------------------------------------

void main_UntransformedPolyhedron_Texture(ref_ptr<Group> pScene)	{
	UntransformedPolyhedronParams uPP;
	ref_ptr<UntransformedPolyhedron> pUntransformedPolyhedron = new UntransformedPolyhedron(uPP);
	pUntransformedPolyhedron->setTexture("../../../../Resources/Textures/lz.rgb");

	pScene->addChild(pUntransformedPolyhedron);
}

//----------------------------------------------------------------------

void main_Cylinder(ref_ptr<Group> pScene)	{
	CylinderParams cP;
	cP.m_flRadius = 1.0;
	cP.m_flHeight = 3.0;
	cP.m_nResolution = 100;
	cP.m_flPosX = 0.0;
	cP.m_flPosY = 0.0;
	cP.m_flPosZ = 0.0;
	cP.m_flLenX = 1.0;
	cP.m_flLenY = 2.0;
	cP.m_flLenZ = 3.0;
	cP.m_arrflRGBA[0] = 0.85;
	cP.m_arrflRGBA[1] = 0.25;
	cP.m_arrflRGBA[2] = 0.15;
	cP.m_arrflRGBA[3] = 1.0;
	cP.m_strFileNameTexture = "../../../../Resources/Textures/lz.rgb";

	ref_ptr<VR::Cylinder> pCylinder = new VR::Cylinder(cP);
	pScene->addChild(pCylinder);
}

//----------------------------------------------------------------------

void main_Prism(ref_ptr<Group> pScene)	{
	PrismParams pP;
	pP.m_flRadius = 1.0;
	pP.m_flHeight = 1.0;
	pP.m_nResolution = 4;
	pP.m_flPosX = 0.0;
	pP.m_flPosY = 0.0;
	pP.m_flPosZ = 0.0;
	pP.m_arrflRGBA[0] = 0.85;
	pP.m_arrflRGBA[1] = 0.25;
	pP.m_arrflRGBA[2] = 0.15;
	pP.m_arrflRGBA[3] = 1.0;

	ref_ptr<VR::Prism> pPrism = new VR::Prism(pP);
	pScene->addChild(pPrism);
}

//----------------------------------------------------------------------

void main_Sphere_Color(ref_ptr<Group> pScene)	{
	SphereParams sP;
	sP.m_nResPhi = sP.m_nResTheta = 50;
	sP.m_flLenX = 1;
	sP.m_flLenY = 2;
	sP.m_flLenZ = 3;

	vector <float> arrflColor;
	arrflColor.push_back(0.85);
	arrflColor.push_back(0.15);
	arrflColor.push_back(0.25);
	arrflColor.push_back(1.0);
	sP.m_arrflRGBA = arrflColor;

	ref_ptr<VR::Sphere> pSphere = new VR::Sphere(sP);
	pScene->addChild(pSphere);
}

//----------------------------------------------------------------------

void main_UntransformedSphere_Texture(ref_ptr<Group> pScene)	{
	ref_ptr<UntransformedSphere> pUntransformedSphere = new UntransformedSphere();
	pUntransformedSphere->setTexture("../../../../Resources/Textures/lz.rgb");
	pScene->addChild(pUntransformedSphere);
}

//====================================================================

void initFromDB_Plate(ref_ptr<Group> pScene)	{
}

//--------------------------------------------------------------

void initFromDB_Sphere(ref_ptr<Group> pScene)	{
}

//--------------------------------------------------------------

void initFromDB_Prism(ref_ptr<Group> pScene)	{
}

//--------------------------------------------------------------

void initFromDB_Cylinder(ref_ptr<Group> pScene)	{
}


//====================================================================


int main(int argc, char * argv[])	{
	QApplication app(argc,argv);

	ref_ptr<Group> pScene = new Group;
	ref_ptr<Node> pAxes = osgDB::readNodeFile("../../../../Resources/Models3D/axes.osgt");
	pScene->addChild(pAxes);

	int nSelection = 11;
	switch (nSelection)	{
	case 1: main_UntransformedPlate2D_Color(pScene); break;
	case 2: main_UntransformedPlate2D_Texture(pScene); break;
	case 3: main_UntransformedPlate3D(pScene); break;
	case 4: main_UntransformedPlate3D_Color(pScene); break;
	case 5: main_UntransformedPlate3D_Texture(pScene); break;
	case 6: main_Plate3D(pScene); break;
	case 7: main_UntransformedPolygon2D(pScene); break;
	case 8: main_UntransformedPolygon2D_Color(pScene); break;
	case 9: main_UntransformedPolyhedron_Color(pScene); break;
	case 10: main_UntransformedPolyhedron_Texture(pScene); break;
	case 11: main_Cylinder(pScene); break;
	case 12: main_Prism(pScene); break;
	case 13: main_Sphere_Color(pScene); break;
	case 14: main_UntransformedSphere_Texture(pScene); break;

	case 15: initFromDB_Plate(pScene); break;
	case 16: initFromDB_Sphere(pScene); break;
	case 17: initFromDB_Prism(pScene); break;
	case 18: initFromDB_Cylinder(pScene); break;
	
	default:	{
		exit(-1);
				}
	}
	osgViewer::Viewer viewer;
	viewer.setSceneData(pScene);

	return viewer.run();
}