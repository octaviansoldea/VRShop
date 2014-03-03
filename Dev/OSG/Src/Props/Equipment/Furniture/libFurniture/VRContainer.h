#ifndef VR_CONTAINER_H
#define VR_CONTAINER_H

#include "VRFurniture.h"

class ostream;

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
		Container(ContainerParams * apContainerParams);
		virtual const char* className() const;

		virtual void init(FurnitureParams * apFurnitureParams);
		virtual void predefinedObject();

		virtual std::string getSQLCommand() const;

		virtual void initFromSQLData(const std::string & astrSQLData);
		virtual void print(std::ostream & os) const;
	};
}
#endif //VR_CONTAINER_H