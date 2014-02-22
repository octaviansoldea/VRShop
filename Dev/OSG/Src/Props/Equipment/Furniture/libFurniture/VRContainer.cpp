#include "VRPlate3D.h"

#include "StringManipulation.h"

#include "VRContainer.h"

using namespace std;
using namespace osg;
using namespace VR;

ContainerParams::ContainerParams() : 
	m_flWidth(2.0),
	m_flHeight(3.0),
	m_flDepth(1.5),
	m_flThickness(0.01)	{
}

//=======================================================================

Container::Container()	{
	const ContainerParams aContainerParams;
}

//-----------------------------------------------------------------------

Container::Container(const ContainerParams & aContainerParams) : Furniture(aContainerParams)	{
	m_ContainerParams = aContainerParams;
}

//-----------------------------------------------------------------------

void Container::init(const FurnitureParams & aFurnitureParams)	{
	m_ContainerParams = static_cast<const ContainerParams&>(aFurnitureParams);

	setScaling(m_ContainerParams.m_flLenX, m_ContainerParams.m_flLenY, m_ContainerParams.m_flLenZ);
	setRotation(m_ContainerParams.m_flAngleXY, m_ContainerParams.m_flAngleXZ, m_ContainerParams.m_flAngleYZ);
	setPosition(m_ContainerParams.m_flPosX, m_ContainerParams.m_flPosY, m_ContainerParams.m_flPosZ);

	Matrix matrix;
	matrix.set(1, 0, 0, 0,
			   0, 1, 0, 0,
			   0, 0, 1, 0,
			   0, 0, 0,	1);

	Matrix containerMatrix =
		matrix.scale(m_AbstractObjectParams.m_flLenX, m_AbstractObjectParams.m_flLenY, m_AbstractObjectParams.m_flLenZ)
		*
		matrix.rotate(
			m_AbstractObjectParams.m_flAngleYZ, osg::X_AXIS,
			m_AbstractObjectParams.m_flAngleXZ, osg::Y_AXIS,
			m_AbstractObjectParams.m_flAngleXY, osg::Z_AXIS)
		*
		matrix.translate(m_AbstractObjectParams.m_flPosX, m_AbstractObjectParams.m_flPosY, m_AbstractObjectParams.m_flPosZ)
	;
	
	setMatrix(containerMatrix);

	setName(Furniture::getName() + ":Container");
}

//-----------------------------------------------------------------------

string Container::getSQLCommand() const {
	string strContainerParams;
	strContainerParams = to_string((long double)m_ContainerParams.m_flPosX) + "_";
	strContainerParams += to_string((long double)m_ContainerParams.m_flPosY) + "_";
	strContainerParams += to_string((long double)m_ContainerParams.m_flPosZ) + "_";
	   											   
	strContainerParams += to_string((long double)m_ContainerParams.m_flLenX) + "_";
	strContainerParams += to_string((long double)m_ContainerParams.m_flLenY) + "_";
	strContainerParams += to_string((long double)m_ContainerParams.m_flLenZ) + "_";
	   											   
	strContainerParams += to_string((long double)m_ContainerParams.m_flAngleXY) + "_";
	strContainerParams += to_string((long double)m_ContainerParams.m_flAngleXZ) + "_";
	strContainerParams += to_string((long double)m_ContainerParams.m_flAngleYZ);

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
	string strSQLData = astrSQLData;
	string strDelimiter = "?";
	
	vector < string > arrstrSQLData = splitString(strSQLData,strDelimiter);
	vector <string> arrstrContainerParams = splitString(arrstrSQLData[0],"_");

	int nI;
	vector < float > arrflMatrix;
	for (nI=0;nI<9;nI++)	{
		arrflMatrix.push_back(stof(arrstrContainerParams[nI]));
	}

	m_ContainerParams.m_flPosX = arrflMatrix[0];
	m_ContainerParams.m_flPosY = arrflMatrix[1];
	m_ContainerParams.m_flPosZ = arrflMatrix[2];
	  
	m_ContainerParams.m_flLenX = arrflMatrix[3];
	m_ContainerParams.m_flLenY = arrflMatrix[4];
	m_ContainerParams.m_flLenZ = arrflMatrix[5];
	  
	m_ContainerParams.m_flAngleXY = arrflMatrix[6];
	m_ContainerParams.m_flAngleXZ = arrflMatrix[7];
	m_ContainerParams.m_flAngleYZ = arrflMatrix[8];

	for (auto it = arrstrSQLData.begin()+1; it != arrstrSQLData.end()-1; it++)	{
		ref_ptr < Plate3D > pPlate = new Plate3D;
		pPlate->initFromSQLData(*it);
		addChild(pPlate);
	}
	init(m_ContainerParams);
}

