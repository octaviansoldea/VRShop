#ifndef VR_CUPBOARD_H
#define VR_CUPBOARD_H

#include <osg/MatrixTransform>
#include <QString>

#include "VRAbstractObject.h"

namespace VR	{
	struct CupboardParams {
		float m_flPosX;
		float m_flPosY;
		float m_flPosZ;

		float m_flScaleX;
		float m_flScaleY;
		float m_flScaleZ;

		float m_flAngleXY;
		float m_flAngleXZ;
		float m_flAngleYZ;

		CupboardParams();
	};

	class Cupboard : public AbstractObject, public osg::MatrixTransform	{
	public:
		Cupboard();

		void addPart(osg::ref_ptr < osg::Node > apNode);
		void removePart(osg::ref_ptr < osg::Node > apNode);

		void init(const CupboardParams & aCupboardParams);

		virtual std::string getSQLFormat() const;

		std::string setSQLCommand(const std::string & astrCommand);

		virtual std::string getSQLCommand() const;
		virtual void initFromSQLData(const std::string & astrSQLData);

		osg::ref_ptr <VR::Cupboard> m_Cupboard;

		void setRotation(const CupboardParams & aCupboardParams);
		void setPosition(const CupboardParams & aCupboardParams);
		void setScaling(const CupboardParams & aCupboardParams);

	private:
		std::vector < std::string > m_arrSQLCommandLines;
		CupboardParams m_CupboardParams;
	};
}
#endif //VR_CUPBOARD_H