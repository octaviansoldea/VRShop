#ifndef VR_BASKET_H
#define VR_BASKET_H

#include <list>

#include <QObject>

namespace VR	{
	class ProductShopClient;

	class Basket : public QObject {
		Q_OBJECT
	public:
		Basket();
		~Basket();

		const char* className() const;

		void addProduct(ProductShopClient * apProduct);
		void removeProduct(ProductShopClient * apProduct);
		void modifyQuantity(ProductShopClient * apProduct);

		float calculateBasketValue() const;

		Basket * getBasket() const;

		int count() const;
		ProductShopClient * getProduct(std::string & astrProductName);
		ProductShopClient * getProduct(int anProductNumber);

	signals:
		void signalBasketChanged(const int & anIndex, bool abIsAdded);		//Emit this signal when adding a product

	private:
		std::list<ProductShopClient*> m_lstBasket;
	};
}
#endif //VR_BASKET_H