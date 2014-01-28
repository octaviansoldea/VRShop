#ifndef VR_PRISM_H
#define VR_PRISM_H

#include "VRAbstractGeomShape.h"

#include "VRUntransformedPolygon3D.h"

namespace VR {
	struct PrismParams : public AbstractGeomShapeParams {
		float m_flRadius;
		float m_flHeight;
		int m_nRes;

		PrismParams();
	};

	class Prism : public AbstractGeomShape	{
	public:
		Prism();
		Prism(const PrismParams & aPrismParams);

		virtual void init(const AbstractGeomShapeParams & aAbstractGeomShapeParams);
		virtual void predefinedObject();

		virtual void setColor(const std::vector < float > & aarrflColor);
		virtual void setTexture(const std::string & astrFileName);
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