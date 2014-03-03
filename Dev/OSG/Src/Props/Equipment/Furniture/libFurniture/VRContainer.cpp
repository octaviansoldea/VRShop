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

Container::Container() : Furniture(new ContainerParams())	{
	ContainerParams * pContainerParams = dynamic_cast<ContainerParams*>(m_pAbstractObjectParams);
	init(pContainerParams);
}

//-----------------------------------------------------------------------

Container::Container(ContainerParams * apContainerParams) : Furniture(apContainerParams)	{
	ContainerParams * pContainerParams = dynamic_cast<ContainerParams*>(m_pAbstractObjectParams);
	init(pContainerParams);
}

//-----------------------------------------------------------------------

const char* Container::className() const	{
	return "Container";
}

//-----------------------------------------------------------------------

void Container::init(FurnitureParams * apFurnitureParams)	{
	apFurnitureParams = dynamic_cast<FurnitureParams*>(m_pAbstractObjectParams);

	setScaling(apFurnitureParams->m_flLenX, apFurnitureParams->m_flLenY, apFurnitureParams->m_flLenZ);
	setRotation(apFurnitureParams->m_flAngleYZ, apFurnitureParams->m_flAngleXZ, apFurnitureParams->m_flAngleXY);
	setPosition(apFurnitureParams->m_flPosX, apFurnitureParams->m_flPosY, apFurnitureParams->m_flPosZ);
	
	Matrix & containerMatrix = calculateMatrix();
	setMatrix(containerMatrix);

	setName("Container");
}

//-----------------------------------------------------------------------

string Container::getSQLCommand() const {
	ContainerParams * pContainerParams = dynamic_cast<ContainerParams*>(m_pAbstractObjectParams);

	string strContainerParams;
	strContainerParams = to_string((long double)pContainerParams->m_flPosX) + "_";
	strContainerParams += to_string((long double)pContainerParams->m_flPosY) + "_";
	strContainerParams += to_string((long double)pContainerParams->m_flPosZ) + "_";

	strContainerParams += to_string((long double)pContainerParams->m_flLenX) + "_";
	strContainerParams += to_string((long double)pContainerParams->m_flLenY) + "_";
	strContainerParams += to_string((long double)pContainerParams->m_flLenZ) + "_";

	strContainerParams += to_string((long double)pContainerParams->m_flAngleXY) + "_";
	strContainerParams += to_string((long double)pContainerParams->m_flAngleXZ) + "_";
	strContainerParams += to_string((long double)pContainerParams->m_flAngleYZ);

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
	ContainerParams * pContainerParams = dynamic_cast<ContainerParams*>(m_pAbstractObjectParams);

	string strSQLData = astrSQLData;
	string strDelimiter = "?";
	
	vector < string > arrstrSQLData = splitString(strSQLData,strDelimiter);
	vector <string> arrstrContainerParams = splitString(arrstrSQLData[0],"_");

	int nI;
	vector < float > arrflMatrix;
	for (nI=0;nI<9;nI++)	{
		arrflMatrix.push_back(stof(arrstrContainerParams[nI]));
	}

	pContainerParams->m_flPosX = arrflMatrix[0];
	pContainerParams->m_flPosY = arrflMatrix[1];
	pContainerParams->m_flPosZ = arrflMatrix[2];

	pContainerParams->m_flLenX = arrflMatrix[3];
	pContainerParams->m_flLenY = arrflMatrix[4];
	pContainerParams->m_flLenZ = arrflMatrix[5];

	pContainerParams->m_flAngleXY = arrflMatrix[6];
	pContainerParams->m_flAngleXZ = arrflMatrix[7];
	pContainerParams->m_flAngleYZ = arrflMatrix[8];

	for (auto it = arrstrSQLData.begin()+1; it != arrstrSQLData.end()-1; it++)	{
		ref_ptr < Plate3D > pPlate = new Plate3D;
		pPlate->initFromSQLData(*it);
		addChild(pPlate);
	}
	init(pContainerParams);
}

//-----------------------------------------------------------------------

