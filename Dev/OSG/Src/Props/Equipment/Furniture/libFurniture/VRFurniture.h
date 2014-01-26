#ifndef VR_FURNITURE_H
#define VR_FURNITURE_H

#include <string>
#include <vector>

#include "VRAbstractObject.h"

namespace VR	{
	struct FurnitureParams : public AbstractObjectParams	{
		FurnitureParams();
	};

	class Furniture : public AbstractObject	{
	public:
		Furniture();
		Furniture(const FurnitureParams & aFurnitureParams);

		virtual void init(const FurnitureParams & aFurnitureParams) = 0;

		virtual void addPart(osg::ref_ptr < osg::Node > apNode);
		virtual void removePart(osg::ref_ptr < osg::Node > apNode);

		virtual std::string getSQLCommand() const;

		static void loadAllFurnitures(osg::ref_ptr<osg::Group> pScene, const std::string & astrDatabase);

	protected:
		std::vector < std::string > m_arrSQLCommandLines;
		FurnitureParams m_FurnitureParams;
	};
}
#endif //VR_FURNITURE_H