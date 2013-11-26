#ifndef VR_DATABASE_MGR_SQLITE_H
#define VR_DATABASE_MGR_SQLITE_H

#include <string>

#include "VRDatabaseMgr.h"

namespace VR {

	class DatabaseMgrSQLite : public DatabaseMgr {

	public:
		virtual QString getDriverName() const;

		DatabaseMgrSQLite(const QString & aqstrDBPathName);

		virtual bool createTable(const std::string & astrSQLCommand);

		virtual void fillPrimitiveTable(std::string & astrCommand);
		virtual std::string readFromDB(std::string & astrCommand);


		virtual void insertIntoDatabase(const DatabaseMgrParams & aDatabaseMgrParams);
	};
}
#endif //VR_DATABASE_MGR_SQLITE_H