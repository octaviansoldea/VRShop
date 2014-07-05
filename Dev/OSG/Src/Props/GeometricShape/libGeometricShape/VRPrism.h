#ifndef VR_PRISM_H
#define VR_PRISM_H

#include "VRAbstractGeomShape.h"
#include "VRUntransformedPolyhedron.h"

class ostream;

namespace VR {
	struct PrismParams : public AbstractGeomShapeParams, public UntransformedPolyhedronParams {
		PrismParams();
	};

	class Prism : public AbstractGeomShape	{
	public:
		Prism(const PrismParams & aPrismParams);
		Prism(const Prism& pr,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);

		virtual const char* className() const;
		virtual osg::Object* cloneType() const;
		virtual osg::Object* clone(const osg::CopyOp& copyop) const;

		virtual void init(const PrismParams & aPrismParams);
		virtual void predefinedObject();

		virtual void setColor(const std::vector < float > & aarrflColor);
		virtual void setTexture(const std::string & astrFileName);

		virtual std::string getSQLFormat() const;
		virtual std::string getSQLCommand() const;

		virtual void initFromSQLData(const std::string & astrSQLData);

		osg::ref_ptr <UntransformedPolyhedron> m_pUntransformedPolyhedron;

		virtual std::string prepareRowData(const std::string & astrParentName="");


	private:
		static std::string m_strSQLFormat;

	protected:		
		virtual void setParams(const PrismParams & aPrismParams);
		virtual void getParams(PrismParams & aPrismParams) const;
	};
}

#endif //VR_PRISM_H