#include <QApplication>

#include "VRAppDataServer.h"

#include "VRAvatarManagerServer.h"
#include "VRUserAccountManager.h"
#include "VRVisitorManagerServer.h"
#include "VRCashierManagerServer.h"
#include "VRProductManagerServer.h"

#include "VRStaticInitOrderServer.h"

using namespace VR;
using namespace std;

StaticInitOrderServer::StaticInitOrderServer() {
	string strPluginsPath = AppDataServer::getFPathDependencies();
	QApplication::addLibraryPath(strPluginsPath.c_str());

	AvatarManagerServer::constructStatics();
	UserAccountManager::constructStatics();
	VisitorManagerServer::constructStatics();
	CashierManagerServer::constructStatics();
	ProductManagerServer::constructStatics();
}

StaticInitOrderServer::~StaticInitOrderServer() {
	AvatarManagerServer::deleteStatics();
	UserAccountManager::deleteStatics();
	VisitorManagerServer::deleteStatics();
	CashierManagerServer::deleteStatics();
	ProductManagerServer::deleteStatics();
}
