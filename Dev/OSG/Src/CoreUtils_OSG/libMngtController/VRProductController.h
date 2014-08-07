#ifndef VR_PRODUCT_CONTROLLER_H
#define VR_PRODUCT_CONTROLLER_H

#include <QObject>

class QLineEdit;
class QComboBox;
class QPushButton;

#include <osg/ref_ptr>

namespace VR {
	class AbstractObject;
	class ProductShopEditor;
	class ProductManager;

	class PickAndDragHandlerShopEditor;

	class ProductController : public QObject {
	public:
		//Objects from the GUI
		ProductController(
			QPushButton * apPushButton_ProductSettings_AddNewProduct,
			QPushButton * apPushButton_ProductSettings_RemoveProduct,
			QPushButton * apPushButton_ProductSettings_Apply,
			QPushButton * apPushButton_ProductSettings_Cancel,
			QPushButton * apPushButton_ProductSettings_MoreSettings,
			QComboBox * apComboBox_ProductSettings_ProductName,
			QLineEdit * apLineEdit_ProductSettings_NewPrice,
			QLineEdit * apLineEdit_ProductSettings_NewQuantity,
			QLineEdit * apLineEdit_ProductSettings_Price,
			QLineEdit * apLineEdit_ProductSettings_Quantity,

			ProductManager * apProductMgr,
			PickAndDragHandlerShopEditor * apPickAndDragHandlerShopEditor
		);	//End of constructor

		
		~ProductController();

	public slots:
		void slotAddNewProduct();
		void slotRemoveProduct();
		void slotProductMoreSettings();

		void slotSetModifyProduct(const AbstractObject * apAbstractObject);
		void slotSetModifyProduct();

	private:
		Q_OBJECT

		QPushButton * m_pPushButton_ProductSettings_AddNewProduct;
		QPushButton * m_pPushButton_ProductSettings_RemoveProduct;
		QPushButton * m_pPushButton_ProductSettings_Apply;
		QPushButton * m_pPushButton_ProductSettings_Cancel;
		QPushButton * m_pPushButton_ProductSettings_MoreSettings;
		QComboBox * m_pComboBox_ProductSettings_ProductName;
		QLineEdit * m_pLineEdit_ProductSettings_NewPrice;
		QLineEdit * m_pLineEdit_ProductSettings_NewQuantity;
		QLineEdit * m_pLineEdit_ProductSettings_Price;
		QLineEdit * m_pLineEdit_ProductSettings_Quantity;

		ProductManager * m_pProductMgr;
		ProductShopEditor * m_pProductShopEditor;

		PickAndDragHandlerShopEditor * m_pPickAndDragHandlerShopEditor;
	};
}
#endif //VR_PRODUCT_CONTROLLER_H