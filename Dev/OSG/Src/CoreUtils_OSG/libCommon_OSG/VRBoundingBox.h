#ifndef OSG_BOUNDING_BOX_H
#define OSG_BOUNDING_BOX_H

#include <osg/Geode>

namespace VR {
	class BoundingBox : public osg::Geode	{
		public:
			BoundingBox(osg::ref_ptr<osg::Node> aNode);
	};
}
#endif //OSG_BOUNDING_BOX_H