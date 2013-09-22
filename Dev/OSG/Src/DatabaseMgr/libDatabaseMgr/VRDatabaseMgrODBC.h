#ifndef VR_DATABASE_MGR_ODBC_H
#define VR_DATABASE_MGR_ODBC_H

#include "VRDatabaseMgr.h"

namespace VR {

	class DatabaseMgrODBC : public DatabaseMgr {

	public:
		virtual QString getDriverName() const;

		DatabaseMgrODBC(const QString & astrDBPathName);

		virtual void deleteItem(const QString &astrSceneObjectID);
		virtual void saveScene(const QString &astrOldSceneName, const QString &astrNewSceneName);
		virtual void loadScene(const QString &astrSceneName);
		virtual void newScene();

		virtual bool createTable();

		virtual void fillPrimitiveTable(std::string & astrCommand);
		virtual std::string getSQLData(const int & anElement);

		virtual void insertIntoDatabase(const DatabaseMgrParams & aDatabaseMgrParams);
		virtual std::vector<float> selectFromDatabase(const int & anElementID);
	};
}
#endif //VR_DATABASE_MGR_ODBC_H