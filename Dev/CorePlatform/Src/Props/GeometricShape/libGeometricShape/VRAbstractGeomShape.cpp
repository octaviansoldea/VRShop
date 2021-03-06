#include "VRAbstractGeomShape.h"

using namespace VR;
using namespace std;
using namespace osg;

//=======================================================================

AbstractGeomShapeParams::AbstractGeomShapeParams() : AbstractObjectParams(),
m_strFileNameTexture(" "){
	m_arrflRGBA.push_back(1.0);
	m_arrflRGBA.push_back(0.0);
	m_arrflRGBA.push_back(0.0);
	m_arrflRGBA.push_back(1.0);
}

//=======================================================================

AbstractGeomShape::AbstractGeomShape(const AbstractGeomShapeParams & aAbstractGeomShapeParams) : 
AbstractObject(aAbstractGeomShapeParams)	{
	setParams(aAbstractGeomShapeParams);
}

//--------------------------------------------------------------------------

AbstractGeomShape::AbstractGeomShape(const AbstractGeomShape& ags,const CopyOp& copyop) :
AbstractObject(ags,copyop)	{
	AbstractGeomShapeParams aGsp;
	ags.getParams(aGsp);
	setParams(aGsp);
}

//--------------------------------------------------------------------------

AbstractGeomShape::~AbstractGeomShape()	{
}

//--------------------------------------------------------------------------

const char* AbstractGeomShape::className() const	{
	return "AbstractGeomShape";
}

//--------------------------------------------------------------------------

void AbstractGeomShape::setParams(const AbstractGeomShapeParams & aAbstractGeomShapeParams) {
	m_arrflRGBA = aAbstractGeomShapeParams.m_arrflRGBA;
	m_strFileNameTexture = aAbstractGeomShapeParams.m_strFileNameTexture;

	AbstractObject::setParams(aAbstractGeomShapeParams);
}

//--------------------------------------------------------------------------

void AbstractGeomShape::getParams(AbstractGeomShapeParams & aAbstractGeomShapeParams) const {
	AbstractObject::getParams(aAbstractGeomShapeParams);

	aAbstractGeomShapeParams.m_arrflRGBA = m_arrflRGBA;
	aAbstractGeomShapeParams.m_strFileNameTexture = m_strFileNameTexture;
}

//--------------------------------------------------------------------------

string AbstractGeomShape::getTexture() const	{
	return m_strFileNameTexture;
}

//--------------------------------------------------------------------------

vector<float> AbstractGeomShape::getColor() const	{
	return m_arrflRGBA;
}