#ifndef VR_CYLINDER_H
#define VR_CYLINDER_H

#include "VRPrism.h"

namespace VR {
	struct CylinderParams : public PrismParams {
		CylinderParams();
	};

	class Cylinder : public Prism {
	private:
		static std::string m_strSQLFormat;

	public:
		Cylinder(const CylinderParams & aCylinderParams);
		Cylinder(const Cylinder& cyl,const osg::CopyOp& copyop=osg::CopyOp::DEEP_COPY_ALL);

		virtual const char* className() const;
		virtual osg::Object* cloneType() const;
		virtual osg::Object* clone(const osg::CopyOp& copyop) const;

		virtual void init(const CylinderParams & aCylinderParams);

		virtual std::string getSQLFormat() const;
		virtual std::string getSQLCommand() const;

		virtual void predefinedObject();

		virtual std::string prepareRowData(const std::string & astrParentName="");

	};
}
#endif //VR_CYLINDER_H
