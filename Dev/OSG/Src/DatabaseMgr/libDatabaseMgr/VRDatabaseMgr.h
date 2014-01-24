#ifndef VR_DATABASE_MGR_H
#define VR_DATABASE_MGR_H

#include <vector>
#include <string>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace VR {

	struct DatabaseMgrParams	{
		std::string m_strTableName;
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

		virtual bool executeQuery(const DatabaseMgrParams & aDatabaseMgrParams) = 0;
		virtual bool createTable(const DatabaseMgrParams & aDatabaseMgrParams) = 0;

		virtual void fillPrimitiveTable(std::string & astrCommand) = 0;
		virtual std::string readFromDB(std::string & astrCommand) = 0;

	protected:

		DatabaseMgr(const QString & aqstrDBPathName);
		bool connect2SQLDatabase();

		QSqlDatabase * m_pQSqlDatabase;

		const QString m_qstrDBPathName;

		void disconnectFromSQLDatabase();
	};
}
#endif //VR_DATABASE_MGR_H

