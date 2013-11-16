#ifndef VR_CYLINDER_H
#define VR_CYLINDER_H

#include "VRPrism.h"

namespace VR {
	struct CylinderParams : public PrismParams {
		CylinderParams();
	};

	class Cylinder : public Prism {
	public:
		Cylinder();
		Cylinder(const CylinderParams & aCylinderParams);

		virtual std::string getSQLCommand(const AbstractGeomShapeParams & aAbstractGeomShapeParams) const;
	};
}
#endif //VR_CYLINDER_H
