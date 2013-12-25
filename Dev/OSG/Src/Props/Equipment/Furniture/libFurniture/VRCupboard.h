#ifndef VR_CUPBOARD_H
#define VR_CUPBOARD_H

#include "VRFurniture.h"

namespace VR	{
	struct CupboardParams : public FurnitureParams	{
		CupboardParams();
	};

	class Cupboard : public Furniture	{
	public:
		Cupboard();
		Cupboard(const CupboardParams & aCupboardParams);

		virtual void init(const FurnitureParams & aFurnitureParams);
		virtual void predefinedObject();

		std::string setSQLCommand(const std::string & astrCommand);
		virtual std::string getSQLCommand() const;

		virtual void initFromSQLData(const std::string & astrSQLData);


	private:
		CupboardParams m_CupboardParams;
	};
}
#endif //VR_CUPBOARD_H