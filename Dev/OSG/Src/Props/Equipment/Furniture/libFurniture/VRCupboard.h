#ifndef VR_CUPBOARD_H
#define VR_CUPBOARD_H

#include "VRFurniture.h"

namespace VR	{
	struct CupboardParams : public FurnitureParams	{
		CupboardParams();
	};

	class Cupboard : public Furniture	{
	public:
		Cupboard(const CupboardParams & aCupboardParams);
		Cupboard(const Cupboard& cup,const osg::CopyOp& copyop=osg::CopyOp::DEEP_COPY_ALL);

		virtual const char* className() const;
		virtual osg::Object* cloneType() const;
		virtual osg::Object* clone(const osg::CopyOp& copyop) const;

		virtual void init(const CupboardParams & aCupboardParams);
		virtual void predefinedObject();

		virtual std::string getSQLCommand() const;

		virtual void initFromSQLData(const std::string & astrSQLData);
	};
}
#endif //VR_CUPBOARD_H