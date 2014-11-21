#include <fstream>

#include "VRPlate3D.h"

#include "BasicStringDefinitions.h"

#include "VRContainer.h"

using namespace std;
using namespace osg;
using namespace VR;

ContainerParams::ContainerParams() : FurnitureParams(),
	m_flWidth(2.0),
	m_flHeight(3.0),
	m_flDepth(1.5),
	m_flThickness(0.01)	{
}

//=======================================================================

Container::Container(const ContainerParams & aContainerParams) : Furniture(aContainerParams)	{
	setParams(aContainerParams);

	setName("Container_"+tostr(getAbstractObjectNo()));
}

//-----------------------------------------------------------------------

Container::Container(const Container& cont,const osg::CopyOp& copyop) :
VR::Furniture(cont, copyop)	{
	ContainerParams aCont;
	cont.getParams(aCont);
	setParams(aCont);

	setName("Container_"+tostr(getAbstractObjectNo()));
}

//-----------------------------------------------------------------------

const char* Container::className() const	{
	return "Container";
}

//-----------------------------------------------------------------------

Object* Container::cloneType() const	{
	ContainerParams aCont;

	return new Container(aCont);
}

//-----------------------------------------------------------------------

Object* Container::clone(const CopyOp& copyop) const	{
	return new Container(*this,copyop);
}

//-----------------------------------------------------------------------

void Container::init(const ContainerParams & aContainerParams)	{

	setParams(aContainerParams);

	/*
	const ContainerParams & cP = dynamic_cast<const ContainerParams&>(aContainerParams);

	setScaling(cP.m_flLenX, cP.m_flLenY, cP.m_flLenZ);
	setRotation(cP.m_flAngleYZ, cP.m_flAngleXZ, cP.m_flAngleXY);
	setPosition(cP.m_flPosX, cP.m_flPosY, cP.m_flPosZ);
	*/
	
	Matrix containerMatrix = calculateMatrix();
	setMatrix(containerMatrix);
}

//-----------------------------------------------------------------------

string Container::getSQLCommand() const {
	ContainerParams containerParams;
	getParams(containerParams);

	string strContainerParams;
	strContainerParams = to_string((long double)containerParams.m_flPosX) + "_";
	strContainerParams += to_string((long double)containerParams.m_flPosY) + "_";
	strContainerParams += to_string((long double)containerParams.m_flPosZ) + "_";

	strContainerParams += to_string((long double)containerParams.m_flLenX) + "_";
	strContainerParams += to_string((long double)containerParams.m_flLenY) + "_";
	strContainerParams += to_string((long double)containerParams.m_flLenZ) + "_";

	strContainerParams += to_string((long double)containerParams.m_flAngleYZ) + "_";
	strContainerParams += to_string((long double)containerParams.m_flAngleXZ) + "_";
	strContainerParams += to_string((long double)containerParams.m_flAngleXY);

	string strSQLCommand = "INSERT INTO EquipmentItem (EquipmentItemName, EquipmentItemParams, EquipmentID) "
		"VALUES ('Container', '" + strContainerParams + "', (SELECT EquipmentID FROM Equipment WHERE EquipmentName = 'Furniture'));";

	vector < string >::const_iterator it = m_arrSQLCommandLines.begin();
	for (it; it != m_arrSQLCommandLines.end(); it++)	{
		strSQLCommand += *it;
	}

	return(strSQLCommand);
}

//-----------------------------------------------------------------------

void Container::initFromSQLData(const string & astrSQLData)	{
	ContainerParams containerParams;

	string strSQLData = astrSQLData;
	string strDelimiter = "?";
	
	vector < string > arrstrSQLData = splitString(strSQLData,strDelimiter);
	vector <string> arrstrContainerParams = splitString(arrstrSQLData[0],"_");

	int nI;
	vector < float > arrflMatrix;
	for (nI=0;nI<9;nI++)	{
		arrflMatrix.push_back(stof(arrstrContainerParams[nI]));
	}

	containerParams.m_flPosX = arrflMatrix[0];
	containerParams.m_flPosY = arrflMatrix[1];
	containerParams.m_flPosZ = arrflMatrix[2];

	containerParams.m_flLenX = arrflMatrix[3];
	containerParams.m_flLenY = arrflMatrix[4];
	containerParams.m_flLenZ = arrflMatrix[5];

	containerParams.m_flAngleYZ = arrflMatrix[6];
	containerParams.m_flAngleXZ = arrflMatrix[7];
	containerParams.m_flAngleXY = arrflMatrix[8];

	for (auto it = arrstrSQLData.begin()+1; it != arrstrSQLData.end()-1; it++)	{
		Plate3DParams plate3DParams;
		ref_ptr < Plate3D > pPlate = new Plate3D(plate3DParams);
		pPlate->initFromSQLData(*it);
		addChild(pPlate);
	}
	init(containerParams);
}

