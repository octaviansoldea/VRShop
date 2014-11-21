#include <fstream>

#include "BasicStringDefinitions.h"

#include "VRCustomFurniture.h"

using namespace std;
using namespace osg;
using namespace VR;

//-----------------------------------------------------------------------

CustomFurniture::CustomFurniture(const CustomFurnitureParams & aCustomFurnitureParams) : Furniture(aCustomFurnitureParams)	{
	setParams(aCustomFurnitureParams);
	setName("CustomFurniture_"+tostr(getAbstractObjectNo()));
}

//-----------------------------------------------------------------------

CustomFurniture::CustomFurniture(const CustomFurniture& cf,const CopyOp& copyop) : Furniture(cf,copyop)	{
	CustomFurnitureParams aCf;
	cf.getParams(aCf);
	setParams(aCf);

	setName("CustomFurniture_"+tostr(getAbstractObjectNo()));
}

//-----------------------------------------------------------------------

const char* CustomFurniture::className() const	{
	return "CustomFurniture";
}

//-----------------------------------------------------------------------

Object* CustomFurniture::cloneType() const	{
	CustomFurnitureParams aCf;
	return new CustomFurniture(aCf);
}

//-----------------------------------------------------------------------

Object* CustomFurniture::clone(const CopyOp& copyop) const	{
	return new CustomFurniture(*this,copyop);
}

//-----------------------------------------------------------------------

void CustomFurniture::init(const CustomFurnitureParams & aCustomFurnitureParams)	{
	setParams(aCustomFurnitureParams);

	Matrix customFurnitureMatrix = calculateMatrix();
	setMatrix(customFurnitureMatrix);
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
