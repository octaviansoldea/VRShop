#ifndef VR_PRODUCT_INTERFACE_H
#define VR_PRODUCT_INTERFACE_H

#include <QObject>

#include "VRProductShopClient.h"

class QFrame;
class QLabel;
class QPushButton;

namespace VR	{
	class ProductInterface : public QObject	{
		Q_OBJECT
	public:
		ProductInterface(
			QFrame * apFrameProductInterface,
			QLabel * apLabelProductInterfaceImage,
			QLabel * apLabelProductInterfaceInfo,
			QPushButton * apPushButtonProductInterface2Basket,
			QPushButton * apPushButtonProductInterfaceDetails,
			QLabel * apLabelProductInterfacePrice
		);	//End of constructor

	private:
		QFrame * m_pFrameProductInterface;
		QLabel * m_pLabelProductInterfaceImage;
		QLabel * m_pLabelProductInterfaceInfo;
		QPushButton * m_pPushButtonProductInterface2Basket;
		QPushButton * m_pPushButtonProductInterfaceDetails;
		QLabel * m_pLabelProductInterfacePrice;

		ProductShopClient m_ProductShopClient;

		void init(const ProductShopClient * apProductShopClient);
		void setGeometry();

	private slots:
		void slotProductDetails();
		void slotCloseInterface();

	public slots:
		void slotProductInitialized(const ProductShopClient * apProductShopClient);

	public:
		ProductShopClient * getProduct();
	};
}
#endif //VR_PRODUCT_INTERFACE_H