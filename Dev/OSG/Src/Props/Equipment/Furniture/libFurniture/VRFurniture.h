#ifndef VR_FURNITURE_H
#define VR_FURNITURE_H

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
        
		virtual ~Furniture() = 0;

		virtual void init(const FurnitureParams & aFurnitureParams) = 0;

		virtual void addPart(osg::ref_ptr < AbstractObject > apAbstractObject);
		virtual void removePart(unsigned int anPartNo);
		virtual void removePart(osg::ref_ptr < AbstractObject > &apAbstractObject);

		
		void splitObject2Children(std::vector< osg::ref_ptr<AbstractObject> > &aarrpChildren);

		virtual std::string getSQLCommand() const;

		static void loadAllFurnitures(osg::ref_ptr<osg::Group> pScene, const std::string & astrDatabase);

	protected:
		std::vector < std::string > m_arrSQLCommandLines;
		FurnitureParams m_FurnitureParams;
	};
}
#endif //VR_FURNITURE_H