//-----------------------------------------------------------------------

void Container::predefinedObject()	{
	ref_ptr < Plate3D > pPlate3D = new Plate3D;
	Plate3DParams aPlate3DParams;
	//Bottom plate
	aPlate3DParams.m_flLenX = m_ContainerParams.m_flWidth;
	aPlate3DParams.m_flLenY = m_ContainerParams.m_flDepth;
	aPlate3DParams.m_flLenZ = m_ContainerParams.m_flThickness;

	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = m_ContainerParams.m_flThickness/2;

	aPlate3DParams.m_arrflRGBA[0] = 0.85;
	aPlate3DParams.m_arrflRGBA[1] = 0.0;
	aPlate3DParams.m_arrflRGBA[2] = 0.85;
	aPlate3DParams.m_arrflRGBA[3] = 1;

	pPlate3D->init(aPlate3DParams);
	addPart(pPlate3D);

	//Left plate
	pPlate3D = new Plate3D;
	
	aPlate3DParams.m_flLenX = m_ContainerParams.m_flThickness;
	aPlate3DParams.m_flLenY = m_ContainerParams.m_flDepth;
	aPlate3DParams.m_flLenZ = m_ContainerParams.m_flHeight;
	aPlate3DParams.m_flPosX = (-m_ContainerParams.m_flWidth+m_ContainerParams.m_flThickness)/2;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = m_ContainerParams.m_flHeight/2;

	pPlate3D->init(aPlate3DParams);
	addPart(pPlate3D);

	//Right plate
	pPlate3D = new Plate3D;

	aPlate3DParams.m_flLenX = m_ContainerParams.m_flThickness;
	aPlate3DParams.m_flLenY = m_ContainerParams.m_flDepth;
	aPlate3DParams.m_flLenZ = m_ContainerParams.m_flHeight;
	aPlate3DParams.m_flPosX = (m_ContainerParams.m_flWidth-m_ContainerParams.m_flThickness)/2;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = m_ContainerParams.m_flHeight/2;

	pPlate3D->init(aPlate3DParams);
	addPart(pPlate3D);

	//Front plate
	pPlate3D =  new Plate3D;

	aPlate3DParams.m_flLenX = m_ContainerParams.m_flWidth;
	aPlate3DParams.m_flLenY = m_ContainerParams.m_flThickness;
	aPlate3DParams.m_flLenZ = m_ContainerParams.m_flHeight;
	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = (-m_ContainerParams.m_flDepth+m_ContainerParams.m_flThickness)/2;
	aPlate3DParams.m_flPosZ = m_ContainerParams.m_flHeight/2;

	pPlate3D->init(aPlate3DParams);
	addPart(pPlate3D);

	//Back plate
	pPlate3D = new Plate3D;

	aPlate3DParams.m_flLenX = m_ContainerParams.m_flWidth;
	aPlate3DParams.m_flLenY = m_ContainerParams.m_flThickness;
	aPlate3DParams.m_flLenZ = m_ContainerParams.m_flHeight;
	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = (m_ContainerParams.m_flDepth-m_ContainerParams.m_flThickness)/2;
	aPlate3DParams.m_flPosZ = m_ContainerParams.m_flHeight/2;

	aPlate3DParams.m_strFileNameTexture = "../../Resources/Textures/lz.rgb";
	pPlate3D->init(aPlate3DParams);
	addPart(pPlate3D);

	init(m_ContainerParams);
	setIsTargetPick(true);
}