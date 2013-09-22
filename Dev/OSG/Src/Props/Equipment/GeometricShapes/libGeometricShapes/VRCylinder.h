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
	};
}
#endif //VR_CYLINDER_H
