#ifndef VR_BASKET_SERVER_H
#define VR_BASKET_SERVER_H

#include <string>
#include <vector>
#include <list>

namespace VR	{
	class ProductServer;

	class BasketServer	{
	public:
		const char* className() const;

		static BasketServer * createBasketServer(std::vector<std::string> & avecstrBasketData);

	private:
//		std::list<ProductShopClient*> m_lstProducts;
		std::list<std::pair<long,float>> m_lstBasketServer;	//pair - 1: ProductID; pair - 2: quantity
	};
}
#endif //VR_BASKET_SERVER_H