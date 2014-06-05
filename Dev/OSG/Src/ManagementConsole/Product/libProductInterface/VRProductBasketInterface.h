#ifndef VR_PRODUCT_BASKET_INTERFACE_H
#define VR_PRODUCT_BASKET_INTERFACE_H

#include <QObject>
#include <list>

class QDoubleSpinBox;
class QFrame;
class QLabel;
class QPushButton;
class QToolButton;


namespace VR	{
	class Basket;
	class ProductShopClient;
	class ProductBasketInterfaceItem_GUI;
	class ProductBasketInterfaceController;

	class ProductBasketInterface : public QObject	{
		Q_OBJECT
	public:
		ProductBasketInterface(
			QToolButton * apToolButtonMyBasket,
			QLabel * apLabelBasketCase,
			QFrame * apFrameItemsBasket,
			QPushButton * apPushButtonBasketBack,
			QPushButton * apPushButtonBasketForward
		);	//End of constructor

		~ProductBasketInterface();

		void setBasket(Basket * apBasket);

	private:
		QToolButton * m_pToolButtonMyBasket;
		QLabel * m_pLabelBasketCase;
		QFrame * m_pFrameItemsBasket;
		QPushButton * m_pPushButtonBasketBack;
		QPushButton * m_pPushButtonBasketForward;

	private slots:
		void slotMyBasket(bool abIndicator);

		void slotBasketBack();
		void slotBasketForward();
		void slotUpdateItemView(const int & anIndex, bool abIsAdded);	//Called with the change of the basket size

	private:
		Basket * m_pBasket;
		std::list<ProductBasketInterfaceItem_GUI*> m_lstProductItemGUI;

		ProductBasketInterfaceController * m_pProductBasketInterfaceController;

		ProductBasketInterfaceItem_GUI * getProductItemGUI(int anPosition);

		void setData(ProductShopClient * apProduct, bool abAppend=true);

		void initGeometry();
		void setupBasketInterface();

		int m_nHandlePosition;	//First item on the left
		const int m_nItemsVisible;	//No of items shown in the Basket bar
	};
}
#endif //VR_PRODUCT_BASKET_INTERFACE_H