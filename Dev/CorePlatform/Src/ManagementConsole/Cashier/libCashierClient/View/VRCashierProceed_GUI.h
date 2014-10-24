#ifndef VR_CASHIER_PROCEED_GUI_H
#define VR_CASHIER_PROCEED_GUI_H

#include <QDialog>

#include "ui_VRCashierProceed_GUI.h"

namespace VR	{
	class CashierProceed_GUI : public QDialog, public Ui::CashierProceed	{
		Q_OBJECT
	public:
		CashierProceed_GUI(QDialog * apParent = 0);

		enum ITEM_NAME	{
			PRODUCT = 0,
			QUANTITY,
			PRICE,
			DISCOUNT,
			AMOUNT
		};
	};
}
#endif //VR_CASHIER_PROCEED_GUI_H