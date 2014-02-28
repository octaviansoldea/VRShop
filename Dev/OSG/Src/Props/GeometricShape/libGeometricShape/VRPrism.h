#ifndef VR_PRISM_H
#define VR_PRISM_H

#include "VRAbstractGeomShape.h"

#include "VRUntransformedPolygon3D.h"

namespace VR {
	struct PrismParams : public AbstractGeomShapeParams, public UntransformedPolygon3DParams {
		PrismParams();
	};

	class Prism : public AbstractGeomShape	{
	public:
		Prism();
		Prism(PrismParams * apPrismParams);

		virtual void init(AbstractGeomShapeParams & aAbstractGeomShapeParams);
		virtual void predefinedObject();

		virtual void setColor(const std::vector < float > & aarrflColor);
		virtual void setTexture(const std::string & astrFileName);
		void setResolution(int anRes);

		virtual std::string getSQLFormat() const;
		virtual std::string getSQLCommand() const;

		virtual void initFromSQLData(const std::string & astrSQLData);

		osg::ref_ptr <UntransformedPolygon3D> m_pUntransformedPolygon3D;

	private:
		static std::string m_strSQLFormat;
	};
}

#endif //VR_PRISM_H