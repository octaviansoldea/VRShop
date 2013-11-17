#ifndef VR_CUPBOARD_H
#define VR_CUPBOARD_H

#include <osg/MatrixTransform>
#include <QString>

namespace VR	{
	struct CupboardParams {
		float m_flPosX;
		float m_flPosY;
		float m_flPosZ;

		CupboardParams();
	};

	class Cupboard : public osg::MatrixTransform	{
	public:
		Cupboard();

		void setPos(const CupboardParams & aCupboardParams);

		void addPart(osg::ref_ptr < osg::Node > apNode);
		//void removePart(osg::Object * apObject);

		QString getSQLPrintCommand()	;
		void initFromSQLData(const std::string & astrSQLData);
	};
}
#endif //VR_CUPBOARD_H