#ifndef VR_CONTAINER_H
#define VR_CONTAINER_H

#include <QString>

#include "VRFurniture.h"

namespace VR	{
	struct ContainerParams : FurnitureParams	{
		ContainerParams();
	};

	class Container : public Furniture	{
	public:
		Container();
		Container(const ContainerParams & aContainerParams);

		void init(const ContainerParams & aContainerParams);

		std::string setSQLCommand(const std::string & astrCommand);
		virtual std::string getSQLCommand() const;

		virtual void initFromSQLData(const std::string & astrSQLData);

	private:
		ContainerParams m_ContainerParams;
	};
}
#endif //VR_CONTAINER_H