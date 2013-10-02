#include <QApplication>
#include <QVBoxLayout>

#include "VRProductInterface_GUI.h"

using namespace osg;
using namespace Ui;

//---------------------------------------------------------------------------

int main(int argc, char * argv[])	{
    QApplication app(argc, argv);

	VRProductInterface w;
	QFrame *f = new QFrame;
	w.setupUi(f);

	//To get a widget without a "TitleBar"
	f->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowSystemMenuHint);

	f->show();

	int nRetCode = app.exec();

    return nRetCode;
}
