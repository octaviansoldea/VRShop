#ifndef VR_DATABASE_INTERFACE_SHOP_CLIENT_H
#define VR_DATABASE_INTERFACE_SHOP_CLIENT_H

#include <QObject>

#include "VRDatabaseInterface.h"

namespace VR {
	struct DatabaseInterfaceShopClientParams : public DatabaseInterfaceParams	{
		DatabaseInterfaceShopClientParams();
	};

	class DatabaseInterfaceShopClient : public DatabaseInterface	{

	public:
		DatabaseInterfaceShopClient();
		DatabaseInterfaceShopClient(const DatabaseInterfaceShopClientParams & aDBInterfaceParams);

		virtual ~DatabaseInterfaceShopClient();

		void loadScene(const std::string & astrScene);

		std::list<std::string> getListOfObjects(const std::string & astrScene);
		std::vector<std::string> getObjectData(std::string & strSceneObject);
	};
}
#endif //VR_DATABASE_MANAGER_SHOP_CLIENT_H