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

		void insertObject(const std::string & astrScene, std::vector<std::string> & avecstrData);
	};
}
#endif //VR_DATABASE_MANAGER_SHOP_EDITOR_H