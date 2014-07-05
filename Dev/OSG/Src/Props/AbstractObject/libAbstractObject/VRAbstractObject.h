#ifndef VR_ABSTRACT_OBJECT_H
#define VR_ABSTRACT_OBJECT_H

#include <string>
#include <osg/MatrixTransform>

class ostream;

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
		AbstractObject(const AbstractObjectParams & aAbstractObjectParams);
		AbstractObject(const AbstractObject& ao,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY);

		virtual ~AbstractObject() = 0;

        virtual const char* className() const;
		virtual osg::Object* cloneType() const = 0;
		virtual osg::Object* clone(const osg::CopyOp& copyop) const = 0;

		static osg::ref_ptr<AbstractObject> createInstance(const std::string & astrClassName);

		virtual std::string getSQLFormat() const;
		virtual std::string getSQLCommand() const {return "";};

		virtual void initFromSQLData(const std::string & astrSQLData) = 0;
		virtual void initFromSQLData(std::vector<std::string> & avecstrSQLData);

		virtual void predefinedObject() = 0;

		virtual void setRotation(float aflAngleX, float aflAngleY, float aflAngleZ);
		virtual void setPosition(float aflPosX, float aflPosY, float aflPosZ);
		virtual void setScaling(float aflLenX, float aflLenY, float aflLenZ);

		osg::Vec3d getRotation() const;
		osg::Vec3d getPosition() const;
		osg::Vec3d getScaling() const;

		osg::Matrix calculateMatrix() const;

		void setIsTargetPick(bool abIsTargetPick);
		bool getIsTargetPick() const;

		virtual void writeObjectHierarchy(std::vector<std::string> &avecstrHierarchy);
		virtual void print(std::ostream & os) const;

		virtual std::string prepareRowData(const std::string & astrParentName="") = 0;
		virtual void preparedObjectData(std::vector<std::string> &avecItems, std::string & astrParent);


		virtual void setColor(const std::vector < float > & aarrflColor) = 0;
		virtual void setTexture(const std::string & astrFileName) = 0;

	protected:
		virtual void setParams(const AbstractObjectParams & aAbstractObjectParams);
		virtual void getParams(AbstractObjectParams & aAbstractObjectParams) const;

		unsigned long getAbstractObjectNo() const;

	private:
		bool m_bIsTargetPick;
		static std::string m_strSQLFormat;

		static unsigned long s_nAbstractObjectNo;

	protected:
		float m_flPosX;
		float m_flPosY;
		float m_flPosZ;

		float m_flLenX;
		float m_flLenY;
		float m_flLenZ;

		float m_flAngleYZ;
		float m_flAngleXZ;
		float m_flAngleXY;
	};
}
#endif //VR_ABSTRACT_OBJECT_H