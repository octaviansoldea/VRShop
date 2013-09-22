#ifndef VR_DATABASE_MGR_SQLITE_H
#define VR_DATABASE_MGR_SQLITE_H

#include <string>

#include "VRDatabaseMgr.h"

namespace VR {

	class DatabaseMgrSQLite : public DatabaseMgr {

	public:
		virtual QString getDriverName() const;

		DatabaseMgrSQLite(const QString & aqstrDBPathName);

		virtual void deleteItem(const QString &aqstrSceneObjectID);
		virtual void saveScene(const QString &aqstrOldSceneName, const QString &aqstrNewSceneName);
		virtual void loadScene(const QString &aqstrSceneName);
		virtual void newScene();


		virtual bool createTable();

		virtual void fillPrimitiveTable(std::string & astrCommand);
		virtual std::string getSQLData(const int & anElement);
		

		virtual void insertIntoDatabase(const DatabaseMgrParams & aDatabaseMgrParams);
		virtual std::vector<float> selectFromDatabase(const int & anElementID);
	};
}
#endif //VR_DATABASE_MGR_SQLITE_H