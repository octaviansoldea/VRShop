#ifndef VR_ABSTRACT_OBJECT_H
#define VR_ABSTRACT_OBJECT_H

#include <string>

namespace VR	{
	struct AbstractObjectParams	{
		float m_flPosX;
		float m_flPosY;
		float m_flPosZ;

		float m_flScaleX;
		float m_flScaleY;
		float m_flScaleZ;

		float m_flAngleXY;
		float m_flAngleXZ;
		float m_flAngleYZ;

		AbstractObjectParams();
	};

	class AbstractObject {
	public:
		AbstractObject();
		AbstractObject(const AbstractObjectParams & aAbstractObjectParams);

		virtual std::string getSQLFormat() const;

		virtual std::string getSQLCommand() const = 0;
		virtual void initFromSQLData(const std::string & astrSQLData) = 0;

		virtual void setRotation(const AbstractObjectParams & aAbstractObjectParams);
		virtual void setPosition(const AbstractObjectParams & aAbstractObjectParams);
		virtual void setScaling(const AbstractObjectParams & aAbstractObjectParams);

		virtual void setIsTargetPick(bool abIsTargetPick);
		virtual bool getIsTargetPick() const;

	private:
		bool m_bIsTargetPick;
		static std::string m_strSQLFormat;

	protected:
		AbstractObjectParams m_AbstractObjectParams;
	};
}
#endif //VR_ABSTRACT_OBJECT_H