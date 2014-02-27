#include "VRAbstractGeomShape.h"

using namespace VR;
using namespace std;

//=======================================================================

AbstractGeomShapeParams::AbstractGeomShapeParams() : AbstractObjectParams(),
m_strFileNameTexture(""){
	m_arrflRGBA.push_back(1.0);
	m_arrflRGBA.push_back(0.0);
	m_arrflRGBA.push_back(0.0);
	m_arrflRGBA.push_back(1.0);
}

//=======================================================================

AbstractGeomShape::AbstractGeomShape() : AbstractObject(new AbstractGeomShapeParams())	{
}

//--------------------------------------------------------------------------

AbstractGeomShape::AbstractGeomShape(AbstractGeomShapeParams * apAbstractGeomShapeParams) : 
AbstractObject(apAbstractGeomShapeParams)	{
}

//--------------------------------------------------------------------------

AbstractGeomShape::~AbstractGeomShape()	{
}
