#ifndef UNTRANSFORMED_SPHERE_H
#define UNTRANSFORMED_SPHERE_H

#include <osg/Geometry>
#include <osg/Geode>

namespace VR {
	struct UntransformedSphereParams	{
		float m_flRadius;
		int m_nResPhi;
		int m_nResTheta;

		UntransformedSphereParams();
	};

	class UntransformedSphere : public osg::Geode	{
	private:
		UntransformedSphereParams m_UntransformedSphereParams;

		void init(const UntransformedSphereParams & aUntransformedSphereParams);
	public:
		UntransformedSphere();
		UntransformedSphere(const UntransformedSphereParams & aUntransformedSphereParams);

		virtual void setColor(const std::vector < float > & aarrflColor);
		virtual void setTexture(const std::string & astrFileName);

		void setResolution(int anResPhi, int anResTheta);
		void setRadius(float aflRadius);
	};
}
#endif //UNTRANSFORMED_SPHERE_H
