#ifndef VR_DATABASE_MANAGER_SHOP_CLIENT_H
#define VR_DATABASE_MANAGER_SHOP_CLIENT_H

#include <QObject>

#include "VRDatabaseManager.h"

namespace VR {
	struct DatabaseManagerShopClientParams : public DatabaseManagerParams	{
		DatabaseManagerShopClientParams();
	};

	class DatabaseManagerShopClient : public DatabaseManager	{

	public:
		DatabaseManagerShopClient(QObject * parent = 0);
		DatabaseManagerShopClient(const DatabaseManagerShopClientParams & aDBMgrParams, QObject * parent = 0);

		virtual ~DatabaseManagerShopClient();
	};
}
#endif //VR_DATABASE_MANAGER_SHOP_CLIENT_H