  #include <iostream>
  #include <string>
  
    #include <QApplication>
    #include <QMessageBox>
    #include <QFile>
    #include <QTextStream>
    
    #include <osgViewer/Viewer>
    #include <osgDB/ReadFile>
    
    #include <osg/DisplaySettings>
    
  #include "BasicStringDefinitions.h"
  
  #include "VRAppData.h"
  
    #include "VRAbstractObject.h"
    #include "VRAbstractGeomShape.h"
    
    
    
    #include "VRUntransformedPlate2D.h"
    #include "VRUntransformedPlate3D.h"
    #include "VRUntransformedPolygon2D.h"
    #include "VRUntransformedPolyhedron.h"
    #include "VRUntransformedSphere.h"
    #include "VRPlate3D.h"
    #include "VRCylinder.h"
    #include "VRSphere.h"
    
    #include "VRFurniture.h"
    #include "VRCupboard.h"
    #include "VRContainer.h"
    
    using namespace osg;
    using namespace std;
    using namespace VR;
    
    
    void createTable(const string & astrDBName) {
    }
    
    //--------------------------------------------------------------
    
    void populateTable(const string & astrDBName)	{
    }
    
    //--------------------------------------------------------------
    
    void insertIntoDatabase_Sphere(const string & astrDBName)	{
    }
    
    //--------------------------------------------------------------
    
    void insertIntoDatabase_Cylinder(const string & astrDBName)	{
    }
    
    //--------------------------------------------------------------
    
    void insertIntoDatabase_Plate3D(const string & astrDBName)	{
    }
    
    //--------------------------------------------------------------
    
    
    void insertIntoDatabase_Container(const string & astrDBName)	{
    }
    
    //--------------------------------------------------------------
    
    void insertIntoDatabase_Cupboard(const string & astrDBName)	{
    }
    
    //====================================================
    
    int main1(int argc, char *argv[])	{
    	QApplication app(argc,argv);
    
    	ref_ptr<Group> pScene = new Group;
  	ref_ptr<Node> pAxes = osgDB::readNodeFile(AppData::getFPathResources() +"/Models3D/axes.osgt");
    	pScene->addChild(pAxes);
    
    	string strDBName;
    	
  	strDBName = AppData::getFPathDatabases() +"/Equipment.db";
    	createTable(strDBName);
    	populateTable(strDBName);
    
    	insertIntoDatabase_Sphere(strDBName);
    	insertIntoDatabase_Cylinder(strDBName);
    	insertIntoDatabase_Plate3D(strDBName);
    
    	insertIntoDatabase_Container(strDBName);
    	insertIntoDatabase_Cupboard(strDBName);
    
    	Furniture::loadAllFurnitures(pScene, strDBName);
    
    	osgViewer::Viewer viewer;
    	viewer.setSceneData(pScene);
    
    	return viewer.run();
    }
    
    //--------------------------------------------------------------------------------------
    
    int main2(int argc, char * argv[])	{
    	QApplication app(argc,argv);
    
    	ref_ptr<Group> pScene = new Group;
	ref_ptr<Node> pAxes = osgDB::readNodeFile(AppData::getFPathResources() + "/Models3D/axes.osgt");
    	pScene->addChild(pAxes);
    
    	ContainerParams cParams;
    	ref_ptr < Container > pContainer = new Container(cParams);
    	pContainer->predefinedObject();
    	pContainer->removePart(3);
    	ref_ptr<AbstractObject> pChild = dynamic_cast<AbstractObject*>(pContainer->getChild(3));
    	pContainer->removePart(pChild);
    
    	//vector <ref_ptr<AbstractObject> > arrpChildren;
    	//pContainer->splitObject2Children(arrpChildren);
    
    	//vector <ref_ptr<AbstractObject> >::iterator it;
    	//for (it=arrpChildren.begin();it != arrpChildren.end();it++)	{
    	//	pScene->addChild(static_cast<ref_ptr<AbstractObject>>(*it));
    	//}
    
    	osgViewer::Viewer viewer;
    	viewer.setSceneData(pScene);
    
    	return viewer.run();
    }
    
    //----------------------------------------------------------------------------------------
    
    int main3(int argc, char * argv[])	{
    	QApplication app(argc,argv);
    
    	ref_ptr<Group> pScene = new Group;
	ref_ptr<Node> pAxes = osgDB::readNodeFile(AppData::getFPathResources() + "/Models3D/axes.osgt");
    	pScene->addChild(pAxes);
    
    	ContainerParams cParams;
    	ref_ptr < Container > pContainer = new Container(cParams);
    	pContainer->predefinedObject();
    	pScene->addChild(pContainer);
    
    	osgViewer::Viewer viewer;
    	viewer.setSceneData(pScene);
    
    	return viewer.run();
    }
    
    //======================================================================
    
    int main(int argc, char * argv[])	{
    	main1(argc, argv);
    //	main2(argc, argv);
    //	main3(argc, argv);
    
    	return (0);
    }

