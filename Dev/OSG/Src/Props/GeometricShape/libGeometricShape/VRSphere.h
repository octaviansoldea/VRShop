#ifndef VR_SPHERE_H
#define VR_SPHERE_H

#include "VRAbstractGeomShape.h"
#include "VRUntransformedSphere.h"

class ostream;

namespace VR	{
	struct SphereParams : public AbstractGeomShapeParams, public UntransformedSphereParams	{
		SphereParams();
	};


	class Sphere : public AbstractGeomShape	{
	private:
		static std::string m_strSQLFormat;

		osg::ref_ptr <UntransformedSphere> m_pUntransformedSphere;

	public:
		Sphere();
		Sphere(SphereParams * apSphereParams);
		Sphere(const Sphere& sp,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);

		virtual const char* className() const;
		virtual osg::Object* cloneType() const { return new Sphere(); }
		virtual osg::Object* clone(const osg::CopyOp& copyop) const { return new Sphere(*this,copyop); }

		virtual std::string getSQLFormat() const;
		virtual std::string getSQLCommand() const;

		virtual void initFromSQLData(const std::string & astrSQLData);
		virtual void init(AbstractGeomShapeParams & aAbstractGeomShapeParams);

		virtual void predefinedObject();

		virtual void setColor(const std::vector < float > & aarrflColor);
		virtual void setTexture(const std::string & astrFileName);
		void setResolution(int anRes);
	};
}
#endif //VR_SPHERE_H