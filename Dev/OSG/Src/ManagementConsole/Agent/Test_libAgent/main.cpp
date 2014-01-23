#include <QApplication>

#include "VRUserAccount.h"

using namespace VR;

int main(int argc, char * argv[])	{
	QApplication app(argc, argv);

	UserAccount ua;
	ua.createUserAccountDB();

	return(0);
}