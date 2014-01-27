#ifndef VR_ABSTRACT_GEOM_SHAPE_H
#define VR_ABSTRACT_GEOM_SHAPE_H

#include "VRAbstractObject.h"

namespace VR {
	struct AbstractGeomShapeParams : AbstractObjectParams	{
		std::vector < float > m_arrflRGBA;
		std::string m_strFileNameTexture;

		AbstractGeomShapeParams();
	};

	class AbstractGeomShape	: public AbstractObject	{
	public:
		AbstractGeomShape();
		virtual ~AbstractGeomShape() {};

		virtual void init(const AbstractGeomShapeParams & aAbstractGeomShapeParams) = 0;

		virtual void setColor(const std::vector < float > & aarrflColor) = 0;
		virtual void setTexture(const std::string & astrFileName) = 0;

	};
}
#endif //VR_ABSTRACT_GEOM_SHAPE_H