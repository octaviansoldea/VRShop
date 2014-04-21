#ifndef VR_PRODUCT_BASKET_INTERFACE_H
#define VR_PRODUCT_BASKET_INTERFACE_H

#include <QObject>

class QDoubleSpinBox;
class QFrame;
class QLabel;
class QPushButton;
class QToolButton;

namespace VR	{
	class ProductBasketInterface : public QObject	{
		Q_OBJECT
	public:
		ProductBasketInterface(
			QToolButton * apToolButtonMyBasket,
			QLabel * apLabelBasketCase,
			QFrame * apFrameItemsBasket,
			QFrame * apFrameProductItem,
			QFrame * apFrameProductItemHover,
			QDoubleSpinBox * apDoubleSpinBoxQuantity,
			QPushButton * apPushButtonHoverDetails,
			QPushButton * apPushButtonHoverRemove,
			QLabel * apLabelProductImage,
			QLabel * m_pLabelProductInfo,
			QLabel * apLabelBasketProductPrice,
			QPushButton * apPushButtonBasketBack,
			QPushButton * apPushButtonBasketForward
		);	//End of constructor

		~ProductBasketInterface();

	private:
		QToolButton * m_pToolButtonMyBasket;
		QLabel * m_pLabelBasketCase;
		QFrame * m_pFrameItemsBasket;
		QFrame * m_pFrameProductItem;
		QFrame * m_pFrameProductItemHover;
		QDoubleSpinBox * m_pDoubleSpinBoxQuantity;
		QPushButton * m_pPushButtonHoverDetails;
		QPushButton * m_pPushButtonHoverRemove;
		QLabel * m_pLabelProductImage;
		QLabel * m_pLabelProductInfo;
		QLabel * m_pLabelBasketProductPrice;

		QPushButton * m_pPushButtonBasketBack;
		QPushButton * m_pPushButtonBasketForward;

	private slots:
		void slotMyBasket(bool abIndicator);
		void slotProductItemHovered();

		void slotHoverDetails();
		void slotHoverRemove();
		void slotSetQuantity();

		void slotBasketBack();
		void slotBasketForward();
	};
}
#endif //VR_PRODUCT_BASKET_INTERFACE_H