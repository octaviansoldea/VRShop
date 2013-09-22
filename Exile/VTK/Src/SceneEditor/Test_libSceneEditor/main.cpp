#include <QApplication>
#include <QMessageBox>
#include "FunctorPathResource.h"
#include "DatabaseMgr.h"
#include "VRShopEditorDlg.h"

int main(int argc, char *argv[])	{
	QApplication app(argc, argv);

//	const char * pchGen = "C:/Projekti/VRShop/Dev/Resources/Databases/";
//
//	if(
//		((argc != 1) && (argc != 3)) ||
//	    ((argc == 3) && (strcmp(pchGen, argv[1]) != 0))
//	  ) {
//		QString strUsage1 = QString("Usage 1: ") + argv[0] + " " + pchGen + " " + "DataBaseFullPathName";
//		QString strUsage2 = QString("Usage 2: ") + argv[0];
//		QMessageBox msgBox;
//		msgBox.setText(strUsage1);
//		msgBox.setInformativeText(strUsage2);
//		msgBox.setStandardButtons(QMessageBox::Ok);
//		msgBox.setDefaultButton(QMessageBox::Ok);
//		int ret = msgBox.exec();
//		exit(-1);
//	}
//
//	if((argc == 3) && (strcmp(pchGen, argv[1]) == 0)) {
//		//Create initial SQL table
//		DatabaseMgr & database = DatabaseMgr::Create(strcat(argv[1],argv[2]), DatabaseMgr::QSQLITE);
//		database.createTable();
//		const QString location[3] = {"0","0","0"};
//		const QString orientation[3] = {"0","0","0"};
//		database.insertItem("Shop", "Furniture", "Desk", "2","banana.jpg", location, orientation);
//
////		exit(0);
//	}
//
//	VRShopEditorDlg *vrShopEditorDlg = new VRShopEditorDlg;
//
//	vrShopEditorDlg->show();
//
	return app.exec();
}

//C:/Projekti/VRShop/Dev/Resources/Databases Products.db