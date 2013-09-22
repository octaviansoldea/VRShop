#include "VRAbstractGeomShape.h"

using namespace VR;
using namespace std;

AbstractGeomShapeParams::AbstractGeomShapeParams()	{
}

//==============================================================

AbstractGeomShape::AbstractGeomShape()	{
}

string AbstractGeomShape::getSQLCommand() const	{
	return("");
}

//--------------------------------------------------------------

void AbstractGeomShape::initFromSQLData(const std::string & astrSQLData)	{
}

//--------------------------------------------------------------
