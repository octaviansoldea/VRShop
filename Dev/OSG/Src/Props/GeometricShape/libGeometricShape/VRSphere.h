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
		Sphere(const SphereParams & aSphereParams);
		Sphere(const Sphere& sp,const osg::CopyOp& copyop=osg::CopyOp::DEEP_COPY_ALL);

		virtual const char* className() const;
		virtual osg::Object* cloneType() const;
		virtual osg::Object* clone(const osg::CopyOp& copyop) const;

		virtual std::string getSQLFormat() const;
		virtual std::string getSQLCommand() const;

		virtual void initFromSQLData(const std::string & astrSQLData);
		virtual void init(const SphereParams & aSphereParams);

		virtual void predefinedObject();

		virtual void setColor(const std::vector < float > & aarrflColor);
		virtual void setTexture(const std::string & astrFileName);
		void setResolution(int anRes);

		virtual std::string prepareRowData(const std::string & astrParentName="");

	};
}
#endif //VR_SPHERE_H