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
		AbstractGeomShape(const AbstractGeomShapeParams & aAbstractGeomShapeParams);
		AbstractGeomShape(const AbstractGeomShape& ags,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);

		virtual const char* className() const;

		virtual ~AbstractGeomShape() = 0;

		virtual void setColor(const std::vector < float > & aarrflColor) = 0;
		virtual void setTexture(const std::string & astrFileName) = 0;


	protected:
		virtual void setParams(const AbstractGeomShapeParams & aAbstractGeomShapeParams);
		virtual void getParams(AbstractGeomShapeParams & aAbstractGeomShapeParams) const;

		std::vector < float > m_arrflRGBA;
		std::string m_strFileNameTexture;


	};
}
#endif //VR_ABSTRACT_GEOM_SHAPE_H