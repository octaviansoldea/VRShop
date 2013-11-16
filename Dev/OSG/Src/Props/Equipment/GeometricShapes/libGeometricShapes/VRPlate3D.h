#ifndef VR_PLATE_3D_H
#define VR_PLATE_3D_H

#include <osg/MatrixTransform>

#include "VRAbstractGeomShape.h"
#include "VRUntransformedPlate3D.h"

namespace VR	{
	struct Plate3DParams : public AbstractGeomShapeParams	{
		float m_flLenX;
		float m_flLenY;
		float m_flLenZ;
		float m_flPosX;
		float m_flPosY;
		float m_flPosZ;

		float m_flRGBA[4];

		const char * m_pchFileName;

		Plate3DParams();
	};


	class Plate3D : public AbstractGeomShape, public osg::MatrixTransform {

		osg::ref_ptr <UntransformedPlate3D> m_pUntransformedPlate3D;

	public:
		Plate3D();

		virtual std::string getSQLCommand(const AbstractGeomShapeParams & aAbstractGeomShapeParams) const;
		virtual void initFromSQLData(const std::string & astrSQLData);
		virtual void init(const AbstractGeomShapeParams & aAbstractGeomShapeParams);

		void setColor(const float aarrflColor[4]);
		void setTexture(const char * apchFileName);

	};
}
#endif //VR_PLATE_3D_H