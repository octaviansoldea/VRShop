#include <string>

#include "qapplication.h"

#include "SelectTwoPointsGUI.h"

using namespace std;

int main(int argc, char** argv)
{

	QApplication app(argc, argv);

	SelectTwoPointsGUI selectTwoPointsGUI;

	selectTwoPointsGUI.show();

	int nRetCode = app.exec();

	return(nRetCode);

}

