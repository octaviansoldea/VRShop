#ifndef VR_PLATE_3D_H
#define VR_PLATE_3D_H

#include "VRAbstractGeomShape.h"
#include "VRUntransformedPlate3D.h"

class ostream;

namespace VR	{
	struct Plate3DParams : public AbstractGeomShapeParams	{
		Plate3DParams();
	};


	class Plate3D : public AbstractGeomShape	{
	private:
		static std::string m_strSQLFormat;

		osg::ref_ptr <UntransformedPlate3D> m_pUntransformedPlate3D;

	public:
		Plate3D();
		Plate3D(Plate3DParams * apPlate3DParams);
		Plate3D(const Plate3D& p3D,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);

		virtual const char* className() const;
		virtual osg::Object* cloneType() const { return new Plate3D(); }
		virtual osg::Object* clone(const osg::CopyOp& copyop) const { return new Plate3D(*this,copyop); }

		virtual std::string getSQLFormat() const;
		virtual std::string getSQLCommand() const;

		virtual void initFromSQLData(const std::string & astrSQLData);
		virtual void init(AbstractGeomShapeParams & aAbstractGeomShapeParams);

		virtual void predefinedObject();

		virtual void setColor(const std::vector < float > & aarrflColor);
		virtual void setTexture(const std::string & astrFileName);
	};
}
#endif //VR_PLATE_3D_H