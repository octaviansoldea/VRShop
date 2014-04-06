#ifndef VR_PRODUCT_CONTROLLER_H
#define VR_PRODUCT_CONTROLLER_H

#include <QObject>

class QLineEdit;
class QComboBox;
class QLabel;
class QPushButton;
class QTextEdit;

namespace VR {
	class Product;

	struct ProductController : public QObject {
		ProductController();

	public slots:
		void slotUpdateProduct();

	private:
		Q_OBJECT

		QComboBox *m_pComboBoxProductCategory;
    QLineEdit *m_pLineEditProductName;
    QLineEdit *m_pLineEditProductCode;
    QTextEdit *m_pTextEditProductDescription;
    QLineEdit *m_pLineEditShortDescription;
    QLineEdit *m_pLineEditProductURL;
    QComboBox *m_pComboBoxProducer;
    QTextEdit *m_pTextEditProducerAddress;
    QComboBox *m_pComboBoxProducerURL;
    QComboBox *m_pComboBoxPlaceOfOrigin;
    QLabel *m_pLabelImage;
    QComboBox *m_pComboBoxImageSelect;
    QPushButton *m_pPushButtonImageSelectFile;
    QComboBox *m_pComboBoxProductUnit;
    QComboBox *m_pComboBoxUnitQuantity;
    QComboBox *m_pComboBoxTaxRate;
    QLineEdit *m_pLineEditLocationX;
    QLineEdit *m_pLineEditLocationY;
    QLineEdit *m_pLineEditLocationZ;
    QLineEdit *m_pLineEditQuantity;
    QLineEdit *m_pLineEditQuantLastChanged;
    QLineEdit *m_pLineEditPrice;
    QLineEdit *m_pLineEditPriceLastChanged;
    QPushButton *m_pPushButtonSave;
    QPushButton *m_pPushButtonCancel;

	};
}
#endif //VR_PRODUCT_CONTROLLER_H