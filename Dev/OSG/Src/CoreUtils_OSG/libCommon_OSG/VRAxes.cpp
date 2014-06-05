#include <osg/Geometry>
#include <osg/LineWidth>

#include "VRAxes.h"

using namespace osg;
using namespace VR;

Axes::Axes()	{
    ref_ptr<Vec3Array> pPoints = new Vec3Array();
    pPoints->push_back(Vec3(0.0f, 0.0f, 0.0f));
    pPoints->push_back(Vec3(1.0f, 0.0f, 0.0f));
    pPoints->push_back(Vec3(0.0f, 0.0f, 0.0f));
    pPoints->push_back(Vec3(0.0f, 1.0f, 0.0f));
    pPoints->push_back(Vec3(0.0f, 0.0f, 0.0f));
    pPoints->push_back(Vec3(0.0f, 0.0f, 1.0f));

    ref_ptr<Vec4Array> pColors = new Vec4Array();
    pColors->push_back(Vec4(1.0f, 0.0f, 0.0f, 1.0f));
    pColors->push_back(Vec4(1.0f, 0.0f, 0.0f, 1.0f));
    pColors->push_back(Vec4(0.0f, 1.0f, 0.0f, 1.0f));
    pColors->push_back(Vec4(0.0f, 1.0f, 0.0f, 1.0f));
    pColors->push_back(Vec4(0.0f, 0.0f, 1.0f, 1.0f));
    pColors->push_back(Vec4(0.0f, 0.0f, 1.0f, 1.0f));

    ref_ptr<Geometry> pGeometry = new Geometry();
	pGeometry->setVertexArray(pPoints);
	pGeometry->setColorArray(pColors, Array::BIND_PER_VERTEX);
    pGeometry->addPrimitiveSet(new DrawArrays(PrimitiveSet::LINES, 0, 6));
    pGeometry->getOrCreateStateSet()->setMode(GL_LIGHTING, false);
	pGeometry->getOrCreateStateSet()->setAttributeAndModes(new osg::LineWidth(50.0));

	addDrawable(pGeometry.get());

	setName("Axes");
}

//------------------------------------------------------------------

Axes::~Axes()	{
}