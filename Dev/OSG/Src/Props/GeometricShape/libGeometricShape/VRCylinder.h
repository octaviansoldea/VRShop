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
		virtual const char* className() const;

		virtual std::string getSQLFormat() const;
		virtual std::string getSQLCommand() const;

		virtual void predefinedObject();
		virtual void print(std::ostream & os) const;
	};
}
#endif //VR_CYLINDER_H
