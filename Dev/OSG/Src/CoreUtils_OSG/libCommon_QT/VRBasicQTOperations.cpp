#include <QMessageBox>

#include "VRBasicQTOperations.h"

void printError(const QString & aqstrMessage) {
	QMessageBox msgBox;
	msgBox.setText(aqstrMessage);
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setWindowTitle("Error window");
	int nRes = msgBox.exec();
}


void printWarning(const QString & aqstrMessage) {
	QMessageBox msgBox;
	msgBox.setText(aqstrMessage);
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setWindowTitle("Warning window");
	int nRes = msgBox.exec();
}
