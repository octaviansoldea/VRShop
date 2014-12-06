#ifndef VR_PRODUCT_CLIENT_MANAGER_H
#define VR_PRODUCT_CLIENT_MANAGER_H

#include <string>
#include <list>

#include <QObject>

#include "VRServerClientCommands.h"
#include "VRAbstractManagerClient.h"

namespace VR	{
	class ProductShopClient;
	class Client;

	class ProductManagerClient : public AbstractManagerClient	{
		Q_OBJECT
	public:
		ProductManagerClient(Client * apClient, QObject * apParent=0);
		virtual ~ProductManagerClient();

		const char* className() const;

		struct ProductManagerClientParams : public AbstractManagerClientParams	{
			ProductShopClient * m_pProduct;
			std::string m_strUserIDName;
			std::string m_strProductName;
			float m_flProductQuantity;
			float m_flProductNewQuantity;
		};

	protected:
		virtual void requestToServer(
			const ServerClientCommands::OPERATION_TYPE & aenumOperationType, 
			AbstractManagerClientParams * apAbstractManagerClientParams=0
		);

		
	private:
		std::list<ProductShopClient*> m_lstProducts;
		ProductShopClient * m_pProduct;

	signals:
		void signalProductInitialized(const std::string & astrProductData);
		void signalProductInitialized(const ProductShopClient * apProduct);

	public:
		ProductShopClient * getProduct();

		void productClicked(std::string & astrProductName);
		void addProduct2Basket(const std::string & astrUserID, ProductShopClient * apProductShopClient);
		void removeProductRequest(const std::string & astrUserID, ProductShopClient * apProduct);
		void modifyProductQuantityRequest(const std::string & astrUserID, ProductShopClient * apProduct, float aflNewQuantity);

		void addProduct2Basket(ProductManagerClientParams & aProductManagerClientParams);

		void initProductFromData(QDataStream & aDataStreamProduct, ProductShopClient * apProduct);
		bool addProduct2Basket(QDataStream & aDataStreamProduct, ProductShopClient * apProduct);
		ProductShopClient * removeProductFromBasket(QDataStream & aDataStreamProduct);
		float modifyProductQuantityRequest(QDataStream & aDataStreamProduct);
	};
}
#endif //VR_PRODUCT_CLIENT_MANAGER_H