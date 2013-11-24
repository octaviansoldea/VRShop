#ifndef VR_DATABASE_MGR_H
#define VR_DATABASE_MGR_H

#include <vector>
#include <string>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "VRAbstractObject.h"

namespace VR {

	struct DatabaseMgrParams	{
		QString m_qstrObjectType;
		QString m_qstrObjectName;
		std::vector < std::string > m_arrstrParams;

		DatabaseMgrParams();
	};

	void printError(const char * apchMessage);
	void printWarning(const char * apchMessage);

	class DatabaseMgr {

	public:
		typedef enum {QODBC = 1, QSQLITE = 2} DRIVER_NAME;
		int m_nDriverSelection;
		virtual QString getDriverName() const = 0;

		static DatabaseMgr & Create(const QString & aqstrDBPathName, DRIVER_NAME aDriverName);
		static DatabaseMgr * CreateSQLite(const QString & aqstrDBPathName);
		static DatabaseMgr * CreateODBC(const QString & aqstrDBPathName);

		virtual ~DatabaseMgr() = 0;

		QSqlError lastError() const;

		virtual bool createTable() = 0;

		virtual void fillPrimitiveTable(const AbstractObject & aAbstractObject) = 0;
		virtual std::string readFromDB(std::string & astrCommand) = 0;


		virtual void insertIntoDatabase(const DatabaseMgrParams & aDatabaseMgrParams) = 0;


	protected:

		DatabaseMgr(const QString & aqstrDBPathName);
		bool connect2SQLDatabase();

		QSqlDatabase m_QSqlDatabase;

		const QString m_qstrDBPathName;
	};
}
#endif //VR_DATABASE_MGR_H