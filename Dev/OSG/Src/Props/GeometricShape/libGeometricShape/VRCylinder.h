#ifndef VR_CYLINDER_H
#define VR_CYLINDER_H

#include "VRPrism.h"

class ostream;

namespace VR {
	struct CylinderParams : public PrismParams {
		CylinderParams();
	};

	class Cylinder : public Prism {
	private:
		static std::string m_strSQLFormat;

	public:
		Cylinder();
		Cylinder(CylinderParams * apCylinderParams);
		Cylinder(const Cylinder& cyl,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);

		virtual const char* className() const;
		virtual osg::Object* cloneType() const { return new VR::Cylinder(); }
		virtual osg::Object* clone(const osg::CopyOp& copyop) const { return new VR::Cylinder(*this,copyop); }

		virtual std::string getSQLFormat() const;
		virtual std::string getSQLCommand() const;

		virtual void predefinedObject();
	};
}
#endif //VR_CYLINDER_H
