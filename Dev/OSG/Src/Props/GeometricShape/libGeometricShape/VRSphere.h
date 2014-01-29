#ifndef VR_SPHERE_H
#define VR_SPHERE_H

#include "VRAbstractGeomShape.h"
#include "VRUntransformedSphere.h"

namespace VR	{
	struct SphereParams : public AbstractGeomShapeParams, public UntransformedSphereParams	{
		SphereParams();
	};


	class Sphere : public AbstractGeomShape	{
	private:
		static std::string m_strSQLFormat;

		osg::ref_ptr <UntransformedSphere> m_pUntransformedSphere;
		SphereParams m_SphereParams;

	public:
		Sphere();
		Sphere(const SphereParams & aSphereParams);

		virtual std::string getSQLFormat() const;
		virtual std::string getSQLCommand() const;

		virtual void initFromSQLData(const std::string & astrSQLData);
		virtual void init(const AbstractGeomShapeParams & aAbstractGeomShapeParams);

		virtual void predefinedObject();

		virtual void setColor(const std::vector < float > & aarrflColor);
		virtual void setTexture(const std::string & astrFileName);
		void setResolution(int anRes);
	};
}
#endif //VR_SPHERE_H