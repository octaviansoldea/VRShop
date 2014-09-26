#include <string>

#include "qapplication.h"

#include "SphereWidget.h"
#include "ui_SelectTwoPointsGUI.h"
#include "SelectTwoPointsGUI.h"

using namespace std;

extern std::string strFullPathResources;

SelectTwoPointsGUI * pSelectTwoPointsGUI;

int main(int argc, char** argv)
{

	QApplication app(argc, argv);

	pSelectTwoPointsGUI = new SelectTwoPointsGUI();
	string strID = string("Select Two Points");
	pSelectTwoPointsGUI->setWindowTitle(strID.c_str());

	pSelectTwoPointsGUI->show();

	int nRetCode = app.exec();

	delete pSelectTwoPointsGUI;

	return(nRetCode);

}

