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

		std::vector < float > m_arrflRGBA;
		std::string m_strFileNameTexture;
			
		PrismParams();
	};

	class Prism : public AbstractGeomShape	{
	public:
		Prism();
		Prism(const PrismParams & aPrismParams);

		virtual void init(const AbstractGeomShapeParams & aAbstractGeomShapeParams);
		virtual void predefinedObject() {};

		void setColor(const std::vector < float > & aarrflColor);
		void setTexture(const std::string & astrFileName);
		void setResolution(int anRes);

		virtual std::string getSQLFormat() const;
		virtual std::string getSQLCommand() const;

		virtual void initFromSQLData(const std::string & astrSQLData);

		osg::ref_ptr <UntransformedPolygon3D> m_pUntransformedPolygon3D;
	protected: 
		PrismParams m_PrismParams;
	private:
		static std::string m_strSQLFormat;
	};
}

#endif //VR_PRISM_H