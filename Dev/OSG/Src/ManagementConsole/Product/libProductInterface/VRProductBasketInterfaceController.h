#ifndef VR_PRODUCT_BASKET_INTERFACE_CONTROLLER_H
#define VR_PRODUCT_BASKET_INTERFACE_CONTROLLER_H

namespace VR	{
	class ProductShopClient;
	class Basket;

	class ProductBasketInterfaceController	{
	public:
		ProductBasketInterfaceController(Basket * apBasket);
		~ProductBasketInterfaceController();

		void removeProduct(ProductShopClient * apProductShopClient);
		void setQuantity(float aflQuantity);

	private:
		Basket * m_pBasket;
	};
}
#endif //VR_PRODUCT_BASKET_INTERFACE_CONTROLLER_H