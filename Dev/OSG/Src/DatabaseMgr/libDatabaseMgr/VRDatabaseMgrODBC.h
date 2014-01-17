#ifndef VR_DATABASE_MGR_ODBC_H
#define VR_DATABASE_MGR_ODBC_H

#include "VRDatabaseMgr.h"

namespace VR {

	class DatabaseMgrODBC : public DatabaseMgr {

	public:
		virtual QString getDriverName() const;

		DatabaseMgrODBC(const QString & astrDBPathName);

		virtual bool executeQuery(const DatabaseMgrParams & aDatabaseMgrParams);

		virtual bool createTable(const DatabaseMgrParams & aDatabaseMgrParams) {return false;};

		virtual void fillPrimitiveTable(std::string & astrCommand);
		virtual std::string readFromDB(std::string & astrCommand);

	};
}
#endif //VR_DATABASE_MGR_ODBC_H