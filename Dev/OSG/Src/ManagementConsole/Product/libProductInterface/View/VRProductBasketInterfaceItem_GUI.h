#ifndef VR_PRODUCT_BASKET_INTERFACE_ITEM_GUI_H
#define VR_PRODUCT_BASKET_INTERFACE_ITEM_GUI_H

#include <QFrame>

#include "ui_VRProductBasketInterfaceItem_GUI.h"

namespace VR	{
	class ProductShopClient;
	class ProductBasketInterfaceController;
	
	class ProductBasketInterfaceItem_GUI : public QFrame, public Ui::ProductBasketInterfaceItem	{
		Q_OBJECT
	public:
		ProductBasketInterfaceItem_GUI(
			ProductBasketInterfaceController * apProductBasketInterfaceController,
			QFrame *apParent=0);

		ProductBasketInterfaceItem_GUI(
			ProductShopClient * apProductShopClient, 
			ProductBasketInterfaceController * apProductBasketInterfaceController,
			QFrame *apParent=0);
		~ProductBasketInterfaceItem_GUI();

		void init(ProductShopClient * apProductShopClient);

	public slots:
		void slotProductItemHovered(bool abIndicator);
		void slotProductDetails();
		void slotProductRemove();
		void slotSetQuantity();

	private:
		ProductShopClient * m_pProductShopClient;
		ProductBasketInterfaceController * m_pProductBasketInterfaceController;
	};
}
#endif //VR_PRODUCT_BASKET_INTERFACE_ITEM_GUI_H