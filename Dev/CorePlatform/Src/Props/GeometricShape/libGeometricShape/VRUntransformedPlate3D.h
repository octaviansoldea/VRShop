#ifndef VR_UNTRANSFORMED_PLATE_3D_H
#define VR_UNTRANSFORMED_PLATE_3D_H

#include <osg/MatrixTransform>

namespace VR {
	class UntransformedPlate2D;

	class UntransformedPlate3D : public osg::MatrixTransform {
	public:
		UntransformedPlate3D();

		enum PlateSide {FRONT=0,BACK,RIGHT,LEFT,BOTTOM,UP,ALL};

		struct Surface	{
			PlateSide m_PlateSide;
			bool m_bIsColor;
			std::vector<float> m_vecColor;
			std::string m_strFileName;
		};

		void setTextureOrColor(Surface & aSurface);
		void setColor(std::vector<float> & avecColor, PlateSide aPlateSide=ALL);
		void setTexture(std::string & astrFileName, PlateSide aPlateSide=ALL);

		UntransformedPlate2D * getPlate2D(const PlateSide & anSide);
	};
}
#endif //VR_UNTRANSFORMED_PLATE_3D_H