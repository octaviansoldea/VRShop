#ifndef VR_CUPBOARD_H
#define VR_CUPBOARD_H

#include <osg/MatrixTransform>
#include <QString>

#include "VRAbstractObject.h"
#include "VRAbstractGeomShape.h"

namespace VR	{
	struct CupboardParams {
		float m_flPosX;
		float m_flPosY;
		float m_flPosZ;

		CupboardParams();
	};

	class Cupboard : public AbstractObject, public osg::MatrixTransform	{
	public:
		Cupboard();

		void addPart(osg::ref_ptr < osg::Node > apNode);
		void removePart(osg::ref_ptr < osg::Node > apNode);

		void init(const CupboardParams & aCupboardParams);

		virtual std::string getSQLFormat() const;

		std::string getSQLPrintCommand();
		void initFromSQLData(const std::string & astrSQLData);

	private:
		std::vector < std::string > m_arrSQLCommandLines;
	};
}
#endif //VR_CUPBOARD_H