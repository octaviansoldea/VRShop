#ifndef VR_SHOP_BUILDER_COMMANDS_H
#define VR_SHOP_BUILDER_COMMANDS_H

#include <string>

namespace VR	{
	class ShopBuilderCommands	{
	public:

		enum ObjectName	{
			PRODUCT = 0,
			PRODUCT_DISPLAY,
			GRID
		};

		static std::string getOperationType(const ObjectName & aObjectName);
	};
}
#endif //VR_SHOP_BUILDER_COMMANDS_H