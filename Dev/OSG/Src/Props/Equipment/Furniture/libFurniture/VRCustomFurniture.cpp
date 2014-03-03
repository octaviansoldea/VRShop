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

const char* CustomFurniture::className() const	{
	return "CustomFurniture";
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

void CustomFurniture::print(std::ostream & os) const	{
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