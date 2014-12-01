#ifndef VR_CASHIER_GUI_H
#define VR_CASHIER_GUI_H

#include <QDialog>
#include "ui_VRCashier_GUI.h"

namespace VR	{
	class Cashier_GUI : public QDialog, public Ui::Cashier	{
	public:
		Cashier_GUI(QDialog * apParent = 0);

		enum ITEM_NAME	{
			PRODUCT = 0,
			QUANTITY,
			PRICE,
			DISCOUNT,
			AMOUNT
		};
	};
}
#endif //VR_CASHIER_GUI_H