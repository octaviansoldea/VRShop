#ifndef VR_DATABASE_MGR_SQLITE_H
#define VR_DATABASE_MGR_SQLITE_H

#include <string>

#include "VRDatabaseMgr.h"

namespace VR {

	class DatabaseMgrSQLite : public DatabaseMgr {

	public:
		virtual QString getDriverName() const;

		DatabaseMgrSQLite(const QString & aqstrDBPathName);

		virtual bool executeQuery(const DatabaseMgrParams & aDatabaseMgrParams);
		virtual bool createTable(const DatabaseMgrParams & aDatabaseMgrParams);

		virtual void fillPrimitiveTable(std::string & astrCommand);
		virtual std::string readFromDB(std::string & astrCommand);


	};
}
#endif //VR_DATABASE_MGR_SQLITE_H