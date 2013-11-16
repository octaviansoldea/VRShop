#ifndef VR_PRISM_H
#define VR_PRISM_H

#include <osg/MatrixTransform>

#include "VRAbstractGeomShape.h"

#include "VRUntransformedPolygon3D.h"

namespace VR {
	struct PrismParams : public AbstractGeomShapeParams {
		float m_flRadius;
		float m_flHeight;
		int m_nRes;

		float m_flPosX;
		float m_flPosY;
		float m_flPosZ;

		float m_arrflRGBA[4];
		const char * m_pchFileName;
			
		PrismParams();
	};

	class Prism : public AbstractGeomShape, public osg::MatrixTransform {
	public:
		Prism();
		Prism(const PrismParams & aPrismParams);

		virtual void init(const AbstractGeomShapeParams & aAbstractGeomShapeParams);

		void setColor(const float aarrflColor[4]);
		void setResolution(int anRes);
		void setTexture(const char * apchFileName);

		virtual std::string getSQLCommand(const AbstractGeomShapeParams & aAbstractGeomShapeParams) const;
		virtual void initFromSQLData(const std::string & astrSQLData);

		osg::ref_ptr <UntransformedPolygon3D> m_pUntransformedPolygon3D;
	};
}

#endif //VR_PRISM_H