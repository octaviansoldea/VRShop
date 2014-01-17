#ifndef VR_ABSTRACT_GEOM_SHAPE_H
#define VR_ABSTRACT_GEOM_SHAPE_H

#include "VRAbstractObject.h"

namespace VR {
	struct AbstractGeomShapeParams : AbstractObjectParams	{
		AbstractGeomShapeParams();
	};

	class AbstractGeomShape	: public AbstractObject	{
	public:
		AbstractGeomShape();

		virtual void init(const AbstractGeomShapeParams & aAbstractGeomShapeParams) = 0;
	};
}
#endif //VR_ABSTRACT_GEOM_SHAPE_H