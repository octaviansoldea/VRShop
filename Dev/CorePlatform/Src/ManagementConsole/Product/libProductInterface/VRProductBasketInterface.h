#ifndef VR_PRODUCT_BASKET_INTERFACE_H
#define VR_PRODUCT_BASKET_INTERFACE_H

#include <QObject>
#include <list>

class QFrame;
class QLabel;
class QPushButton;
class QToolButton;

namespace VR	{
	class ProductShopClient;
	class BasketClient;
	class ProductBasketInterfaceItem_GUI;
	class Client;

	class ProductBasketInterface : public QObject	{
		Q_OBJECT
	public:
		ProductBasketInterface(
			QToolButton * apToolButtonMyBasket,
			QLabel * apLabelBasketCase,
			QFrame * apFrameItemsBasket,
			QPushButton * apPushButtonBasketBack,
			QPushButton * apPushButtonBasketForward,
			BasketClient * apBasket,
			Client * m_pClient
		);	//End of constructor

		~ProductBasketInterface();

	private:
		QToolButton * m_pToolButtonMyBasket;
		QLabel * m_pLabelBasketCase;
		QFrame * m_pFrameItemsBasket;
		QPushButton * m_pPushButtonBasketBack;
		QPushButton * m_pPushButtonBasketForward;
		BasketClient * m_pBasket;
		Client * m_pClient;

	private slots:
		void slotMyBasket(bool abIndicator);
		void slotBasketBack();
		void slotBasketForward();
		void slotUpdateItemView(const int & anIndex, bool abIsAdded);	//Called with the change of the basket size

	private:
		std::list<ProductBasketInterfaceItem_GUI*> m_lstProductItemGUI;

		ProductBasketInterfaceItem_GUI * getProductItemGUI(int anPosition);

		void setData(ProductShopClient * apProduct, bool abAppend=true);

		void initGeometry();
		void setupBasketInterface();

		int m_nHandlePosition;	//First item on the left
		const int m_nItemsVisible;	//No of items shown in the Basket bar

	signals:
		void signalProductBasketChangeRequest(ProductShopClient * apProduct);
		void signalProductBasketModifyRequest(ProductShopClient * apProduct, float aflNewQuantity);
		void signalSetSpinBoxProduct(float aflNewSpinBoxValue);

	private slots:
		void slotRemoveFromBasketClicked(ProductShopClient * apProduct);

	public:
		void removeProductRespond(QDataStream & aDataStream);

	private:
		ProductShopClient * m_pProduct;
	};
}
#endif //VR_PRODUCT_BASKET_INTERFACE_H