#ifndef VR_DATABASE_INTERFACE_SHOP_EDITOR_H
#define VR_DATABASE_INTERFACE_SHOP_EDITOR_H

#include <QObject>

#include "VRDatabaseInterface.h"

namespace VR {
	struct DatabaseInterfaceShopEditorParams : public DatabaseInterfaceParams	{
		DatabaseInterfaceShopEditorParams();
	};

	class DatabaseInterfaceShopEditor : public DatabaseInterface	{

	public:
		DatabaseInterfaceShopEditor();
		DatabaseInterfaceShopEditor(const DatabaseInterfaceShopEditorParams & aDBInterfaceParams);

		virtual void init(const DatabaseInterfaceShopEditorParams & aDBInterfaceParams);

		void insertScene(const std::string & astrScene);
		void insertObject(const std::string & astrScene, std::vector<std::string> & avecstrData);

		std::list<std::string> getListOfObjects(const std::string & astrScene);
		std::vector<std::string> getObjectData(std::string & strSceneObject);
		std::vector<std::string> getObjectData(int anObjectID,std::string & astrClassName,std::string & astrObjectName);

		std::string getPrimitiveObjectData(int anObjectID,std::string & astrClassName,std::string & astrObjectName);

		std::list<std::string> getProductsData();


	private:
		void systemOfTables(std::vector<std::pair<std::string,std::string>> & avecStmtPairs);
	};
}
#endif //VR_DATABASE_MANAGER_SHOP_EDITOR_H