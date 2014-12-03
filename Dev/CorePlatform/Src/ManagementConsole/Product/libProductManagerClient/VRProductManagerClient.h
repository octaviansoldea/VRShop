#ifndef VR_PRODUCT_CLIENT_MANAGER_H
#define VR_PRODUCT_CLIENT_MANAGER_H

#include <string>
#include <list>

#include <QObject>

#include "VRServerClientCommands.h"
#include "VRAbstractManagerClient.h"

namespace VR	{
	class BasketClient;
	class ProductShopClient;
	class ModelViewControllerClient;

	class ProductManagerClient : public AbstractManagerClient	{
		Q_OBJECT
	public:
		ProductManagerClient(ModelViewControllerClient * apMVCClient, BasketClient * apBasketClient=0, QObject * apParent=0);
		virtual ~ProductManagerClient();

		const char* className() const;

		struct ProductManagerClientParams : public AbstractManagerClientParams	{
			ProductShopClient * m_pProduct;
			std::string m_strUserIDName;
			std::string m_strProductName;
			float m_flProductQuantity;
			float m_flProductNewQuantity;
		};

		virtual void requestToServer(
			const ServerClientCommands::OPERATION_TYPE & aenumOperationType, 
			AbstractManagerClientParams * apAbstractManagerClientParams=0
		);

		ProductShopClient * getProduct();
		
	private:
		std::list<ProductShopClient*> m_lstProducts;
		ProductShopClient * m_pProduct;
		BasketClient * m_pBasket;
		ModelViewControllerClient * m_pMVCClient;


	signals:
		void signalProductInitialized(const std::string & astrProductData);
		void signalProductInitialized(const ProductShopClient * apProduct);

	public:
		virtual void slotReceiveDataFromServer();

		void productClicked(std::string & astrProductName);
		void addProduct2Basket(const std::string & astrUserID, ProductShopClient * apProductShopClient);
		void removeProductRequest(const std::string & astrUserID, ProductShopClient * apProduct);
		void modifyProductQuantityRequest(const std::string & astrUserID, ProductShopClient * apProduct, float aflNewQuantity);

		void addProduct2Basket(ProductManagerClientParams & aProductManagerClientParams);
	};
}
#endif //VR_PRODUCT_CLIENT_MANAGER_H