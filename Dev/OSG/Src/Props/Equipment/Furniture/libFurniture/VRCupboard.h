#ifndef VR_CUPBOARD_H
#define VR_CUPBOARD_H

#include "VRFurniture.h"

class ostream;

namespace VR	{
	struct CupboardParams : public FurnitureParams	{
		CupboardParams();
	};

	class Cupboard : public Furniture	{
	public:
		Cupboard();
		Cupboard(CupboardParams * apCupboardParams);
		virtual const char* className() const;

		virtual void init(FurnitureParams * apFurnitureParams);
		virtual void predefinedObject();

		virtual std::string getSQLCommand() const;

		virtual void initFromSQLData(const std::string & astrSQLData);
		virtual void print(std::ostream & os) const;
	};
}
#endif //VR_CUPBOARD_H