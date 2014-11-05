#ifndef VR_SHOP_BUILDER_COMMANDS_H
#define VR_SHOP_BUILDER_COMMANDS_H

#include <string>

namespace VR	{
	class ShopBuilderCommands	{
	public:

		enum OBJECT_NAME	{
			PRODUCT = 0,
			PRODUCT_DISPLAY,
			GRID
		};

		static std::string getOperationType(enum OBJECT_NAME aenumOBJECT_NAME);
	};
}
#endif //VR_SHOP_BUILDER_COMMANDS_H