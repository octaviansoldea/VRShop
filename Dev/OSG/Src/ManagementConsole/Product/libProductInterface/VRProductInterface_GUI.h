#ifndef VR_PRODUCT_INTERFACE_GUI_H
#define VR_PRODUCT_INTERFACE_GUI_H

#include <QFrame>

#include "ui_VRProductInterface.h"

namespace VR	{
	class Product;

	class ProductInterface_GUI : public QFrame, public Ui::ProductInterface	{
		Q_OBJECT
	public:
		ProductInterface_GUI();
		ProductInterface_GUI(QWidget * parent = 0, Product * apProduct=0);
		~ProductInterface_GUI();

	private:
		Product * m_pProduct;
	};
}
#endif //VR_PRODUCT_INTERFACE_GUI_H