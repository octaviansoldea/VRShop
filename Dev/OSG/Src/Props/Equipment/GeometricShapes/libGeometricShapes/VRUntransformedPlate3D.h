#ifndef VR_UNTRANSFORMED_PLATE_3D_H
#define VR_UNTRANSFORMED_PLATE_3D_H

#include <osg/Group>

namespace VR {
	class UntransformedPlate3D : public osg::Group {
	public:
		UntransformedPlate3D();

		void setColor(const float aarrflColor[4]);
		void setTexture(const char * apchFileName);
	};
}
#endif //VR_UNTRANSFORMED_PLATE_3D_H