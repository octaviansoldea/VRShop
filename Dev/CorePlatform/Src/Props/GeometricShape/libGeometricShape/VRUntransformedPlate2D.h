#ifndef UNTRANSFORMED_PLATE_2D_H
#define UNTRANSFORMED_PLATE_2D_H

#include <osg/Geode>
#include <osg/Geometry>

namespace VR {
	class UntransformedPlate2D : public osg::Geode {
	public:
		UntransformedPlate2D();

		virtual void setColor(const std::vector < float > & aarrflColor);
		virtual void setTexture(const std::string & astrFileName);
	private:
		osg::ref_ptr<osg::Geometry> m_pGeometry;
	};
}
#endif //UNTRANSFORMED_PLATE_2D_H