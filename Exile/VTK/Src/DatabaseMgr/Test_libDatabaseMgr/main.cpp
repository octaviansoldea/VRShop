#include <QApplication>
#include <iostream>
#include <string>

#include "DatabaseMgr.h"
#include "FunctorPathResource.h"

using namespace std;

void createAndPopulate1() {
//	FunctorPathResource f;
//
//	DatabaseMgr & database = DatabaseMgr::Create(f("Databases/Products.db").c_str(), DatabaseMgr::QSQLITE);
//	database.createTable();
//	const double arrdbLocationXYZ[3] = {1.1,1.1,1.1};
//	const double tbldbRotationMatrix[3][3] = {{1.1,1.2,1.4},{1,3,6},{9,4,4}};
//	const double arrdbScale[3] = {1,1,1};
//
//	vector < double > arrdbParameters;
//
//	arrdbParameters.resize(2);
//	//Width - x
//	arrdbParameters[0] = 100;
//	//Height Y
//	arrdbParameters[1] = 200;
//	database.insertPrimitive("Plate", 2, arrdbParameters);
//
//	//Radius
//	arrdbParameters[0] = 100;
//	//Height - on z
//	arrdbParameters[1] = 200;
//	database.insertPrimitive("Cylinder", 2, arrdbParameters);
//
//
//	arrdbParameters.resize(3);
//	//Width - x
//	arrdbParameters[0] = 100;
//	//Height - y
//	arrdbParameters[1] = 200;
//	//Dwpth - z
//	arrdbParameters[2] = 500;
//	database.insertPrimitive("RightParallelipiped", 3, arrdbParameters);
//
//	arrdbParameters.resize(1);
//	//Radius
//	arrdbParameters[0] = 100;
//	database.insertPrimitive("Sphere", 1, arrdbParameters);
//	
//	database.insertTexture("AJX", "C:/Projekti/VRShop/Dev/Resources/Textures/AJX.jpg");
//	database.insertTexture("WallTexture", "C:/Projekti/VRShop/Dev/Resources/Textures/WallTexture.jpg");
//	database.insertTexture("Aluminum", "C:/Projekti/VRShop/Dev/Resources/Textures/Aluminum.jpg");
//
//	const QString location[3] = {"0","0","0"};
//	const QString orientation[3] = {"0","0","0"};
////	database.insertItem("Product", "Food", "juice", "002","AJX.jpg", location, orientation);
//
//	delete (&database);
}

int main(int argc, char *argv[])	{
	QApplication app(argc,argv);

	createAndPopulate1();
	
	return(0);
}