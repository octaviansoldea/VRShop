#ifndef UNTRANSFORMED_SPHERE_H
#define UNTRANSFORMED_SPHERE_H

#include <osg/Geometry>
#include <osg/Geode>
#include <osg/MatrixTransform>

#include "VRAbstractGeomShape.h"

namespace VR {
	struct SphereParams : public AbstractGeomShapeParams	{
		float m_flRadius;
		int m_nResPhi;
		int m_nResTheta;

		std::vector < float > m_arrflRGBA;
		std::string m_strFileNameTexture;

		SphereParams();
	};

	class UntransformedSphere : public AbstractGeomShape	{
	private:
		static std::string m_strSQLFormat;
		SphereParams m_SphereParams;
		osg::ref_ptr<osg::Geode> m_pGeode;

	public:
		UntransformedSphere();
		UntransformedSphere(const SphereParams & aSphereParams);

		void setColor(const std::vector < float > & aarrflColor);
		void setTexture(const std::string astrFileName);
		void setResolution(int anResPhi, int anResTheta);
		void setRadius(float aflRadius);

		virtual std::string getSQLFormat() const;
		virtual std::string getSQLCommand() const;

		virtual void init(const AbstractGeomShapeParams & aAbstractGeomShapeParams);
		virtual void initFromSQLData(const std::string & astrSQLData);
		virtual void predefinedObject() {};
	};
}
#endif //UNTRANSFORMED_SPHERE_H
