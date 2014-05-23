#ifndef VR_PRODUCT_BASKET_INTERFACE_H
#define VR_PRODUCT_BASKET_INTERFACE_H

#include <QObject>
#include <list>

#include "VRProductBasketInterfaceItem.h"

class QDoubleSpinBox;
class QFrame;
class QLabel;
class QPushButton;
class QToolButton;

namespace VR	{
	class VRQFrame;
	class ProductShopClient;

	class ProductBasketInterface : public QObject	{
		Q_OBJECT
	public:
		ProductBasketInterface(
			QToolButton * apToolButtonMyBasket,
			QLabel * apLabelBasketCase,
			QFrame * apFrameItemsBasket,
//			QFrame * apFrameProductItem,
			VRQFrame * apVRQFrameProductItem,
			QFrame * apFrameProductItemHover,
			QDoubleSpinBox * apDoubleSpinBoxQuantity,
			QPushButton * apPushButtonDetails,
			QPushButton * apPushButtonRemove,
			QLabel * apLabelProductImage,
			QLabel * apLabelProductInfo,
			QLabel * apLabelBasketProductPrice,
			QPushButton * apPushButtonBasketBack,
			QPushButton * apPushButtonBasketForward
		);	//End of constructor

		~ProductBasketInterface();

	private:
		QToolButton * m_pToolButtonMyBasket;
		QLabel * m_pLabelBasketCase;
		QFrame * m_pFrameItemsBasket;
//		QFrame * m_pFrameProductItem;
		VRQFrame * m_pVRQFrameProductItem;
		QFrame * m_pFrameProductItemHover;
		QDoubleSpinBox * m_pDoubleSpinBoxQuantity;
		QPushButton * m_pPushButtonDetails;
		QPushButton * m_pPushButtonRemove;
		QLabel * m_pLabelProductImage;
		QLabel * m_pLabelProductInfo;
		QLabel * m_pLabelBasketProductPrice;

		QPushButton * m_pPushButtonBasketBack;
		QPushButton * m_pPushButtonBasketForward;

	private slots:
		void slotMyBasket(bool abIndicator);
		void slotProductItemHovered(bool abIndicator);

		void slotProductDetails();
		void slotProductRemove();
		void slotSetQuantity();

		void slotBasketBack();
		void slotBasketForward();

	private:
		ProductShopClient * m_pProductShopClient;
		std::list<ProductShopClient*> * m_plstProducts;

		void init();
		void update();
	};
}
#endif //VR_PRODUCT_BASKET_INTERFACE_H