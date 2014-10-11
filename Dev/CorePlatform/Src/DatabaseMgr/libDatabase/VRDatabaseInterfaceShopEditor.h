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

		virtual ~DatabaseInterfaceShopEditor();

		virtual void init(const DatabaseInterfaceShopEditorParams & aDBInterfaceParams);

		void insertScene(const std::string & astrScene);
		void insertObject(const std::string & astrScene, std::vector<std::string> & avecstrData);
		void insertProduct(std::vector<std::string> & avecstrData);

		std::list<std::string> getListOfObjects(const std::string & astrScene);
		std::vector<std::string> getObjectData(std::string & strSceneObject);

	private:
		virtual void systemOfTables(std::vector<std::pair<std::string,std::string>> & avecStmtPairs);
	};
}
#endif //VR_DATABASE_MANAGER_SHOP_EDITOR_H