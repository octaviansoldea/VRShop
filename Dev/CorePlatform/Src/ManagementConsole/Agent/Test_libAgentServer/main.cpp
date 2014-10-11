#include <QApplication>

#include "VRUserAccountManager.h"

int main(int argc, char * argv[])	{

	VR::UserAccountManager ua;
	ua.createUserAccountDB();

	return(0);
}