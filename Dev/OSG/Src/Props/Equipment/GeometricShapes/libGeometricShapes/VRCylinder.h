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
		CylinderParams m_CylinderParams;
	public:
		Cylinder();
		Cylinder(const CylinderParams & aCylinderParams);

		virtual std::string getSQLFormat() const;
		virtual std::string getSQLCommand() const;
	};
}
#endif //VR_CYLINDER_H
