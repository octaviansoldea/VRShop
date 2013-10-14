#include <osg/Geometry>
#include <osg/PolygonMode>
#include <osg/ComputeBoundsVisitor>

#include "VRBoundingBox.h"

using namespace osg;
using namespace VR;

VR::BoundingBox::BoundingBox(ref_ptr<Node> aNode)	{
	osg::ref_ptr<osg::ComputeBoundsVisitor> cbv = new osg::ComputeBoundsVisitor();
	aNode->accept(*cbv);

	osg::BoundingBox boundingBox = cbv->getBoundingBox();

	osg::ref_ptr<osg::Vec3Array> points = new osg::Vec3Array(10);
	(*points)[0].set(boundingBox.xMin(), boundingBox.yMin(), boundingBox.zMin());
	(*points)[1].set(boundingBox.xMin(), boundingBox.yMin(), boundingBox.zMax());
	(*points)[2].set(boundingBox.xMax(), boundingBox.yMin(), boundingBox.zMin());
	(*points)[3].set(boundingBox.xMax(), boundingBox.yMin(), boundingBox.zMax());
	(*points)[4].set(boundingBox.xMax(), boundingBox.yMax(), boundingBox.zMin());
	(*points)[5].set(boundingBox.xMax(), boundingBox.yMax(), boundingBox.zMax());
	(*points)[6].set(boundingBox.xMin(), boundingBox.yMax(), boundingBox.zMin());
	(*points)[7].set(boundingBox.xMin(), boundingBox.yMax(), boundingBox.zMax());
	(*points)[8].set(boundingBox.xMin(), boundingBox.yMin(), boundingBox.zMin());
	(*points)[9].set(boundingBox.xMin(), boundingBox.yMin(), boundingBox.zMax());

	//Set color of the bounding box
	osg::ref_ptr<osg::Vec4Array> color = new osg::Vec4Array;
	color->push_back(osg::Vec4(1,1,1,1));

	//Send points to the geometry
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	geom->setVertexArray(points);
	geom->setColorArray(color.get());
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUAD_STRIP, 0, 10));	

	addDrawable(geom.get());
	osg::StateSet* ss = this->getOrCreateStateSet();
	ss->setAttributeAndModes(new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE));
}