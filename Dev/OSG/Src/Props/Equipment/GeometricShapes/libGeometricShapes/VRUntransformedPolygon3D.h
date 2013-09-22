#ifndef VR_UNTRANSFORMED_POLYGON_3D_H
#define VR_UNTRANSFORMED_POLYGON_3D_H

#include <osg/Group>
#include <osg/Geode>

#include "VRAbstractGeomShape.h"

namespace VR {
	class UntransformedPolygon3D : public osg::Group {
	public:
		UntransformedPolygon3D();

		void setColor(const float aarrflColor[4]);
		void setTexture(const char * apchFileName);
		void setResolution(int anSidesNr);
	};
}
#endif //VR_UNTRANSFORMED_POLYGON_3D_H