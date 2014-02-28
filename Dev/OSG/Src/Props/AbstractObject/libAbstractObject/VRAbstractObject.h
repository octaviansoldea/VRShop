#ifndef VR_ABSTRACT_OBJECT_H
#define VR_ABSTRACT_OBJECT_H

#include <string>
#include <osg/MatrixTransform>

namespace VR	{
	struct AbstractObjectParams	{
		float m_flPosX;
		float m_flPosY;
		float m_flPosZ;

		float m_flLenX;
		float m_flLenY;
		float m_flLenZ;

		float m_flAngleYZ;
		float m_flAngleXZ;
		float m_flAngleXY;

		AbstractObjectParams();
		virtual ~AbstractObjectParams();
	};

	class AbstractObject : public osg::MatrixTransform	{
	public:
		AbstractObject(AbstractObjectParams * pAbstractObjectParams = 0);

		virtual ~AbstractObject() = 0;

		static osg::ref_ptr<AbstractObject> createInstance(const std::string & astrClassName);

		virtual std::string getSQLFormat() const;
		virtual std::string getSQLCommand() const {return "";};

		virtual void initFromSQLData(const std::string & astrSQLData) = 0;
		virtual void predefinedObject() = 0;

		virtual void setRotation(float aflAngleX, float aflAngleY, float aflAngleZ);
		virtual void setPosition(float aflPosX, float aflPosY, float aflPosZ);
		virtual void setScaling(float aflLenX, float aflLenY, float aflLenZ);

		osg::Vec3d getRotation() const;
		osg::Vec3d getPosition() const;
		osg::Vec3d getScaling() const;

		osg::Matrix calculateMatrix() const;

		virtual void setIsTargetPick(bool abIsTargetPick);
		virtual bool getIsTargetPick() const;

	private:
		bool m_bIsTargetPick;
		static std::string m_strSQLFormat;

	protected:
		AbstractObjectParams * m_pAbstractObjectParams;
	};
}
#endif //VR_ABSTRACT_OBJECT_H