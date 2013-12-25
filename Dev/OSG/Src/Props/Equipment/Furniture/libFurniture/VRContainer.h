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
		Container();
		Container(const ContainerParams & aContainerParams);

		virtual void init(const FurnitureParams & aFurnitureParams);
		virtual void predefinedObject();

		std::string setSQLCommand(const std::string & astrCommand);
		virtual std::string getSQLCommand() const;

		virtual void initFromSQLData(const std::string & astrSQLData);

	private:
		ContainerParams m_ContainerParams;
	};
}
#endif //VR_CONTAINER_H