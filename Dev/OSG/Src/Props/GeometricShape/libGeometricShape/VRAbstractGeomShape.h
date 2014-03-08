#ifndef VR_ABSTRACT_GEOM_SHAPE_H
#define VR_ABSTRACT_GEOM_SHAPE_H

#include "VRAbstractObject.h"

namespace VR {
	struct AbstractGeomShapeParams : public AbstractObjectParams	{
		std::vector < float > m_arrflRGBA;
		std::string m_strFileNameTexture;

		AbstractGeomShapeParams();
	};

	class AbstractGeomShape	: public AbstractObject	{
	public:
		AbstractGeomShape();
		AbstractGeomShape(AbstractGeomShapeParams * apAbstractGeomShapeParams);
		AbstractGeomShape(const AbstractGeomShape& ags,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);

		virtual const char* className() const {return "AbstractGeomShape";};

		virtual ~AbstractGeomShape() = 0;

		virtual void init(AbstractGeomShapeParams & aAbstractGeomShapeParams) = 0;

		virtual void setColor(const std::vector < float > & aarrflColor) = 0;
		virtual void setTexture(const std::string & astrFileName) = 0;
	};
}
#endif //VR_ABSTRACT_GEOM_SHAPE_H