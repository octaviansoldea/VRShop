#ifndef VR_BASKET_CLIENT_H
#define VR_BASKET_CLIENT_H

#include <list>

#include <QObject>

namespace VR	{
	class ProductShopClient;

	class BasketClient : public QObject {
		Q_OBJECT
	public:
		BasketClient();
		~BasketClient();

		const char* className() const;

		void addProduct(ProductShopClient * apProduct);
		void removeProduct(ProductShopClient * apProduct);
		void modifyQuantity(ProductShopClient * apProduct);

		float calculateBasketValue();

		int count() const;
		ProductShopClient * getProduct(std::string & astrProductName);
		ProductShopClient * getProduct(int anProductNumber);

		std::list<std::pair<long,float>> getBasketProductsAndQuantities();
		std::string getBasketIDQuantity2String();
	
	signals:
		void signalBasketChanged(const int & anIndex, bool abIsAdded);		//Emit this signal when adding a product

	private:
		std::list<ProductShopClient*> m_lstProducts;
	};
}
#endif //VR_BASKET_CLIENT_H