#ifndef VR_DATABASE_MANAGER_SHOP_EDITOR_H
#define VR_DATABASE_MANAGER_SHOP_EDITOR_H

#include <QObject>

#include "VRDatabaseManager.h"

namespace VR {
	struct DatabaseManagerShopEditorParams : public DatabaseManagerParams	{
		DatabaseManagerShopEditorParams();
	};

	class DatabaseManagerShopEditor : public DatabaseManager	{

	public:
		DatabaseManagerShopEditor(QObject * parent = 0);
		DatabaseManagerShopEditor(const DatabaseManagerShopEditorParams & aDBMgrParams, QObject * parent = 0);

		virtual ~DatabaseManagerShopEditor();

		virtual void init(const DatabaseManagerShopEditorParams & aDBMgrParams);

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