//-----------------------------------------------------------------------

void Container::predefinedObject()	{
	ContainerParams containerParams;

	ref_ptr < Plate3D > pPlate3D;
	Plate3DParams aPlate3DParams;
	//Bottom plate
	aPlate3DParams.m_flLenX = containerParams.m_flWidth;
	aPlate3DParams.m_flLenY = containerParams.m_flDepth;
	aPlate3DParams.m_flLenZ = containerParams.m_flThickness;

	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = containerParams.m_flThickness/2;

	aPlate3DParams.m_arrflRGBA[0] = 0.85;
	aPlate3DParams.m_arrflRGBA[1] = 0.0;
	aPlate3DParams.m_arrflRGBA[2] = 0.85;
	aPlate3DParams.m_arrflRGBA[3] = 1;

	pPlate3D = new Plate3D(aPlate3DParams);
	addPart(pPlate3D);

	//Left plate
	aPlate3DParams.m_flLenX = containerParams.m_flThickness;
	aPlate3DParams.m_flLenY = containerParams.m_flDepth;
	aPlate3DParams.m_flLenZ = containerParams.m_flHeight;
	aPlate3DParams.m_flPosX = (-containerParams.m_flWidth+containerParams.m_flThickness)/2;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = containerParams.m_flHeight/2;

	pPlate3D = new Plate3D(aPlate3DParams);
	addPart(pPlate3D);

	//Right plate
	aPlate3DParams.m_flLenX = containerParams.m_flThickness;
	aPlate3DParams.m_flLenY = containerParams.m_flDepth;
	aPlate3DParams.m_flLenZ = containerParams.m_flHeight;
	aPlate3DParams.m_flPosX = (containerParams.m_flWidth-containerParams.m_flThickness)/2;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = containerParams.m_flHeight/2;

	pPlate3D = new Plate3D(aPlate3DParams);
	addPart(pPlate3D);

	//Front plate
	aPlate3DParams.m_flLenX = containerParams.m_flWidth;
	aPlate3DParams.m_flLenY = containerParams.m_flThickness;
	aPlate3DParams.m_flLenZ = containerParams.m_flHeight;
	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = (-containerParams.m_flDepth+containerParams.m_flThickness)/2;
	aPlate3DParams.m_flPosZ = containerParams.m_flHeight/2;

	pPlate3D = new Plate3D(aPlate3DParams);
	addPart(pPlate3D);

	//Back plate
	aPlate3DParams.m_flLenX = containerParams.m_flWidth;
	aPlate3DParams.m_flLenY = containerParams.m_flThickness;
	aPlate3DParams.m_flLenZ = containerParams.m_flHeight;
	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = (containerParams.m_flDepth-containerParams.m_flThickness)/2;
	aPlate3DParams.m_flPosZ = containerParams.m_flHeight/2;

	aPlate3DParams.m_strFileNameTexture = "../../Resources/Textures/lz.rgb";
	pPlate3D = new Plate3D(aPlate3DParams);
	addPart(pPlate3D);

	init(containerParams);
	setIsTargetPick(true);
}

//-----------------------------------------------------------------------

void Container::setParams(const ContainerParams & aContainerParams)	{
	Furniture::setParams(aContainerParams);

	m_flWidth = aContainerParams.m_flWidth;
	m_flHeight = aContainerParams.m_flHeight;
	m_flDepth = aContainerParams.m_flDepth;
	m_flThickness = aContainerParams.m_flThickness;
}

//-----------------------------------------------------------------------

void Container::getParams(ContainerParams & aContainerParams) const	{
	Furniture::getParams(aContainerParams);

	aContainerParams.m_flWidth = m_flWidth;
	aContainerParams.m_flHeight = m_flHeight;
	aContainerParams.m_flDepth = m_flDepth;
	aContainerParams.m_flThickness = m_flThickness;
}
