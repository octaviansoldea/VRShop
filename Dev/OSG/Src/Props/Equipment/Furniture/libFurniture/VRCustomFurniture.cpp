#include "BasicStringDefinitions.h"

#include "VRCustomFurniture.h"

using namespace std;
using namespace osg;
using namespace VR;

CustomFurniture::CustomFurniture() : Furniture(new CustomFurnitureParams())	{
}

//-----------------------------------------------------------------------

CustomFurniture::CustomFurniture(CustomFurnitureParams * apCustomFurnitureParams) : Furniture(apCustomFurnitureParams)	{
	CustomFurnitureParams * pCustomFurnitureParams = dynamic_cast<CustomFurnitureParams*>(m_pAbstractObjectParams);
}

//-----------------------------------------------------------------------

void CustomFurniture::init(FurnitureParams & aFurnitureParams)	{
	CustomFurnitureParams * pCustomFurnitureParams = dynamic_cast<CustomFurnitureParams*>(&aFurnitureParams);

	setScaling(pCustomFurnitureParams->m_flLenX, pCustomFurnitureParams->m_flLenY, pCustomFurnitureParams->m_flLenZ);
	setRotation(pCustomFurnitureParams->m_flAngleYZ, pCustomFurnitureParams->m_flAngleXZ, pCustomFurnitureParams->m_flAngleXY);
	setPosition(pCustomFurnitureParams->m_flPosX, pCustomFurnitureParams->m_flPosY, pCustomFurnitureParams->m_flPosZ);

	Matrix matrix;
	matrix.set(1, 0, 0, 0,
			   0, 1, 0, 0,
			   0, 0, 1, 0,
			   0, 0, 0,	1);

	Matrix customFurnitureMatrix =
		matrix.scale(pCustomFurnitureParams->m_flLenX, pCustomFurnitureParams->m_flLenY, pCustomFurnitureParams->m_flLenZ)
		*
		matrix.rotate(
			pCustomFurnitureParams->m_flAngleYZ, osg::X_AXIS,
			pCustomFurnitureParams->m_flAngleXZ, osg::Y_AXIS,
			pCustomFurnitureParams->m_flAngleXY, osg::Z_AXIS)
		*
		matrix.translate(pCustomFurnitureParams->m_flPosX, pCustomFurnitureParams->m_flPosY, pCustomFurnitureParams->m_flPosZ)
	;
	
	setMatrix(customFurnitureMatrix);

	setName(Furniture::getName() + ":CustomFurniture");

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