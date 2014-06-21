#include "VRDatabaseManagerShopClient.h"

using namespace VR;
using namespace std;


//==================================================================================

DatabaseManagerShopClientParams::DatabaseManagerShopClientParams() :
DatabaseManagerParams()	{
}

//-------------------------------------------------------------------------------

DatabaseManagerShopClient::DatabaseManagerShopClient(QObject * parent) :
DatabaseManager(parent)	{
}

//-------------------------------------------------------------------------------

DatabaseManagerShopClient::DatabaseManagerShopClient(const DatabaseManagerShopClientParams & aDBMgrParams, QObject * parent):
DatabaseManager(aDBMgrParams,parent)	{
}

//-------------------------------------------------------------------------------

DatabaseManagerShopClient::~DatabaseManagerShopClient()	{
}

//===============================================================================
