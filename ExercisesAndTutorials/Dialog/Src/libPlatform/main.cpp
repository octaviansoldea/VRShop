#include <qapplication>

#include "OutputWindow.h"

int main(int argc, char *argv[])	{
	QApplication app(argc, argv);

	OutputWindow *output = new OutputWindow;
	output->show();

	return app.exec();

	delete output;
}
