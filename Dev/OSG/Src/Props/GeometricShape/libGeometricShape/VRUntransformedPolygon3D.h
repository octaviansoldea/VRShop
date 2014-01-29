#ifndef VR_UNTRANSFORMED_POLYGON_3D_H
#define VR_UNTRANSFORMED_POLYGON_3D_H

#include <osg/Group>
#include <osg/Geode>

#include "VRAbstractGeomShape.h"

namespace VR {
	struct UntransformedPolygon3DParams	{
		float m_flRadius;
		float m_flHeight;
		int m_nRes;

		UntransformedPolygon3DParams();
	};

	class UntransformedPolygon3D : public osg::Group {
	private:
		UntransformedPolygon3DParams m_UntransformedPolygon3DParams;

	public:
		UntransformedPolygon3D();
		UntransformedPolygon3D(const UntransformedPolygon3DParams & aUntransformedPolygon3DParams);

		virtual void setColor(const std::vector < float > & aarrflColor);
		virtual void setTexture(const std::string & astrFileName);

		void setResolution(int anRes);
		void init(const UntransformedPolygon3DParams & aUntransformedPolygon3DParams);
	};
}
#endif //VR_UNTRANSFORMED_POLYGON_3D_H