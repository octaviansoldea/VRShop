#ifndef VR_CUSTOM_FURNITURE_H
#define VR_CUSTOM_FURNITURE_H

#include "VRFurniture.h"

class ostream;

namespace VR	{
	struct CustomFurnitureParams : public FurnitureParams	{
	};

	class CustomFurniture : public Furniture	{
	public:
		CustomFurniture(const CustomFurnitureParams & aCustomFurnitureParams);
		CustomFurniture(const CustomFurniture& cf,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);

		virtual const char* className() const;
		virtual osg::Object* cloneType() const;
		virtual osg::Object* clone(const osg::CopyOp& copyop) const;

		virtual void init(const CustomFurnitureParams & aCustomFurnitureParams);

		virtual std::string getSQLCommand() const;

		virtual void initFromSQLData(const std::string & astrSQLData);

		virtual void predefinedObject();
	};
}
#endif //VR_CUSTOM_FURNITURE_H