#ifndef VR_CLIENT_SHOP_H
#define VR_CLIENT_SHOP_H

namespace VR	{
	class Client;
	class ShoppingPlace_GUI;
	
	struct ClientShop	{
		ClientShop();
		~ClientShop();

		bool initializeClient();
		bool createNewClientGUI();

	private:
		Client * m_pClient;
		ShoppingPlace_GUI * m_pShoppingPlace_GUI;
	};
}
#endif //VR_CLIENT_SHOP_H