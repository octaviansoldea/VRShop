#ifndef VR_CONTAINER_H
#define VR_CONTAINER_H

#include "VRFurniture.h"

namespace VR	{
	struct ContainerParams : public FurnitureParams	{
		ContainerParams();

		float m_flWidth;
		float m_flHeight;
		float m_flDepth;
		float m_flThickness;
	};

	class Container : public Furniture	{
	public:
		Container(const ContainerParams & aContainerParams);
		Container(const Container& cont,const osg::CopyOp& copyop=osg::CopyOp::DEEP_COPY_ALL);

		virtual const char* className() const;
		virtual osg::Object* cloneType() const;
		virtual osg::Object* clone(const osg::CopyOp& copyop) const;

		virtual void init(const ContainerParams & aContainerParams);
		virtual void predefinedObject();

		virtual std::string getSQLCommand() const;

		virtual void initFromSQLData(const std::string & astrSQLData);

		void setParams(const ContainerParams & aContainerParams);
		void getParams(ContainerParams & aContainerParams) const;

	private:
		float m_flWidth;
		float m_flHeight;
		float m_flDepth;
		float m_flThickness;
	};
}
#endif //VR_CONTAINER_H