#ifndef VR_PRODUCT_MANAGER_SERVER_H
#define VR_PRODUCT_MANAGER_SERVER_H

#include <string>
#include <vector>

namespace VR	{
	class BasketServer;
	class DatabaseInterface;
	struct DatabaseInterfaceParams;

	class ProductManagerServer	{

	public:
		const char* className() const;

		struct ProductManagerServerParams	{
			std::string m_strUserIDName;
			std::string m_strProductName;
			float m_flProductQuantity;
			float m_flProductNewQuantity;
		};

		std::string getProductDataFromDB(const std::string astrProductName);
		std::string getProductInfo(const std::string astrProductName);

		bool canFullfilRequest(std::string & astrBasketRequest);
		float tryAddProduct2Basket(const ProductManagerServerParams & aProductManagerServerParams);
		bool removeProduct(const ProductManagerServerParams & aProductManagerServerParams);
		float modifyProductQuantity(const ProductManagerServerParams & aProductManagerServerParams);

		void productViewedCounter(const std::string astrProductName);


	private:
		static DatabaseInterface * m_pDIProduct;

		static DatabaseInterfaceParams getDBParams();
		static std::string getTableName();
		static std::string getDatabaseName();

		static DatabaseInterface * getDatabaseInterface();

		static void createDB();

	public:
		static void constructStatics();
		static void deleteStatics();
	};
}
#endif //VR_PRODUCT_MANAGER_SERVER_H