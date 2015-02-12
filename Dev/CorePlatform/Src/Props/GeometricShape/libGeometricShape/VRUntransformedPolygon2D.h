#ifndef VR_UNTRANSFORMED_POLYGON_2D_H
#define VR_UNTRANSFORMED_POLYGON_2D_H

#include <osg/Geode>

namespace osg {class Geometry;}

namespace VR {
	class UntransformedPolygon2D : public osg::Geode {
	public:
		UntransformedPolygon2D(int anNumSides);

		virtual void setColor(const std::vector < float > & aarrflColor);
		virtual void setTexture(const std::string & astrFileName);
	private:
		osg::ref_ptr<osg::Geometry> m_pGeometry;
	};
}
#endif //VR_UNTRANSFORMED_POLYGON_2D_H