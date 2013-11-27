#ifndef VR_FURNITURE_H
#define VR_FURNITURE_H

#include <string>
#include <osg/Group>
#include <osg/MatrixTransform>

#include "VRAbstractObject.h"

namespace VR	{
	struct FurnitureParams : public AbstractObjectParams	{
		FurnitureParams();
	};

	class Furniture : public osg::MatrixTransform, public AbstractObject	{
	public:
		Furniture();
		Furniture(const FurnitureParams & aFurnitureParams);

		virtual void addPart(osg::ref_ptr < osg::Node > apNode);
		virtual void removePart(osg::ref_ptr < osg::Node > apNode);

		static void loadAllFurnitures(osg::ref_ptr<osg::Group> pScene, const std::string & astrDatabase);

	protected:
		std::vector < std::string > m_arrSQLCommandLines;
		FurnitureParams m_FurnitureParams;
	};
}
#endif //VR_FURNITURE_H