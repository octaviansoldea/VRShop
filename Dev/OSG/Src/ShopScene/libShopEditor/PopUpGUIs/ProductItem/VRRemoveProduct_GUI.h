#ifndef VR_REMOVE_PRODUCT_GUI_H
#define VR_REMOVE_PRODUCT_GUI_H

#include <QDialog>

#include <osg/Node>

#include "ui_VRRemoveProduct_GUI.h"

namespace VR	{
	class Product;
	class ProductController;

	class RemoveProduct_GUI : public QDialog, public Ui::RemoveProduct {
		Q_OBJECT
	public:
		RemoveProduct_GUI();
		RemoveProduct_GUI(Product * apProduct);
		~RemoveProduct_GUI();

	public slots:
		virtual void accept();
		virtual void close();

	private:
		void buildConnections();

		Product * m_pProduct;
	};
}
#endif //VR_REMOVE_PRODUCT_GUI_H