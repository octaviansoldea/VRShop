#ifndef VR_FURNITURE_H
#define VR_FURNITURE_H

#include <vector>

#include "VRAbstractObject.h"

namespace VR	{
	struct FurnitureParams : public AbstractObjectParams	{
		FurnitureParams();
	};

	class Furniture : public AbstractObject	{
	protected:
		virtual ~Furniture() = 0;

	public:
		Furniture(const FurnitureParams & aFurnitureParams);
		Furniture(const Furniture& fur,const osg::CopyOp& copyop=osg::CopyOp::DEEP_COPY_ALL);

		virtual const char* className() const;

		virtual void addPart(osg::ref_ptr < AbstractObject > apAbstractObject);
		virtual void removePart(unsigned int anPartNo);
		virtual void removePart(osg::ref_ptr < AbstractObject > apAbstractObject);

		virtual std::string getSQLCommand() const;

		static void loadAllFurnitures(osg::ref_ptr<osg::Group> pScene, const std::string & astrDatabase);
		virtual void initFromSQLData(std::vector<std::string> & avecstrSQLData);

		virtual std::string prepareRowData(const std::string & astrParentName="");

		virtual void setColor(const std::vector < float > & aarrflColor);
		virtual void setTexture(const std::string & astrFileName);

		virtual void setParams(const AbstractObjectParams & aAbstractObjectParams);

	protected:
		void getParams(FurnitureParams & aFurnitureParams) const;

		std::vector < std::string > m_arrSQLCommandLines;
	};
}
#endif //VR_FURNITURE_H