void Container::predefinedObject()	{
	ContainerParams * pContainerParams = dynamic_cast<ContainerParams*>(m_pAbstractObjectParams);

	ref_ptr < Plate3D > pPlate3D = new Plate3D;
	Plate3DParams aPlate3DParams;
	//Bottom plate
	aPlate3DParams.m_flLenX = pContainerParams->m_flWidth;
	aPlate3DParams.m_flLenY = pContainerParams->m_flDepth;
	aPlate3DParams.m_flLenZ = pContainerParams->m_flThickness;

	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = pContainerParams->m_flThickness/2;

	aPlate3DParams.m_arrflRGBA[0] = 0.85;
	aPlate3DParams.m_arrflRGBA[1] = 0.0;
	aPlate3DParams.m_arrflRGBA[2] = 0.85;
	aPlate3DParams.m_arrflRGBA[3] = 1;

	pPlate3D->init(aPlate3DParams);
	addPart(pPlate3D);

	//Left plate
	pPlate3D = new Plate3D;

	aPlate3DParams.m_flLenX = pContainerParams->m_flThickness;
	aPlate3DParams.m_flLenY = pContainerParams->m_flDepth;
	aPlate3DParams.m_flLenZ = pContainerParams->m_flHeight;
	aPlate3DParams.m_flPosX = (-pContainerParams->m_flWidth+pContainerParams->m_flThickness)/2;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = pContainerParams->m_flHeight/2;

	pPlate3D->init(aPlate3DParams);
	addPart(pPlate3D);

	//Right plate
	pPlate3D = new Plate3D;

	aPlate3DParams.m_flLenX = pContainerParams->m_flThickness;
	aPlate3DParams.m_flLenY = pContainerParams->m_flDepth;
	aPlate3DParams.m_flLenZ = pContainerParams->m_flHeight;
	aPlate3DParams.m_flPosX = (pContainerParams->m_flWidth-pContainerParams->m_flThickness)/2;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = pContainerParams->m_flHeight/2;

	pPlate3D->init(aPlate3DParams);
	addPart(pPlate3D);

	//Front plate
	pPlate3D =  new Plate3D;

	aPlate3DParams.m_flLenX = pContainerParams->m_flWidth;
	aPlate3DParams.m_flLenY = pContainerParams->m_flThickness;
	aPlate3DParams.m_flLenZ = pContainerParams->m_flHeight;
	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = (-pContainerParams->m_flDepth+pContainerParams->m_flThickness)/2;
	aPlate3DParams.m_flPosZ = pContainerParams->m_flHeight/2;

	pPlate3D->init(aPlate3DParams);
	addPart(pPlate3D);

	//Back plate
	pPlate3D = new Plate3D;

	aPlate3DParams.m_flLenX = pContainerParams->m_flWidth;
	aPlate3DParams.m_flLenY = pContainerParams->m_flThickness;
	aPlate3DParams.m_flLenZ = pContainerParams->m_flHeight;
	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = (pContainerParams->m_flDepth-pContainerParams->m_flThickness)/2;
	aPlate3DParams.m_flPosZ = pContainerParams->m_flHeight/2;

	aPlate3DParams.m_strFileNameTexture = "../../Resources/Textures/lz.rgb";
	pPlate3D->init(aPlate3DParams);
	addPart(pPlate3D);

	init(pContainerParams);
	setIsTargetPick(true);
}

//------------------------------------------------------------------------------------------

void Container::print(std::ostream & os) const	{
	os << "Object name: " << getName() << endl;
	int nI, nJ;
	os << "GetMatrix()" << endl;
	for (nI=0;nI<4;nI++)	{
		for (nJ=0;nJ<4;nJ++)	{
			os << getMatrix()(nI,nJ) << " ";
		}
		os << endl;
	}
	os << endl;
	os << "calculateMatrix()" << endl;
	for (nI=0;nI<4;nI++)	{
		for (nJ=0;nJ<4;nJ++)	{
			os << calculateMatrix()(nI,nJ) << " ";
		}
		os << endl;
	}
	os << endl;

	os << "Child index: " << getChildIndex(this) << endl;

	os << "========================================" << endl;
}