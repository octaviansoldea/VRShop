#ifndef VR_CUSTOM_FURNITURE_H
#define VR_CUSTOM_FURNITURE_H

#include "VRFurniture.h"

class ostream;

namespace VR	{
	struct CustomFurnitureParams : public FurnitureParams	{
	};

	class CustomFurniture : public Furniture	{
	public:
		CustomFurniture();
		CustomFurniture(CustomFurnitureParams * apCustomFurnitureParams);
		virtual const char* className() const;

		virtual void init(FurnitureParams * apFurnitureParams);

		virtual std::string getSQLCommand() const;

		virtual void initFromSQLData(const std::string & astrSQLData);

		virtual void predefinedObject();
		virtual void print(std::ostream & os) const;
	};
}
#endif //VR_CUSTOM_FURNITURE_H