#ifndef VR_PRODUCT_CLIENT_MANAGER_H
#define VR_PRODUCT_CLIENT_MANAGER_H

#include <string>
#include <list>

#include <QObject>

namespace VR	{
	class Client;
	class ProductShopClient;

	class ProductManagerClient : public QObject	{
		Q_OBJECT
	public:
		ProductManagerClient();
		~ProductManagerClient();

		const char* className() const;
		
		void initProduct(const std::string & astrProductName);
		ProductShopClient * getProduct();

		void requestProductParams(const std::string & astrProductName);
		
	private:
		std::list<ProductShopClient*> m_lstProducts;
		ProductShopClient * m_pProduct;

		Client * m_pClient;

	private slots:
		void slotReceiveProductParams();

	signals:
		void signalProductInitialized();

	};
}
#endif //VR_PRODUCT_CLIENT_MANAGER_H