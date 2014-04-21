#ifndef VR_PRODUCT_INTERFACE_H
#define VR_PRODUCT_INTERFACE_H

#include <QObject>

class QFrame;
class QLabel;
class QPushButton;

namespace VR	{
	class Product;

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

		~ProductInterface();

		void initProductInterface(const Product * apProduct);

	private slots:

	private:
		QFrame * m_pFrameProductInterface;
		QLabel * m_pLabelProductInterfaceImage;
		QLabel * m_pLabelProductInterfaceInfo;
		QPushButton * m_pPushButtonProductInterface2Basket;
		QPushButton * m_pPushButtonProductInterfaceDetails;
		QLabel * m_pLabelProductInterfacePrice;


		Product * m_pProduct;
	};
}
#endif //VR_PRODUCT_INTERFACE_H