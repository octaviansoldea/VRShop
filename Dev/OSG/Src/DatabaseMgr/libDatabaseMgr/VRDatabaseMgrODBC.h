#ifndef VR_DATABASE_MGR_ODBC_H
#define VR_DATABASE_MGR_ODBC_H

#include "VRDatabaseMgr.h"

namespace VR {

	class DatabaseMgrODBC : public DatabaseMgr {

	public:
		virtual QString getDriverName() const;

		DatabaseMgrODBC(const QString & astrDBPathName);

		virtual bool createTable();

		virtual void fillPrimitiveTable(const AbstractObject & aAbstractObject);
		virtual std::string readFromDB(std::string & astrCommand);


		virtual void insertIntoDatabase(const DatabaseMgrParams & aDatabaseMgrParams);

	};
}
#endif //VR_DATABASE_MGR_ODBC_H