#include <osg/Texture2D>
#include <osg/Image>
#include <osg/StateSet>
#include <osg/TextureRectangle>
#include <osg/TexMat>
#include <osgDB/ReadFile>

#include "VRUntransformedPolygon2D.h"

using namespace osg;
using namespace VR;
using namespace std;

UntransformedPolygon2D::UntransformedPolygon2D(int anNumSides)	{
	ref_ptr<Vec3Array> m_pPoints = new Vec3Array(anNumSides);

	float flAngleStep = (2*PI) / anNumSides;

	float flPosX = 0.0;
	const float flPosY = - 1.0 / 2.0;
	float flPosZ = 0.0;

	int nI;
	for (nI=0;nI<anNumSides;nI++)	{
		float flAngle = nI*flAngleStep;
		flPosX = cos(flAngle);
		flPosZ = sin(flAngle);

		(*m_pPoints)[nI].set(flPosX, flPosY, flPosZ);
	}
	
	m_pGeometry = new Geometry;
	m_pGeometry->setVertexArray(m_pPoints.get());
	m_pGeometry->addPrimitiveSet(new DrawArrays(PrimitiveSet::TRIANGLE_FAN, 0, anNumSides));

	ref_ptr<Vec3Array> pN = new Vec3Array;
	m_pGeometry->setNormalArray(pN.get());
	m_pGeometry->setNormalBinding(Geometry::BIND_OVERALL);
	pN->push_back(Vec3(0.0, -1.0, 0.0));

	addDrawable(m_pGeometry);
}

//--------------------------------------------------------------

void UntransformedPolygon2D::setColor(const vector < float > & aarrflColor) {
	ref_ptr<Vec4Array> pColors = new Vec4Array;
	m_pGeometry->setColorArray(pColors.get());
	m_pGeometry->setColorBinding(Geometry::BIND_OVERALL);
	Vec4 vec4(aarrflColor[0], aarrflColor[1], aarrflColor[2], aarrflColor[3]);
	pColors->push_back(vec4);
}
