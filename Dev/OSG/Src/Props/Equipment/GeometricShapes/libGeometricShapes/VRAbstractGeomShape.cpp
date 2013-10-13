#include "VRAbstractGeomShape.h"

using namespace VR;
using namespace std;

AbstractGeomShapeParams::AbstractGeomShapeParams()	{
}

//==============================================================

AbstractGeomShape::AbstractGeomShape() : m_bIsTargetPick(false) {
}

//--------------------------------------------------------------

string AbstractGeomShape::getSQLCommand() const	{
	return("");
}

//--------------------------------------------------------------

void AbstractGeomShape::initFromSQLData(const std::string & astrSQLData)	{
}

//--------------------------------------------------------------------------

void AbstractGeomShape::setIsTargetPick(bool abIsTargetPick)	{
	m_bIsTargetPick = abIsTargetPick;
}

//--------------------------------------------------------------------------

bool AbstractGeomShape::getIsTargetPick() const	{
	return m_bIsTargetPick;
}

