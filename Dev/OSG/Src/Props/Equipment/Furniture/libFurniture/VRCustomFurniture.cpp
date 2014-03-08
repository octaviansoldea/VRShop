#include <fstream>

#include "BasicStringDefinitions.h"

#include "VRCustomFurniture.h"

using namespace std;
using namespace osg;
using namespace VR;

CustomFurniture::CustomFurniture() : Furniture(new CustomFurnitureParams())	{
	setName("CustomFurniture");
}

//-----------------------------------------------------------------------

CustomFurniture::CustomFurniture(CustomFurnitureParams * apCustomFurnitureParams) : Furniture(apCustomFurnitureParams)	{
	CustomFurnitureParams * pCustomFurnitureParams = dynamic_cast<CustomFurnitureParams*>(m_pAbstractObjectParams);
	init(pCustomFurnitureParams);
}

//-----------------------------------------------------------------------

CustomFurniture::CustomFurniture(const CustomFurniture& cf,const CopyOp& copyop) : Furniture(cf,copyop)	{
}

//-----------------------------------------------------------------------

const char* CustomFurniture::className() const	{
	return "CustomFurniture";
}

//-----------------------------------------------------------------------

Object* CustomFurniture::cloneType() const	{
	return new CustomFurniture();
}

//-----------------------------------------------------------------------

Object* CustomFurniture::clone(const CopyOp& copyop) const	{
	return new CustomFurniture(*this,copyop);
}

//-----------------------------------------------------------------------

void CustomFurniture::init(FurnitureParams * apFurnitureParams)	{
	apFurnitureParams = dynamic_cast<FurnitureParams*>(m_pAbstractObjectParams);

	setScaling(apFurnitureParams->m_flLenX, apFurnitureParams->m_flLenY, apFurnitureParams->m_flLenZ);
	setRotation(apFurnitureParams->m_flAngleYZ, apFurnitureParams->m_flAngleXZ, apFurnitureParams->m_flAngleXY);
	setPosition(apFurnitureParams->m_flPosX, apFurnitureParams->m_flPosY, apFurnitureParams->m_flPosZ);
	
	Matrix & customFurnitureMatrix = calculateMatrix();
	setMatrix(customFurnitureMatrix);

	setName("CustomFurniture");
}

//-----------------------------------------------------------------------

string CustomFurniture::getSQLCommand() const {
	return(0);
}

//-----------------------------------------------------------------------

void CustomFurniture::initFromSQLData(const string & astrSQLData)	{
	string strSQLData = astrSQLData;
}

//-----------------------------------------------------------------------

void CustomFurniture::predefinedObject()	{
}

//------------------------------------------------------------------------------------------
