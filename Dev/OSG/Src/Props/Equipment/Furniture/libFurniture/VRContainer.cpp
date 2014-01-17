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
	const ContainerParams & aContainerParams = static_cast<const ContainerParams&>(aFurnitureParams);

	setScaling(aContainerParams);
	setRotation(aContainerParams);
	setPosition(aContainerParams);

	Matrix matrix;
	matrix.set(1, 0, 0, 0,
			   0, 1, 0, 0,
			   0, 0, 1, 0,
			   0, 0, 0,	1);

	osg::Matrix containerMatrix =
		matrix.scale(aContainerParams.m_flScaleX, aContainerParams.m_flScaleY, aContainerParams.m_flScaleZ)
		*
		matrix.rotate(
			aContainerParams.m_flAngleYZ, osg::X_AXIS,
			aContainerParams.m_flAngleXZ, osg::Y_AXIS,
			aContainerParams.m_flAngleXY, osg::Z_AXIS)
		*
		matrix.translate(aContainerParams.m_flPosX, aContainerParams.m_flPosY, aContainerParams.m_flPosZ)
	;
	
	setMatrix(containerMatrix);

	setName(Furniture::getName() + ":Container");
}

//-----------------------------------------------------------------------

string Container::getSQLCommand() const {
	string strSQLCommand = "INSERT INTO EquipmentItem (EquipmentItemName, EquipmentID) "
		"VALUES ('Container', (SELECT EquipmentID FROM Equipment WHERE EquipmentName = 'Furniture'));";
	int nNumParts = m_arrSQLCommandLines.size();

	vector < string >::const_iterator it = m_arrSQLCommandLines.begin();
	for (it; it != m_arrSQLCommandLines.end()-1; it++)	{
		strSQLCommand += *it;
	}
	strSQLCommand += m_arrSQLCommandLines[nNumParts-1];
	
	return(strSQLCommand);
}

//-----------------------------------------------------------------------

void Container::initFromSQLData(const string & astrSQLData)	{
	string strSQLData = astrSQLData;
	string strDelimiter = "?";
	
	vector < string > arrstrSQLData = splitString(strSQLData,strDelimiter);

	ContainerParams containerParams;
	containerParams.m_flPosX = 0.0;
	containerParams.m_flPosY = 0.0;
	containerParams.m_flPosZ = 0.0;
	containerParams.m_flAngleXY = 0.0;
	containerParams.m_flScaleX = 1;

	for (auto it = arrstrSQLData.begin(); it != arrstrSQLData.end()-1; it++)	{
		ref_ptr < Plate3D > pPlate = new Plate3D;
		pPlate->initFromSQLData(*it);
		addChild(pPlate);
	}
	init(containerParams);
}

//-----------------------------------------------------------------------

void Container::predefinedObject()	{
	ref_ptr < Plate3D > pPlate3D =  new Plate3D;
	Plate3DParams aPlate3DParams;
	//Bottom plate
	aPlate3DParams.m_flLenX = m_ContainerParams.m_flWidth;
	aPlate3DParams.m_flLenY = m_ContainerParams.m_flDepth;
	aPlate3DParams.m_flLenZ = m_ContainerParams.m_flThickness;
				  
	aPlate3DParams.m_flPosX = 0;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = m_ContainerParams.m_flThickness/2;
				  
	aPlate3DParams.m_arrflRGBA.push_back((float)1.0);
	aPlate3DParams.m_arrflRGBA.push_back((float)0.0);
	aPlate3DParams.m_arrflRGBA.push_back((float)0.0);
	aPlate3DParams.m_arrflRGBA.push_back((float)1.0);
	pPlate3D->init(aPlate3DParams);
	addPart(pPlate3D);

	//Left plate
	pPlate3D =  new Plate3D;
	aPlate3DParams.m_flLenX = m_ContainerParams.m_flThickness;
	aPlate3DParams.m_flLenY = m_ContainerParams.m_flDepth;
	aPlate3DParams.m_flLenZ = m_ContainerParams.m_flHeight;
	aPlate3DParams.m_flPosX = (-m_ContainerParams.m_flWidth+m_ContainerParams.m_flThickness)/2;
	aPlate3DParams.m_flPosY = 0;
	aPlate3DParams.m_flPosZ = m_ContainerParams.m_flHeight/2;

	aPlate3DParams.m_arrflRGBA.push_back((float)1.0);
	aPlate3DParams.m_arrflRGBA.push_back((float)0.0);
	aPlate3DParams.m_arrflRGBA.push_back((float)0.0);
	aPlate3DParams.m_arrflRGBA.push_back((float)1.0);

	pPlate3D->init(aPlate3DParams);
	addPart(pPlate3D);

	//Right plate
	pPlate3D =  new Plate3D;
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
	pPlate3D =  new Plate3D;
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