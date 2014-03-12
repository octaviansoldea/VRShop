#include "VRAbstractGeomShape.h"

using namespace VR;
using namespace std;
using namespace osg;

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

AbstractGeomShape::AbstractGeomShape(const AbstractGeomShape& ags,const CopyOp& copyop) :
AbstractObject(ags,copyop)	{
}

//--------------------------------------------------------------------------

AbstractGeomShape::~AbstractGeomShape()	{
}

//--------------------------------------------------------------------------

const char* AbstractGeomShape::className() const	{
	return "AbstractGeomShape";
};