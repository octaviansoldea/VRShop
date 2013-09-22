#ifndef UNTRANSFORMED_PLATE_2D_H
#define UNTRANSFORMED_PLATE_2D_H

#include <osg/Geode>
#include <osg/Geometry>

namespace VR {
	class UntransformedPlate2D : public osg::Geode {
	public:
		UntransformedPlate2D();

		void setColor(const float aarrflColor[4]);
		void setTexture(const char * apchFileName);
	private:
		osg::ref_ptr<osg::Geometry> m_pGeometry;
	};
}
#endif //UNTRANSFORMED_PLATE_2D_H