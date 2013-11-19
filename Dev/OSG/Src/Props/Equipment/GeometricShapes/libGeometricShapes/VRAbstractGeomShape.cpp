#include <string>

#include "VRAbstractGeomShape.h"

using namespace VR;
using namespace std;

string AbstractGeomShape::m_strSQLFormat = "";

AbstractGeomShapeParams::AbstractGeomShapeParams()	{
}

//==============================================================

AbstractGeomShape::AbstractGeomShape() : m_bIsTargetPick(false) {
}

//--------------------------------------------------------------

void AbstractGeomShape::initFromSQLData(const std::string & astrSQLData)	{
}

//--------------------------------------------------------------------------

std::string AbstractGeomShape::getSQLFormat() const {
	return(m_strSQLFormat);
}

//--------------------------------------------------------------------------

void AbstractGeomShape::setIsTargetPick(bool abIsTargetPick)	{
	m_bIsTargetPick = abIsTargetPick;
}

//--------------------------------------------------------------------------

bool AbstractGeomShape::getIsTargetPick() const	{
	return m_bIsTargetPick;
}

