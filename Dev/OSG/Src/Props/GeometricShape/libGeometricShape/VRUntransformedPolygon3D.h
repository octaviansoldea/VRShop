#ifndef VR_UNTRANSFORMED_POLYGON_3D_H
#define VR_UNTRANSFORMED_POLYGON_3D_H

#include <osg/Group>
#include <osg/Geode>

#include "VRAbstractGeomShape.h"

namespace VR {
	class UntransformedPolygon3D : public osg::Group {
	public:
		UntransformedPolygon3D();

		virtual void setColor(const std::vector < float > & aarrflColor);
		virtual void setTexture(const std::string & astrFileName);

		void setResolution(int anSidesNr);
	};
}
#endif //VR_UNTRANSFORMED_POLYGON_3D_H