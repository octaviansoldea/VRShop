#ifndef VR_SIGN_UP_GUI_H
#define VR_SIGN_UP_GUI_H

#include <QDialog>

#include "ui_VRSignUp_GUI.h"

namespace VR	{
	class SignUp_GUI : public QDialog, public Ui::SignUp {
		Q_OBJECT
	public:
		SignUp_GUI();

	private slots:
		void slotSignUpUser();
	};
}
#endif //VR_SIGN_UP_GUI_H