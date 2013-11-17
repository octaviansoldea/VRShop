#ifndef VR_UNTRANSFORMED_POLYGON_2D_H
#define VR_UNTRANSFORMED_POLYGON_2D_H

#include <osg/Geode>
#include <osg/Geometry>

namespace VR {
	class UntransformedPolygon2D : public osg::Geode {
	public:
		UntransformedPolygon2D(int anNumSides);

		void setColor(const std::vector < float > & aarrflColor);
		void setTexture(const std::string & astrFileName);
	private:
		osg::ref_ptr<osg::Geometry> m_pGeometry;
	};
}
#endif //VR_UNTRANSFORMED_POLYGON_2D_H