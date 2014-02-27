#ifndef VR_CUSTOM_FURNITURE_H
#define VR_CUSTOM_FURNITURE_H

#include "VRFurniture.h"

namespace VR	{
	struct CustomFurnitureParams : public FurnitureParams	{
	};

	class CustomFurniture : public Furniture	{
	public:
		CustomFurniture();
		CustomFurniture(CustomFurnitureParams * apCustomFurnitureParams);

		virtual void init(FurnitureParams & aFurnitureParams);

		virtual std::string getSQLCommand() const;

		virtual void initFromSQLData(const std::string & astrSQLData);

		virtual void predefinedObject();
	};
}
#endif //VR_CUSTOM_FURNITURE_H