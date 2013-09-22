#ifndef UNTRANSFORMED_SPHERE_H
#define UNTRANSFORMED_SPHERE_H

#include <osg/Geode>
#include <osg/Geometry>

#include "VRAbstractGeomShape.h"

namespace VR {
	struct SphereParams : public AbstractGeomShapeParams	{
		float m_flRadius;
		int m_nResPhi;
		int m_nResTheta;

		float m_arrflRGBA[4];
		const char * m_pchFileName;

		SphereParams();
	};

	class UntransformedSphere : public AbstractGeomShape, public osg::Geode {
		int m_nResPhi;
		int m_nResTheta;
	public:
		UntransformedSphere();
		UntransformedSphere(const SphereParams & aSphereParams);

		void setColor(const float aarrflColor[4]);
		void setTexture(const char * apchFileName);
		void setResolution(int anResPhi, int anResTheta);
		void setRadius(float aflRadius);

		virtual std::string getSQLCommand() const;
		virtual void init(const AbstractGeomShapeParams & aAbstractGeomShapeParams);

		virtual void initFromSQLData(const std::string & astrSQLData);
	};
}
#endif //UNTRANSFORMED_SPHERE_H
