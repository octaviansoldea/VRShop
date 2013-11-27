#ifndef VR_ABSTRACT_GEOM_SHAPE_H
#define VR_ABSTRACT_GEOM_SHAPE_H

#include <string>

#include "VRAbstractObject.h"

namespace VR {
	struct AbstractGeomShapeParams : AbstractObjectParams	{
		AbstractGeomShapeParams();
	};

	class AbstractGeomShape	: public AbstractObject	{
	public:
		AbstractGeomShape();

		virtual void init(const AbstractGeomShapeParams & aAbstractGeomShapeParams) = 0;

	private:
		static std::string m_strSQLFormat;
	};
}
#endif //VR_ABSTRACT_GEOM_SHAPE_H