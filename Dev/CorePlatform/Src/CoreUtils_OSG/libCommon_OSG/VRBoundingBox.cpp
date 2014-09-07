#include <osg/Geometry>
#include <osg/PolygonMode>
#include <osg/ComputeBoundsVisitor>

#include "VRBoundingBox.h"

using namespace osg;
using namespace VR;

VR::BoundingBox::BoundingBox(ref_ptr<Node> aNode)	{
	ref_ptr<ComputeBoundsVisitor> cbv = new ComputeBoundsVisitor();
	aNode->accept(*cbv);

	osg::BoundingBox boundingBox = cbv->getBoundingBox();

	ref_ptr<Vec3Array> points = new Vec3Array(10);
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
	ref_ptr<Vec4Array> color = new Vec4Array;
	color->push_back(Vec4(1,1,1,1));

	//Send points to the geometry
	ref_ptr<Geometry> geom = new Geometry;
	geom->setVertexArray(points);
	geom->setColorArray(color.get());
	geom->setColorBinding(Geometry::BIND_OVERALL);
	geom->addPrimitiveSet(new DrawArrays(PrimitiveSet::QUAD_STRIP, 0, 10));	

	addDrawable(geom.get());
	StateSet* ss = this->getOrCreateStateSet();
	ss->setAttributeAndModes(new PolygonMode(PolygonMode::FRONT_AND_BACK, PolygonMode::LINE));

	setName("BoundingBox");
}


const char * VR::BoundingBox::className() const	{
	return "BoundingBox";
}
