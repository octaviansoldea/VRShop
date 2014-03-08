#ifndef VR_PRISM_H
#define VR_PRISM_H

#include "VRAbstractGeomShape.h"

#include "VRUntransformedPolygon3D.h"

class ostream;

namespace VR {
	struct PrismParams : public AbstractGeomShapeParams, public UntransformedPolygon3DParams {
		PrismParams();
	};

	class Prism : public AbstractGeomShape	{
	public:
		Prism();
		Prism(PrismParams * apPrismParams);
		Prism(const Prism& pr,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);

		virtual const char* className() const;
		virtual osg::Object* cloneType() const { return new Prism(); }
		virtual osg::Object* clone(const osg::CopyOp& copyop) const { return new Prism(*this,copyop); }

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