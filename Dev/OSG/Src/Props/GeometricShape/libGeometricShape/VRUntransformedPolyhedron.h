#ifndef VR_UNTRANSFORMED_POLYHEDRON_H
#define VR_UNTRANSFORMED_POLYHEDRON_H

#include <osg/Group>
#include <osg/Geode>

#include "VRAbstractGeomShape.h"

namespace VR {
	struct UntransformedPolyhedronParams	{
		float m_flRadius;
		float m_flHeight;
		int m_nResolution;

		UntransformedPolyhedronParams();
	};

	class UntransformedPolyhedron : public osg::Group {
	private:
		UntransformedPolyhedronParams m_UntransformedPolyhedronParams;

	public:
		UntransformedPolyhedron();
		UntransformedPolyhedron(const UntransformedPolyhedronParams & aUntransformedPolyhedronParams);

		virtual void setColor(const std::vector < float > & aarrflColor);
		virtual void setTexture(const std::string & astrFileName);

		void setResolution(int anResolution);
		virtual void init(const UntransformedPolyhedronParams & aUntransformedPolyhedronParams);
	};
}
#endif //VR_UNTRANSFORMED_POLYHEDRON_H