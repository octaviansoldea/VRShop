#ifndef VR_CASHIER_WELCOME_GUI_H
#define VR_CASHIER_WELCOME_GUI_H

#include <QDialog>
#include <QObject>

#include "ui_VRCashierWelcome_GUI.h"

namespace VR	{
	class CashierWelcome_GUI : public QDialog, public Ui::Cashier	{
		Q_OBJECT
	public:
		CashierWelcome_GUI(QDialog * apParent = 0);
	};
}
#endif //VR_CASHIER_WELCOME_GUI_H