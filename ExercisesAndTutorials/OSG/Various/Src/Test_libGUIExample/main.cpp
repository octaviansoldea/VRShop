#include <QApplication>

#include "OSG_GUI.h"

using namespace osg;
using namespace Ui;

//---------------------------------------------------------------------------

int Test_OSGQT(int argc, char * argv[])	{
    QApplication app(argc, argv);

	OSGQT_GUI widget;

	widget.show();

	int nRetCode = app.exec();

    return nRetCode;
}

//===================================================================

int main(int argc, char * argv[])	{
	Test_OSGQT(argc, argv);
	return 0;
}