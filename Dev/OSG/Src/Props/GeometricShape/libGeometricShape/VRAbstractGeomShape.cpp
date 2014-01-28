#include "VRAbstractGeomShape.h"

using namespace VR;
using namespace std;

//=======================================================================

AbstractGeomShapeParams::AbstractGeomShapeParams() :
m_strFileNameTexture(""){
	m_arrflRGBA.push_back(1.0);
	m_arrflRGBA.push_back(0.0);
	m_arrflRGBA.push_back(0.0);
	m_arrflRGBA.push_back(1.0);
}

//=======================================================================

AbstractGeomShape::AbstractGeomShape()	{
}

//--------------------------------------------------------------------------

AbstractGeomShape::~AbstractGeomShape()	{
}
