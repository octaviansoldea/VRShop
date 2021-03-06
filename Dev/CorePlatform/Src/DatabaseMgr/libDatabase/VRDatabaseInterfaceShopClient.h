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

		void loadScene(const std::string & astrScene);

		std::list<std::string> getListOfObjects(const std::string & astrScene);
		std::vector<std::string> getObjectData(std::string & strSceneObject);
		std::vector<std::string> getObjectData(int anObjectID,std::string & astrClassName,std::string & astrObjectName);

		std::string getPrimitiveObjectData(int anObjectID,std::string & astrClassName,std::string & astrObjectName);

		std::list<std::string> getProductsData();
	};
}
#endif //VR_DATABASE_MANAGER_SHOP_CLIENT_H