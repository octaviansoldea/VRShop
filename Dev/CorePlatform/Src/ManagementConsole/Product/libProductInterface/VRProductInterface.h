#ifndef VR_PRODUCT_INTERFACE_H
#define VR_PRODUCT_INTERFACE_H

#include <QObject>

#include "VRProductShopClient.h"

class QFrame;
class QLabel;
class QPushButton;

namespace VR	{
	class Client;

	class ProductInterface : public QObject	{
		Q_OBJECT
	public:
		ProductInterface(
			QFrame * apFrameProductInterface,
			QLabel * apLabelProductInterfaceImage,
			QLabel * apLabelProductInterfaceInfo,
			QPushButton * apPushButtonProductInterface2Basket,
			QPushButton * apPushButtonProductInterfaceDetails,
			QLabel * apLabelProductInterfacePrice,
			Client * apClient
		);	//End of constructor

	private:
		QFrame * m_pFrameProductInterface;
		QLabel * m_pLabelProductInterfaceImage;
		QLabel * m_pLabelProductInterfaceInfo;
		QPushButton * m_pPushButtonProductInterface2Basket;
		QPushButton * m_pPushButtonProductInterfaceDetails;
		QLabel * m_pLabelProductInterfacePrice;

		Client * m_pClient;

		ProductShopClient m_ProductShopClient;

		void init(const ProductShopClient * apProductShopClient);

	private slots:
		void slotProductDetails();
		void slotCloseInterface();

	public:
		ProductShopClient * getProduct();

		void productClicked(const std::string & astrProductName);
		void removeProductRequest(ProductShopClient * apProduct);

		void productClickedRespond(QDataStream & aDataStream);
	};
}
#endif //VR_PRODUCT_INTERFACE_H