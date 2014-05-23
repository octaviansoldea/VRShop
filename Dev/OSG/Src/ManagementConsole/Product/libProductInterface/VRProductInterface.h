#ifndef VR_PRODUCT_INTERFACE_H
#define VR_PRODUCT_INTERFACE_H

#include <QObject>

#include "VRProductManagerClient.h"

class QFrame;
class QLabel;
class QPushButton;

#include <string>

namespace VR	{
	class ProductShopClient;
	class Product;
	class PickAndDragHandlerShopClient;

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
			PickAndDragHandlerShopClient * apPickAndDragHandlerShopClient
		);	//End of constructor

		~ProductInterface();

		void init(const ProductShopClient * apProductShopClient);
		void init(const std::string & astrProductName);

	private:
		QFrame * m_pFrameProductInterface;
		QLabel * m_pLabelProductInterfaceImage;
		QLabel * m_pLabelProductInterfaceInfo;
		QPushButton * m_pPushButtonProductInterface2Basket;
		QPushButton * m_pPushButtonProductInterfaceDetails;
		QLabel * m_pLabelProductInterfacePrice;
		PickAndDragHandlerShopClient * m_pPickAndDragHandlerShopClient;

		ProductShopClient * m_pProductShopClient;
		ProductManagerClient m_ProductMgrClient;

		void setGeometry();

	private slots:
		void slotAdd2Basket();
		void slotProductDetails();
		void slotGetProduct();

		void slotCloseInterface();
	};
}
#endif //VR_PRODUCT_INTERFACE_H