#ifndef VR_PRODUCT_BASKET_INTERFACE_ITEM_GUI_H
#define VR_PRODUCT_BASKET_INTERFACE_ITEM_GUI_H

#include <QFrame>

#include "ui_VRProductBasketInterfaceItem_GUI.h"

namespace VR	{
	class ProductShopClient;
	
	class ProductBasketInterfaceItem_GUI : public QFrame, public Ui::ProductBasketInterfaceItem	{
		Q_OBJECT
	public:
		ProductBasketInterfaceItem_GUI(
			QFrame *apParent=0);

		ProductBasketInterfaceItem_GUI(
			ProductShopClient * apProductShopClient, 
			QFrame *apParent=0);

		void init(ProductShopClient * apProductShopClient);
		ProductShopClient * getProduct();

	public slots:
		void slotProductItemHovered(bool abIndicator);
		void slotProductDetails();
		void slotProductRemove();
		void slotSetQuantity();

		void slotSetProductSpinBox(float aflNewProductValue);

	signals:
		void signalModifyProductQuantity(ProductShopClient * apProductShopClient, float aflNewQuantity);
		void signalRemoveProduct(ProductShopClient * apProductShopClient);

	private:
		ProductShopClient * m_pProductShopClient;
	};
}
#endif //VR_PRODUCT_BASKET_INTERFACE_ITEM_GUI_H